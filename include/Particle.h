#ifndef GUARD_BDX_PARTICLE_H
#define GUARD_BDX_PARTICLE_H

#include "BDXObject.h"

struct ID;
struct Kind;
struct List;
struct Vector;

struct Particle : BDXObject
{
	Vector *u = NULL;
	Vector *E = NULL;
	Vector *d = NULL;
	Vector *F = NULL;
	Vector *T = NULL;
	List *list = NULL;
	ID *id = NULL;
	Kind *kind = NULL;
	double __radius__ = 1.0;
	double __translational_mobility_scaling__ = 1.0;
	double __rotational_mobility_scaling__ = 1.0;
	Particle(Vector *r,
		 Vector *u,
		 Vector *E,
		 Vector *d,
		 Vector *F,
		 Vector *T,
		 List *list,
		 ID *id,
		 Kind *kind,
		 double const a);
	virtual void ia(const Particle *particle) = 0;
	void *operator new(size_t size);
	void operator delete(void *p);
	double _rotational_mobility_scaling_() const;
	double _translational_mobility_scaling_() const;
	void _updatePositionVectorComponent_(double *x,
					     double const F_x,
					     double const mobility);
	void _translate_(double const mobility);
	void _rotate_(double const mobility);
	void _orient_(double const mobility);
	void buildVerletList(Particle **begin, Particle **end);
	void BrownianMotion();
	void txt(void *stream) const;
	double radius() const;
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
source: include/Particle.h

References:
[0] A Koenig and B Moo, Accelerated C++ Practical Programming by Example.
[1] MP Allen and DJ Tildesley, Computer Simulation of Liquids.
[2] S Kim and S Karrila, Microhydrodynamics.

*/
