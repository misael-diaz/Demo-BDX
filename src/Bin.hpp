#ifndef BDX_DEMO_BIN_HPP
#define BDX_DEMO_BIN_HPP

#include "util.hpp"

#define BDX_CAP_BIN 8L

struct Bin
{
	long  _store_[BDX_CAP_BIN];
	long *_begin_ = _store_;
	long *_avail_ = _store_;
	long *_limit_ = _store_ + BDX_CAP_BIN;
	Bin();
	void push_back(long const particle_id);
	void *operator new(size_t size);
	void operator delete(void *p);
	long size() const;
	void clear();
};

#endif

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
source: Bin.hpp

References:
[0] A Koenig and B Moo, Accelerated C++ Practical Programming by Example.
[1] MP Allen and DJ Tildesley, Computer Simulation of Liquids.
[2] S Kim and S Karrila, Microhydrodynamics.

*/
