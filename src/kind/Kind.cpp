#include <cstdio>
#include <cstring>

#include "util.h"
#include "Kind.h"

Kind::Kind () : kind(kind::SPHERE)
{
	return;
}

Kind::Kind (enum kind const kind) : kind(kind)
{
	return;
}

enum kind Kind::k() const
{
	return this->kind;
}

const char *Kind::stringify (const Kind *kind)
{
	enum kind const k = kind->k();
	switch(k) {
		case kind::SPHERE:
			return "Sphere";
		case kind::JANUS:
			return "Janus";
		case kind::SPHEROID:
			return "Spheroid";
		case kind::CHIRAL:
			return "Chiral";
		default:
			return "";
	}
}

enum kind Kind::enumerator (const char *kind)
{
	if (!strcmp(kind, "Sphere")) {
		return kind::SPHERE;
	}

	if (!strcmp(kind, "Janus")) {
		return kind::JANUS;
	}

	if (!strcmp(kind, "Spheroid")) {
		return kind::SPHEROID;
	}

	if (!strcmp(kind, "Chiral")) {
		return kind::CHIRAL;
	}

	enum kind unknown = ((enum kind) -1);
	return unknown;
}

void *Kind::operator new (size_t size)
{
	return util::malloc(size);
}

void Kind::operator delete (void *p)
{
	p = util::free(p);
}

void Kind::txt (void *stream) const
{
	FILE *f = (FILE*) stream;
	ssize_t const k = ((ssize_t) this->k());
	fprintf(f, "%zd ", k);
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
