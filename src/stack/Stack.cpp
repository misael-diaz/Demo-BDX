#include <cstdio>
#include <cstring>

#include "util.h"
#include "Stack.h"

static void err_create ()
{
	fprintf(stderr, "Stack::create: error\n");
}

static void err_init ()
{
	fprintf(stderr, "Stack::init: error\n");
}

static void err_add ()
{
	fprintf(stderr, "Stack::add: error\n");
}

static void err_copy ()
{
	fprintf(stderr, "Stack::copy: error\n");
}

static void err_grow ()
{
	fprintf(stderr, "Stack::grow: error\n");
}

static void **create (size_t const allot)
{
	size_t const limit = (allot + 1);
	size_t const size = limit * sizeof(void*);
	void *p = Util_Malloc(size);
	if (!p) {
		err_create();
		return NULL;
	}

	memset(p, 0, size);
	return ((void**) p);
}

Stack::Stack (void)
{
	return;
}

size_t Stack::cap () const
{
	return (this->limit - this->begin);
}

size_t Stack::numel () const
{
	return (this->avail - this->begin);
}

void **Stack::data ()
{
	return this->stack;
}

void *Stack::copy () const
{
	size_t const numel = this->numel();
	size_t const size = numel * sizeof(void*);
	void *dst = Util_Malloc(size);
	if (!dst) {
		err_copy();
		return NULL;
	}

	const void *src = ((const void*) this->stack);
	memcpy(dst, src, size);
	return dst;
}

int Stack::grow ()
{
	int rc = 0;
	void *data = Stack::copy();
	if (!data) {
		rc = -1;
		err_grow();
		return rc;
	}

	size_t const numel = this->numel();
	size_t const allot = 2 * numel;
	void **stack = create(allot);
	if (!stack) {
		rc = -1;
		err_grow();
		return rc;
	}

	void *vstack = (void*) stack;
	size_t const size = numel * sizeof(void*);
	memcpy(vstack, data, size);
	data = Util_Free(data);

	this->stack = stack;
	this->begin = stack;
	this->avail = stack + numel;
	this->limit = stack + allot;
	this->allot = allot;
	return rc;
}

int Stack::init ()
{
	int rc = 0;
	this->stack = create(this->allot);
	if (!this->stack) {
		rc = -1;
		err_init();
		return rc;
	}

	this->begin = this->stack;
	this->avail = this->stack;
	this->limit = this->stack + allot;
	return rc;
}

int Stack::add (void *elem)
{
	int rc = 0;
	if (!this->stack) {
		rc = Stack::init();
		if (rc != 0) {
			err_add();
			return rc;
		}
	}

	if (this->avail == this->limit) {
		rc = grow();
		if (rc != 0) {
			err_add();
			return rc;
		}
	}

	*this->avail = elem;
	++this->avail;
	return rc;
}

void *Stack::operator new (size_t size)
{
	return Util_Malloc(size);
}

void Stack::operator delete (void *p)
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
source: src/stack/Stack.cpp

References:
[0] A Koenig and B Moo, Accelerated C++ Practical Programming by Example.
[1] MP Allen and DJ Tildesley, Computer Simulation of Liquids.
[2] S Kim and S Karrila, Microhydrodynamics.

*/
