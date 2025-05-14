#include <cmath>
#include <cstdio>
#include <cstdlib>
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
void HardSphere::interact_compute (struct Particle const * const particle)
{
	struct Particle const * const that = particle;
	if (that == this) {
		return;
	}
	this->F_x = 0;
	this->F_y = 0;
	this->F_z = 0;
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
