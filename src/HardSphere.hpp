#ifndef BDX_DEMO_HARD_SPHERE_HPP
#define BDX_DEMO_HARD_SPHERE_HPP

#include "util.hpp"
#include "Particle.hpp"

struct HardSphere : Particle 
{
	double _repulsionHS_;
	HardSphere(
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
		);
	void *operator new(size_t size);
	void operator delete(void *p);
	void HS(struct Particle const * const Particle,
			double const L,
			double const W,
			double const H);
	void interact_compute(struct Particle const * const Particle,
			double const L,
			double const W,
			double const H);
};

#endif

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
source: Particle.hpp

References:
[0] A Koenig and B Moo, Accelerated C++ Practical Programming by Example.
[1] MP Allen and DJ Tildesley, Computer Simulation of Liquids.
[2] S Kim and S Karrila, Microhydrodynamics.

*/
