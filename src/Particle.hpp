#ifndef GUARD_BDX_PARTICLE_HPP
#define GUARD_BDX_PARTICLE_HPP

#include "util.hpp"
#include "BDXObject.hpp"

struct Particle : BDXObject
{
	long _feat_;
	/* displacement vector */
	double dx;
	double dy;
	double dz;
	/* force vector */
	double F_x;
	double F_y;
	double F_z;
	double _radius_;
	double _mobilityLinear_;
	double _mobilityBrownianLinear_;
	Particle(
			long const feat,
			double const x,
			double const y,
			double const z,
			double const radius,
			double const time_step
		);
	void *operator new(size_t size);
	void operator delete(void *p);
	double radius() const;
	virtual void interact_compute(struct Particle const * const Particle) = 0;
	void BrownianForce();
	void translate();
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
