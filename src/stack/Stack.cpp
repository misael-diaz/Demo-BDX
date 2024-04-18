#include <cstring>
#include <cstdlib>

#include "os.h"
#include "util.h"
#include "Stack.h"

static void **create (size_t const allot)
{
	size_t const limit = (allot + 1);
	size_t const size = limit * sizeof(void*);
	void *p = util::malloc(size);
	memset(p, 0, size);
	return ((void**) p);
}

Stack::Stack (void)
{
	return;
}

size_t Stack::cap () const
{
	return (this->__limit__ - this->__begin__);
}

size_t Stack::numel () const
{
	return (this->__avail__ - this->__begin__);
}

size_t Stack::_bytes_ () const
{
	return this->__size__;
}

void Stack::clear ()
{
	if (!this->__stack__) {
		return;
	}

	void *vstack = (void*) this->__stack__;
	size_t const bytes = this->_bytes_();
	memset(vstack, 0, bytes);
	this->__avail__ = this->__begin__;
	this->__size__ = 0;
}

void **Stack::begin ()
{
	return this->__begin__;
}

void **Stack::end ()
{
	return this->__avail__;
}

void *Stack::_copy_ () const
{
	size_t const numel = this->numel();
	size_t const size = numel * sizeof(void*);
	void *dst = util::malloc(size);
	const void *src = ((const void*) this->__stack__);
	memcpy(dst, src, size);
	return dst;
}

void Stack::_grow_ ()
{
	void *data = this->_copy_();
	size_t const numel = this->numel();
	size_t const allot = 2 * numel;
	void **stack = create(allot);

	void *vstack = (void*) stack;
	size_t const size = numel * sizeof(void*);
	memcpy(vstack, data, size);
	data = util::free(data);

	this->__stack__ = stack;
	this->__begin__ = stack;
	this->__avail__ = stack + numel;
	this->__limit__ = stack + allot;
	this->__allot__ = allot;
}

void Stack::_init_ ()
{
	this->__stack__ = create(this->__allot__);
	this->__begin__ = this->__stack__;
	this->__avail__ = this->__stack__;
	this->__limit__ = this->__stack__ + this->__allot__;
}

void Stack::add (void *elem)
{
	if (!this->__stack__) {
		this->_init_();
	}

	if (this->__avail__ == this->__limit__) {
		this->_grow_();
	}

	*this->__avail__ = elem;
	++this->__avail__;
	this->__size__ += sizeof(void*);
}

void *Stack::operator new (size_t size)
{
	return util::malloc(size);
}

void Stack::operator delete (void *p)
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
source: src/stack/Stack.cpp

References:
[0] A Koenig and B Moo, Accelerated C++ Practical Programming by Example.
[1] MP Allen and DJ Tildesley, Computer Simulation of Liquids.
[2] S Kim and S Karrila, Microhydrodynamics.

*/
