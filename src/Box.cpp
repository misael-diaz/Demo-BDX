#include <cmath>
#include "util.hpp"
#include "Box.hpp"

Box::Box (
			double const length,
			double const width,
			double const height
		) :
	BDXObject(
			0,
			0,
			0
		 )
{
	this->L = length;
	this->W = width;
	this->H = height;
}

void *Box::operator new (size_t size)
{
	return util::malloc(size);
}

void Box::operator delete (void *p)
{
	p = util::free(p);
}

double Box::length () const
{
	return this->L;
}

double Box::width () const
{
	return this->W;
}

double Box::height () const
{
	return this->H;
}

/*

BDX                                             December 31, 2023

Copyright (C) 2023 Misael Diaz-Maldonado

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
source: src/Box.cpp

References:
[0] A Koenig and B Moo, Accelerated C++ Practical Programming by Example.
[1] MP Allen and DJ Tildesley, Computer Simulation of Liquids.
[2] S Kim and S Karrila, Microhydrodynamics.

*/
