#ifndef BDX_PRNG_HPP
#define BDX_PRNG_HPP

#define PRNG_GLIBCRANDOM_ID 0L
#define PRNG_MXORSHIFT64_ID 1L

#define BDX_ID_PRNG PRNG_MXORSHIFT64_ID
#define BDX_RAND_PERIOD (0xffffffffffffffffLU)

extern "C" struct Random {
	long id;
	long state;
	long seeded;
	long cycles;
	long unsigned period;
	long unsigned draws;
	long cached;
	double next;
};

#endif

/*

BDX                                             December 31, 2023

Synopsis:
Pseudo-Random Number Generator PRNG header.
Notes:
We use Marsaglia's xorshift64 PRNG for debugging, otherwise we use GLIBC's PRNG for
production runs depending on the value of the global MACRO CFG_XORSHIFT64.

Copyright (C) 2023 Misael Diaz-Maldonado

This file is released under the GNU General Public License version 2 only
as published by the Free Software Foundation.

author: @misael-diaz
source: src/PRNG.hpp

*/
