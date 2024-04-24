#include <cmath>
#include <cstdio>
#if defined(DEBUG) && DEBUG
#include "os.h"
#endif
#include "util.h"
#include "ID.h"
#include "Kind.h"
#include "Vector.h"
#include "List.h"
#include "Config.h"
#include "VerletList.h"
#include "Particle.h"

Particle::Particle (Vector *r,
		    Vector *u,
		    Vector *E,
		    Vector *d,
		    Vector *F,
		    Vector *T,
		    VerletList *vl,
		    ID *id,
		    Kind *kind,
		    double const a):
		    BDXObject(r)
{
	this->u = u;
	this->E = E;
	this->d = d;
	this->F = F;
	this->T = T;
	this->vl = vl;
	this->id = id;
	this->kind = kind;
	this->__radius__ = a;
	this->__rotational_mobility_scaling__= (1.0 / sqrt(a * a * a));
	this->__translational_mobility_scaling__ = (1.0 / sqrt(a));
}

void *Particle::operator new (size_t size)
{
	return util::malloc(size);
}

void Particle::operator delete (void *p)
{
	p = util::free(p);
}

double Particle::_rotational_mobility_scaling_() const
{
	return this->__rotational_mobility_scaling__;
}

double Particle::_translational_mobility_scaling_() const
{
	return this->__translational_mobility_scaling__;
}

void Particle::_updatePositionVectorComponent_ (double *x,
					        double const F_x,
					        double const mobility)
{
	double const mob = mobility;
	*x += (mob * F_x);
}

void Particle::_orient_ (double const mobility)
{
	double const mob = mobility;
	Vector *dTheta = this->F;
	dTheta->zero();
	this->_updatePositionVectorComponent_(&dTheta->x, this->T->x, mob);
	this->_updatePositionVectorComponent_(&dTheta->y, this->T->y, mob);
	this->_updatePositionVectorComponent_(&dTheta->z, this->T->z, mob);
	Vector *dOrient = this->T;
	Vector *director = this->d;
	vector::cross(dOrient, dTheta, director);
	this->_updatePositionVectorComponent_(&director->x, dOrient->x, 1.0);
	this->_updatePositionVectorComponent_(&director->y, dOrient->y, 1.0);
	this->_updatePositionVectorComponent_(&director->z, dOrient->z, 1.0);
	director->unit();
}

void Particle::_translate_ (double const mobility)
{
	double const mob = mobility;
	this->_updatePositionVectorComponent_(&this->r->x, this->F->x, mob);
	this->_updatePositionVectorComponent_(&this->r->y, this->F->y, mob);
	this->_updatePositionVectorComponent_(&this->r->z, this->F->z, mob);
	this->_updatePositionVectorComponent_(&this->u->x, this->F->x, mob);
	this->_updatePositionVectorComponent_(&this->u->y, this->F->y, mob);
	this->_updatePositionVectorComponent_(&this->u->z, this->F->z, mob);
}

void Particle::_rotate_ (double const mobility)
{
	double const mob = mobility;
	this->_updatePositionVectorComponent_(&this->E->x, this->T->x, mob);
	this->_updatePositionVectorComponent_(&this->E->y, this->T->y, mob);
	this->_updatePositionVectorComponent_(&this->E->z, this->T->z, mob);
}

void Particle::BrownianMotion ()
{
	constexpr double dt = GLOBAL_TIME_STEP;
	constexpr double translational_mobility_base = sqrt(2.0 * dt);
	constexpr double rotational_mobility_base = sqrt(1.5 * dt);
	double const translational_mobility = (this->_translational_mobility_scaling_() *
					       translational_mobility_base);
	double const rotational_mobility = (this->_rotational_mobility_scaling_() *
					    rotational_mobility_base);
	this->_translate_(translational_mobility);
	this->_rotate_(rotational_mobility);
	this->_orient_(rotational_mobility);
}

void Particle::txt (void *stream) const
{
	FILE *f = (FILE*) stream;
	this->id->txt(stream);
	this->kind->txt(stream);
	this->r->txt(stream);
	this->u->txt(stream);
	this->E->txt(stream);
	this->d->txt(stream);
	this->F->txt(stream);
	this->T->txt(stream);
	fprintf(f, "%.15e \n", this->radius());
}

double Particle::radius () const
{
	return this->__radius__;
}

// NOTE:
// if the user forgets to adds the interaction ranges (for the particle kinds of interest)
// to these tables we will be able to determine that and complain accordingly as long as
// these tables remain static (zero initialized) in the `config` module
bool Particle::checkInteractionTable (const Particle **begin, const Particle **end) const
{
	for (const Particle **particles = begin; particles != end; ++particles) {
		const Particle *particle = *particles;
		const Particle *that = particle;
		if (that == this) {
			continue;
		}
		double const tbl = config::particleInteractionRange(this, that);
		double const xtbl = config::particleExtendedInteractionRange(this, that);
		if (tbl == 0 || xtbl == 0) {
			return false;
		}
	}
	return true;
}

double Particle::contact (const Particle *particle) const
{
	const Particle *that = particle;
	return (this->radius() + that->radius());
}

double Particle::extent2 (const Particle *particle) const
{
	const Particle *that = particle;
	double const extent_base = config::particleExtendedInteractionRange(this, that);
	double const contact = this->contact(that);
	double const extent2 = (contact * extent_base) * (contact * extent_base);
	return extent2;
}

bool Particle::isNeighbor (const Particle *particle) const
{
	Vector relativePosition = Vector();
	Vector *relpos = &relativePosition;
	const Particle *that = particle;
	vector::sub(relpos, this->r, that->r);
	double const dist2 = relpos->norm2();
	double const extent2 = this->extent2(that);
	if (dist2 < extent2) {
		return true;
	} else {
		return false;
	}
}

void Particle::addNeighbor (Particle *particle)
{
	Particle *that = particle;
	this->vl->add(that);
}

void Particle::clearVerletList ()
{
	this->vl->clear();
}

size_t Particle::sizeVerletList () const
{
	return this->vl->numel();
}

#if defined(DEBUG) && DEBUG
void Particle::buildVerletList (Particle **begin, Particle **end)
{
	size_t pairs = 0;
	this->clearVerletList();
	for (Particle **particles = begin; particles != end; ++particles) {
		Particle *particle = *particles;
		Particle *that = particle;
		if (this == that) {
			continue;
		}

		if (this->isNeighbor(that)) {
			this->addNeighbor(that);
			++pairs;
		}
	}

	if (this->sizeVerletList() != pairs) {
		os::print("FAIL");
	}
}
#else
void Particle::buildVerletList (Particle **begin, Particle **end)
{
	this->clearVerletList();
	for (Particle **particles = begin; particles != end; ++particles) {
		Particle *particle = *particles;
		Particle *that = particle;
		if (this == that) {
			continue;
		}

		if (this->isNeighbor(that)) {
			this->addNeighbor(that);
		}
	}
}
#endif

/*

BDX                                             December 31, 2023

Copyright (C) 2023 Misael Díaz-Maldonado

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.

author: @misael-diaz
source: src/particle/Particle.cpp

References:
[0] A Koenig and B Moo, Accelerated C++ Practical Programming by Example.
[1] MP Allen and DJ Tildesley, Computer Simulation of Liquids.
[2] S Kim and S Karrila, Microhydrodynamics.

*/
