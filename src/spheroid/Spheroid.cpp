#include "os.h"
#include "util.h"
#include "ID.h"
#include "Kind.h"
#include "Vector.h"
#include "List.h"
#include "Spheroid.h"

Spheroid::Spheroid (Vector *r,
		    Vector *u,
		    Vector *E,
		    Vector *d,
		    Vector *F,
		    Vector *T,
		    List *list,
		    ID *id,
		    Kind *kind,
		    double const a,
		    double const b):
		    Particle(r, u, E, d, F, T, list, id, kind, a),
		    _radius_minor_(a),
		    _radius_major_(b)
{
	return;
}

double Spheroid::radius_minor () const
{
	return this->_radius_minor_;
}

double Spheroid::radius_major () const
{
	return this->_radius_major_;
}

void Spheroid::ia (const Particle *particle)
{
	const Particle *that = particle;
	const Kind *kind = that->kind;
	kind_t const k = kind->k();
	switch(k){
		case SPHERE:
		os::print("spheroid-sphere interaction\n");
		break;
		case JANUS:
		os::print("spheroid-janus interaction\n");
		break;
		case SPHEROID:
		os::print("spheroid-spheroid interaction\n");
		break;
		case CHIRAL:
		os::print("spheroid-chiral interaction\n");
		break;
		default:
		os::print("no interaction\n");
	}
}

void *Spheroid::operator new (size_t size)
{
	return util::malloc(size);
}

void Spheroid::operator delete (void *p)
{
	p = util::free(p);
}

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
source: src/spheroid/Spheroid.cpp

References:
[0] A Koenig and B Moo, Accelerated C++ Practical Programming by Example.
[1] MP Allen and DJ Tildesley, Computer Simulation of Liquids.
[2] S Kim and S Karrila, Microhydrodynamics.

*/
