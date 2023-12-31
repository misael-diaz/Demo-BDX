#include <cstdio>

#include "util.h"
#include "ID.h"
#include "Kind.h"
#include "Vector.h"
#include "BDXObject.h"
#include "Particle.h"
#include "Spheroid.h"
#include "Chiral.h"

Chiral::Chiral (Vector *r,
		Vector *u,
		Vector *E,
		Vector *d,
		Vector *F,
		Vector *T,
		ID *id,
		Kind *kind,
		double const a,
		double const b,
		double const c):
		Spheroid(r, u, E, d, F, T, id, kind, a, b),
		c(c)
{
	return;
}

double Chiral::chiral () const
{
	return this->c;
}

void Chiral::ia (const Particle *particle)
{
	const Particle *that = particle;
	const Kind *kind = that->kind;
	kind_t const k = kind->k();
	switch(k){
		case SPHERE:
		printf("chiral-sphere interaction\n");
		break;
		case JANUS:
		printf("chiral-janus interaction\n");
		break;
		case SPHEROID:
		printf("chiral-spheroid interaction\n");
		break;
		case CHIRAL:
		printf("chiral-chiral interaction\n");
		break;
		default:
		printf("no interaction\n");
	}
}

void *Chiral::operator new (size_t size)
{
	return Util_Malloc(size);
}

void Chiral::operator delete (void *p)
{
	p = Util_Free(p);
}

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
source: src/chiral/Chiral.cpp

References:
[0] A Koenig and B Moo, Accelerated C++ Practical Programming by Example.
[1] MP Allen and DJ Tildesley, Computer Simulation of Liquids.
[2] S Kim and S Karrila, Microhydrodynamics.

*/
