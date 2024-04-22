#include "util.h"
#include "List.h"
#include "Particle.h"
#include "VerletList.h"

VerletList::VerletList (List *list, Vector *displacement) : d(0)
{
	this->__list__ = list;
	this->dr = displacement;
}

size_t VerletList::cap () const
{
	return this->__list__->cap();
}

size_t VerletList::numel () const
{
	return this->__list__->numel();
}

void VerletList::clear ()
{
	this->__list__->clear();
}

Particle **VerletList::begin ()
{
	return this->__list__->begin();
}

Particle **VerletList::end ()
{
	return this->__list__->end();
}

void VerletList::add (Particle *particle)
{
	this->__list__->add(particle);
}

void *VerletList::operator new (size_t size)
{
	return util::malloc(size);
}

void VerletList::operator delete (void *p)
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
source: src/VerletList/VerletList.cpp

References:
[0] A Koenig and B Moo, Accelerated C++ Practical Programming by Example.
[1] MP Allen and DJ Tildesley, Computer Simulation of Liquids.
[2] S Kim and S Karrila, Microhydrodynamics.

*/
