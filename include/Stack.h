#ifndef GUARD_BDX_STACK_H
#define GUARD_BDX_STACK_H

struct Stack
{
	void **__stack__ = NULL;
	void **__begin__ = NULL;
	void **__avail__ = NULL;
	void **__limit__ = NULL;
	size_t __allot__ = 8;
	size_t __size__ = 0;
	void _init_();
	void *_copy_() const;
	size_t _bytes_ () const;
	void _grow_();
	Stack(void);
	size_t cap() const;
	size_t numel() const;
	void add(void *elem);
	void clear();
	void **begin();
	void **end();
	void *operator new(size_t size);
	void operator delete(void *p);
};

#endif

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
source: include/Stack.h

References:
[0] A Koenig and B Moo, Accelerated C++ Practical Programming by Example.
[1] MP Allen and DJ Tildesley, Computer Simulation of Liquids.
[2] S Kim and S Karrila, Microhydrodynamics.

*/
