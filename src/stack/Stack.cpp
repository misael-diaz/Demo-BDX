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
	return (this->_limit_ - this->_begin_);
}

size_t Stack::numel () const
{
	return (this->_avail_ - this->_begin_);
}

size_t Stack::bytes () const
{
	return this->_size_;
}

void Stack::clear ()
{
	if (!this->_stack_) {
		return;
	}

	void *vstack = (void*) this->_stack_;
	size_t const bytes = this->bytes();
	memset(vstack, 0, bytes);
	this->_avail_ = this->_begin_;
	this->_size_ = 0;
}

void **Stack::begin ()
{
	return this->_begin_;
}

void **Stack::end ()
{
	return this->_avail_;
}

void *Stack::copy () const
{
	size_t const numel = this->numel();
	size_t const size = numel * sizeof(void*);
	void *dst = util::malloc(size);
	const void *src = ((const void*) this->_stack_);
	memcpy(dst, src, size);
	return dst;
}

int Stack::grow ()
{
	int rc = 0;
	void *data = Stack::copy();
	size_t const numel = this->numel();
	size_t const allot = 2 * numel;
	void **stack = create(allot);

	void *vstack = (void*) stack;
	size_t const size = numel * sizeof(void*);
	memcpy(vstack, data, size);
	data = util::free(data);

	this->_stack_ = stack;
	this->_begin_ = stack;
	this->_avail_ = stack + numel;
	this->_limit_ = stack + allot;
	this->_allot_ = allot;
	return rc;
}

int Stack::init ()
{
	int rc = 0;
	this->_stack_ = create(this->_allot_);
	this->_begin_ = this->_stack_;
	this->_avail_ = this->_stack_;
	this->_limit_ = this->_stack_ + this->_allot_;
	return rc;
}

int Stack::add (void *elem)
{
	int rc = 0;
	if (!this->_stack_) {
		rc = Stack::init();
	}

	if (this->_avail_ == this->_limit_) {
		rc = grow();
	}

	*this->_avail_ = elem;
	++this->_avail_;
	this->_size_ += sizeof(void*);
	return rc;
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
