#ifndef GUARD_BDX_VECTOR_H
#define GUARD_BDX_VECTOR_H

struct Vector {
	double x;
	double y;
	double z;
	Vector();
	Vector(double const x, double const y, double const z);
	void copy(const Vector *vector);
	void *operator new(size_t size);
	void operator delete(void *p);
	void txt(void *stream) const;
	double norm2();
	void unit();
	void zero();
};

namespace vector {
	void sub(Vector *w, const Vector *u, const Vector *v);
	void cross(Vector *w, const Vector *u, const Vector *v);
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
source: include/Vector.h

References:
[0] A Koenig and B Moo, Accelerated C++ Practical Programming by Example.
[1] MP Allen and DJ Tildesley, Computer Simulation of Liquids.
[2] S Kim and S Karrila, Microhydrodynamics.

*/
