#include <cmath>
#include <cstdio>
#include <cstdlib>
#include "bdx.hpp"
#include "util.hpp"
#include "HardSphere.hpp"

HardSphere::HardSphere (
			long const kind,
			long const group,
			long const feat,
			long const id,
			double const x,
			double const y,
			double const z,
			double const radius,
			double const time_step,
			double const repulsionHS
		) :
	Particle(
			kind,
			group,
			feat,
			id,
			x,
			y,
			z,
			radius,
			time_step
		 )
{
	this->_repulsionHS_ = repulsionHS;
}

void *HardSphere::operator new (size_t size)
{
	return util::malloc(size);
}

void HardSphere::operator delete (void *p)
{
	p = util::free(p);
}

// TODO: we only have the code that resets the force, implement steric repulsion
void HardSphere::interact_compute (
		struct Particle const * const particle,
		double const L,
		double const W,
		double const H)
{
	struct Particle const * const that = particle;
	if (that == this) {
		return;
	}
	if (!(that->_feat_ & BDX_FEAT_HS)) {
		fprintf(stderr, "%s\n", "HardSphere::interact_compute: UXConfigError");
		util::clearall();
		util::quit();
	}
	struct HardSphere const * const other = (struct HardSphere const*) particle;
	double const rep = (0.5 * (this->_repulsionHS_ + other->_repulsionHS_));
	double const contact = this->contact(that);
	double const contact2 = (contact * contact);
	double const dx = this->MinImageX(that, L);
	double const dy = this->MinImageY(that, W);
	double const dz = this->MinImageZ(that, H);
	double const r2 = (
			(dx * dx) +
			(dy * dy) +
			(dz * dz)
	);
	double F_x = 0.0;
	double F_y = 0.0;
	double F_z = 0.0;
	if (contact2 > r2) {
		double const r = sqrt(r2);
		double const r_inv = (1.0 / r);
		double const F = rep * r_inv;
		F_x = F;
		F_y = F;
		F_z = F;
		F_x *= dx;
		F_y *= dy;
		F_z *= dz;
	} else {
		F_x = 0;
		F_y = 0;
		F_z = 0;
	}
	this->F_x += F_x;
	this->F_y += F_y;
	this->F_z += F_z;
}

/*

BDX                                             December 31, 2023

Copyright (C) 2023 Misael Diaz-Maldonado

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
source: src/HardSphere.cpp

References:
[0] A Koenig and B Moo, Accelerated C++ Practical Programming by Example.
[1] MP Allen and DJ Tildesley, Computer Simulation of Liquids.
[2] S Kim and S Karrila, Microhydrodynamics.

*/
