#ifndef BDX_DEMO_HANDLER_HPP
#define BDX_DEMO_HANDLER_HPP

#include "Bin.hpp"
#include "Particle.hpp"
#include "System.hpp"
#include "Box.hpp"

struct Handler
{
	struct System * system;
	struct Random * random;
	bool __partitioned__;
	Handler(
			struct System * const system,
			struct Random * const random
	       );
	void *operator new(size_t size);
	void operator delete(void *p);
	double mindist() const;
	double mindistp() const;
	void check_overlap() const;
	void __kernel_interact_compute__(
		struct Particle * const particle,
		struct Bin const * const bin
	);
	void __partition_interact_compute__(
		struct Particle * const particle,
		long const i,
		long const j,
		long const k
	);
	void interact_compute();
	void BrownianForce();
	void BrownianShift();
	void translate();
	void partition();
	void update();
	void PBC();
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
source: Handler.hpp

References:
[0] A Koenig and B Moo, Accelerated C++ Practical Programming by Example.
[1] MP Allen and DJ Tildesley, Computer Simulation of Liquids.
[2] S Kim and S Karrila, Microhydrodynamics.

*/
