#ifndef GUARD_BDX_LOOPER_H
#define GUARD_BDX_LOOPER_H

#include <cstddef>

struct BDX;

struct Looper
{
	BDX *app = NULL;
	size_t _step_ = 0;
	size_t const _num_steps_ = (GLOBAL_TIME_END - GLOBAL_TIME_START) /
				    GLOBAL_TIME_STEP;
	Looper();
	void bind(BDX *app);
	void *operator new(size_t size);
	void operator delete(void *p);
	size_t step() const;
	size_t num_steps() const;
	void loop();
};

#endif

/*

BDX                                             December 31, 2023

Copyright (C) 2023 Misael Díaz-Maldonado
Copyright (C) 2024 UCF-Research Group

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
source: include/Looper.h

References:
[0] A Koenig and B Moo, Accelerated C++ Practical Programming by Example.
[1] MP Allen and DJ Tildesley, Computer Simulation of Liquids.
[2] S Kim and S Karrila, Microhydrodynamics.

*/
