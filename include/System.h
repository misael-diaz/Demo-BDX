#ifndef GUARD_BDX_SYSTEM_H
#define GUARD_BDX_SYSTEM_H

struct BoundingBox;
struct Brownian;
struct Handler;
struct BDX;

struct System
{
	BDX *app = NULL;
	BoundingBox *bb = NULL;
	struct Brownian *Brownian = NULL;
	Handler *handler = NULL;
	System(BoundingBox *bb, struct Brownian *Brownian, Handler *handler);
	void bind(BDX *app);
	void *operator new(size_t size);
	void operator delete(void *p);
	void contain();
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
source: include/System.h

References:
[0] A Koenig and B Moo, Accelerated C++ Practical Programming by Example.
[1] MP Allen and DJ Tildesley, Computer Simulation of Liquids.
[2] S Kim and S Karrila, Microhydrodynamics.

*/
