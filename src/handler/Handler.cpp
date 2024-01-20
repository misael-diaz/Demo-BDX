#include "util.h"
#include "Stack.h"
#include "BDXObject.h"
#include "Particle.h"
#include "Handler.h"

Handler::Handler (Stack *stack)
{
	this->stack = stack;
}

size_t Handler::cap () const
{
	return this->stack->cap();
}

size_t Handler::numel () const
{
	return this->stack->numel();
}

Particle **Handler::begin ()
{
	return ((Particle**) this->stack->begin());
}

Particle **Handler::end ()
{
	return ((Particle**) this->stack->end());
}

int Handler::add (Particle *particle)
{
	void *elem = (void*) particle;
	return this->stack->add(elem);
}

void *Handler::operator new (size_t size)
{
	return Util_Malloc(size);
}

void Handler::operator delete (void *p)
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
source: src/handler/Handler.cpp

References:
[0] A Koenig and B Moo, Accelerated C++ Practical Programming by Example.
[1] MP Allen and DJ Tildesley, Computer Simulation of Liquids.
[2] S Kim and S Karrila, Microhydrodynamics.

*/
