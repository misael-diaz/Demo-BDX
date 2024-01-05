#include <cstring>

#include "util.h"
#include "Kind.h"

Kind::Kind () : kind(SPHERE)
{
	return;
}

Kind::Kind (kind_t const kind) : kind(kind)
{
	return;
}

kind_t Kind::k() const
{
	return this->kind;
}

const char *Kind::stringify (const Kind *kind)
{
	kind_t const k = kind->k();
	switch(k) {
		case SPHERE:
			return "Sphere";
		case JANUS:
			return "Janus";
		case SPHEROID:
			return "Spheroid";
		case CHIRAL:
			return "Chiral";
		default:
			return "";
	}
}

kind_t Kind::enumerator (const char *kind)
{
	if (!strcmp(kind, "Sphere")) {
		return SPHERE;
	}

	if (!strcmp(kind, "Janus")) {
		return JANUS;
	}

	if (!strcmp(kind, "Spheroid")) {
		return SPHEROID;
	}

	if (!strcmp(kind, "Chiral")) {
		return CHIRAL;
	}

	kind_t unknown = ((kind_t) -1);
	return unknown;
}

void *Kind::operator new (size_t size)
{
	return Util_Malloc(size);
}

void Kind::operator delete (void *p)
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
source: src/kind/Kind.cpp

References:
[0] A Koenig and B Moo, Accelerated C++ Practical Programming by Example.
[1] MP Allen and DJ Tildesley, Computer Simulation of Liquids.
[2] S Kim and S Karrila, Microhydrodynamics.

*/
