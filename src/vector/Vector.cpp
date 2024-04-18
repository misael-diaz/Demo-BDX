#include <cmath>
#include <cstdio>
#include "util.h"
#include "Vector.h"

Vector::Vector() : x(0), y(0), z(0)
{
	return;
}

Vector::Vector(double const x0, double const y0, double const z0) : x(x0), y(y0), z(z0)
{
	return;
}

void Vector::copy (const Vector *vector)
{
	this->x = vector->x;
	this->y = vector->y;
	this->z = vector->z;
}

void *Vector::operator new (size_t size)
{
	return util::malloc(size);
}

void Vector::operator delete (void *p)
{
	p = util::free(p);
}

void Vector::txt (void *stream) const
{
	FILE *f = (FILE*) stream;
	fprintf(f, "%.15e %.15e %.15e ", this->x, this->y, this->z);
}

void Vector::unit ()
{
	double const norm = sqrt(this->x * this->x +
				 this->y * this->y +
				 this->z * this->z);
	this->x /= norm;
	this->y /= norm;
	this->z /= norm;
}

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
source: src/vector/Vector.cpp

References:
[0] A Koenig and B Moo, Accelerated C++ Practical Programming by Example.
[1] MP Allen and DJ Tildesley, Computer Simulation of Liquids.
[2] S Kim and S Karrila, Microhydrodynamics.

*/
