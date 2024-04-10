#include "util.h"
#include "Vector.h"
#include "BDXObject.h"
#include "BoundingBox.h"

BoundingBox::BoundingBox (Vector *r,
			  double const l,
			  double const w,
			  double const h):
			  BDXObject(r),
			  _length_(l),
			  _width_(w),
			  _height_(h)
{
	return;
}

double BoundingBox::length() const
{
	return this->_length_;
}

double BoundingBox::width() const
{
	return this->_width_;
}

double BoundingBox::height() const
{
	return this->_height_;
}

void *BoundingBox::operator new (size_t size)
{
	return util::malloc(size);
}

void BoundingBox::operator delete (void *p)
{
	p = util::free(p);
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
source: src/box/BoundingBox.cpp

References:
[0] A Koenig and B Moo, Accelerated C++ Practical Programming by Example.
[1] MP Allen and DJ Tildesley, Computer Simulation of Liquids.
[2] S Kim and S Karrila, Microhydrodynamics.

*/
