#include <cstdio>
#include <cstdlib>
#include <time.h>
#include <cmath>
#include "util.hpp"
#include "Random.hpp"

Random::Random ()
{
	this->_state_ = 0L;
	this->_seeded_ = 0L;
	this->_cycles_ = 0L;
	this->_draws_ = 0LU;
	this->_cached_ = 0L;
	this->_next_ = 0L;
}

void *Random::operator new (size_t size)
{
	return util::malloc(size);
}

void Random::operator delete (void *p)
{
	p = util::free(p);
}

void Random::__seed__()
{
	long const t = time(NULL);
	this->_state_ = (t)? t : 0xffffffffffffffff;
	this->_seeded_ = 0x0000000000000001L;
}


long Random::__xorshift64__ ()
{
	long x = this->_state_;
	x ^= (x << 13);
	x ^= (x >> 7);
	x ^= (x << 17);
	this->_state_ = x;
	return x;
}

double Random::__urand__ ()
{
	double constexpr offset = (1L << 63);
	double constexpr of = -offset;
	double constexpr sc = 1.0 / (2.0 * of);
	if (!this->_seeded_) {
		this->__seed__();
		this->_draws_ = 0LU;
		this->_cycles_ = 0L;
	} else if (BDX_PERIOD_RANDOM == this->_draws_) {
		this->__seed__();
		this->_draws_ = 0LU;
		this->_cycles_++;
	}

	double const ur = __xorshift64__();
	double const ur_scaled = sc * (of + ur);
	this->_draws_++;
	return ur_scaled;
}

double Random::__grand__ ()
{
	double constexpr inf = (INFINITY);
	if (this->_cached_) {
		this->_cached_ = 0L;
		return this->_next_;
	}
	double r = inf;
	double x = inf;
	double y = inf;
	while (1.0 < r) {
		x = (2.0 * this->__urand__() - 1.0);
		y = (2.0 * this->__urand__() - 1.0);
		r = ((x * x) + (y * y));
	}

	r = sqrt((-2.0 * log(r)) / r);
	this->_next_ = (r * y);
	this->_cached_ = 1L;
	return (r * x);
}

double Random::rand ()
{
	return this->__grand__();
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
source: src/Random.cpp

References:
[0] A Koenig and B Moo, Accelerated C++ Practical Programming by Example.
[1] MP Allen and DJ Tildesley, Computer Simulation of Liquids.
[2] S Kim and S Karrila, Microhydrodynamics.

*/
