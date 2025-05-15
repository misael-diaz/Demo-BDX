#ifndef BDX_DEMO_RANDOM_HPP
#define BDX_DEMO_RANDOM_HPP

#define RANDOM_MXORSHIFT64_ID 0L
#define BDX_ID_RANDOM RANDOM_MXORSHIFT64_ID
#define BDX_PERIOD_RANDOM (0xffffffffffffffffLU)

struct Random {
	long const _id_ = BDX_ID_RANDOM;
	long unsigned const _period_ = BDX_PERIOD_RANDOM;
	long _state_;
	long _seeded_;
	long _cycles_;
	long unsigned _draws_;
	long _cached_;
	double _next_;
	Random();
	void *operator new(size_t size);
	void operator delete(void *p);
	long __xorshift64__();
	double __urand__();
	double __grand__();
	void __seed__();
	double rand();
};

#endif

/*

BDX                                             December 31, 2023

Synopsis:
Pseudo-Random Number Generator PRNG header.

Copyright (C) 2023 Misael Diaz-Maldonado

This file is released under the GNU General Public License version 2 only
as published by the Free Software Foundation.

author: @misael-diaz
source: src/Random.hpp

*/
