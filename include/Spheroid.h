#ifndef GUARD_BDX_SPHEROID_H
#define GUARD_BDX_SPHEROID_H

#include "Particle.h"

struct ID;
struct Kind;
struct List;
struct Vector;

struct Spheroid : Particle
{
	double _radius_minor_ = 1.0;
	double _radius_major_ = 3.0;
	Spheroid(Vector *r,
	         Vector *u,
	         Vector *E,
	         Vector *d,
	         Vector *F,
	         Vector *T,
	         VerletList *vl,
	         ID *id,
	         Kind *kind,
	         double const a,
		 double const b);
	double radius_minor() const;
	double radius_major() const;
	void ia(const Particle *particle);
	void *operator new(size_t size);
	void operator delete(void *p);
};

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
source: include/Spheroid.h

References:
[0] A Koenig and B Moo, Accelerated C++ Practical Programming by Example.
[1] MP Allen and DJ Tildesley, Computer Simulation of Liquids.
[2] S Kim and S Karrila, Microhydrodynamics.

*/
