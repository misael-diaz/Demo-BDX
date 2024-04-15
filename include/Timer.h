#ifndef GUARD_BDX_TIMER_H
#define GUARD_BDX_TIMER_H

#include <ctime>

struct BDX;

struct Timer
{
	BDX *app = NULL;
	time_t _begin_ = 0;
	time_t _end_ = 0;
	time_t _walltime_ = 0;
	Timer();
	Timer(time_t const walltime);
	void bind(BDX *app);
	void *operator new(size_t size);
	void operator delete(void *p);
	void etime();
	void begin();
	void end();
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
source: include/Timer.h

References:
[0] A Koenig and B Moo, Accelerated C++ Practical Programming by Example.
[1] MP Allen and DJ Tildesley, Computer Simulation of Liquids.
[2] S Kim and S Karrila, Microhydrodynamics.

*/
