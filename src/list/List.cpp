#include "util.h"
#include "Stack.h"
#include "BDXObject.h"
#include "Particle.h"
#include "List.h"

List::List (Stack *stack)
{
	this->stack = stack;
}

size_t List::cap () const
{
	return this->stack->cap();
}

size_t List::numel () const
{
	return this->stack->numel();
}

const Particle **List::begin () const
{
	return ((const Particle**) this->stack->begin());
}

const Particle **List::end () const
{
	return ((const Particle**) this->stack->end());
}

int List::add (Particle *particle)
{
	void *elem = (void*) particle;
	return this->stack->add(elem);
}

void List::clear ()
{
	this->stack->clear();
}

void *List::operator new (size_t size)
{
	return Util_Malloc(size);
}

void List::operator delete (void *p)
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
source: src/list/List.cpp

References:
[0] A Koenig and B Moo, Accelerated C++ Practical Programming by Example.
[1] MP Allen and DJ Tildesley, Computer Simulation of Liquids.
[2] S Kim and S Karrila, Microhydrodynamics.

*/
