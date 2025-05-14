#include <cstdio>
#include <cstdlib>
#include "util.hpp"
#include "Bin.hpp"

Bin::Bin ()
{
	this->_begin_ = this->_store_;
	this->_avail_ = this->_store_;
	this->_limit_ = this->_store_ + BDX_CAP_BIN;
}

void *Bin::operator new (size_t size)
{
	return util::malloc(size);
}

void Bin::operator delete(void *p)
{
	util::free(p);
}

long Bin::size () const
{
	return ((this->_avail_ - this->_begin_) / sizeof(*this->_begin_));
}

void Bin::clear ()
{
	this->_avail_ = this->_begin_;
}

void Bin::push_back (long const particle_id)
{
	long const id = particle_id;
	if (this->_limit_ == this->_avail_) {
		fprintf(stderr, "%s\n", "Bin::push_back: BinWouldOverrunBufferError");
		util::clearall();
		util::quit();
	}
	*this->_avail_ = id;
	this->_avail_++;
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
source: src/Bin.cpp

References:
[0] A Koenig and B Moo, Accelerated C++ Practical Programming by Example.
[1] MP Allen and DJ Tildesley, Computer Simulation of Liquids.
[2] S Kim and S Karrila, Microhydrodynamics.

*/
