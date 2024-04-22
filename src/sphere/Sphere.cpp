#include "os.h"
#include "util.h"
#include "ID.h"
#include "Kind.h"
#include "Vector.h"
#include "List.h"
#include "Sphere.h"

Sphere::Sphere (Vector *r,
		Vector *u,
		Vector *E,
		Vector *d,
		Vector *F,
		Vector *T,
		List *list,
		ID *id,
		Kind *kind,
		double const a):
		Particle(r, u, E, d, F, T, list, id, kind, a)
{
	return;
}

void Sphere::ia (const Particle *particle)
{
	const Particle *that = particle;
	const Kind *kind = that->kind;
	enum kind const k = kind->k();
	switch(k){
		case SPHERE:
		os::print("sphere-sphere interaction\n");
		break;
		case JANUS:
		os::print("sphere-janus interaction\n");
		break;
		case SPHEROID:
		os::print("sphere-spheroid interaction\n");
		break;
		case CHIRAL:
		os::print("sphere-chiral interaction\n");
		break;
		default:
		os::print("no interaction\n");
	}
}

void *Sphere::operator new (size_t size)
{
	return util::malloc(size);
}

void Sphere::operator delete (void *p)
{
	p = util::free(p);
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
source: src/sphere/Sphere.cpp

References:
[0] A Koenig and B Moo, Accelerated C++ Practical Programming by Example.
[1] MP Allen and DJ Tildesley, Computer Simulation of Liquids.
[2] S Kim and S Karrila, Microhydrodynamics.

*/
