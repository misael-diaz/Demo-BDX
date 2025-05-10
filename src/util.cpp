#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <cmath>
#include <time.h>
#include "util.hpp"

#define HASH ((size_t) 0xdb0f1d1d0dec2023)
#define BDX_RAND_PERIOD (0xffffffffffffffffLU)

static long xorshift64 (struct Random * const __restrict__ prng)
{
	long x = prng->state;
	x ^= (x << 13);
	x ^= (x >> 7);
	x ^= (x << 17);
	prng->state = x;
	return x;
}

static void random_SeedPRNG (struct Random * const __restrict__ prng)
{
	long const t = time(NULL);
	prng->state = (t)? t : 0xffffffffffffffff;
	prng->seeded = 0x0000000000000001L;
}

static double random_UniformPseudoRandomNumberGenerator (
		struct Random * const __restrict__ prng)
{
	if (!prng->seeded) {
		random_SeedPRNG(prng);
		prng->draws = 0LU;
		prng->cycles = 0L;
	} else if (BDX_RAND_PERIOD == prng->draws) {
		random_SeedPRNG(prng);
		prng->draws = 0LU;
		prng->cycles++;
	}

	double constexpr offset = (1L << 63);
	double constexpr of = -offset;
	double constexpr sc = 1.0 / (2.0 * of);
	double const ur = xorshift64(prng);
	double const ur_scaled = sc * (of + ur);
	prng->draws++;
	return ur_scaled;
}

static double random_GaussianPseudoRandomNumberGenerator (
		struct Random * const __restrict__ prng)
{
	if (prng->cached) {
		prng->cached = 0L;
		return prng->next;
	}
	double (*uprng)(struct Random * const __restrict__ prng) = (
		random_UniformPseudoRandomNumberGenerator
	);
	double const inf = (INFINITY);
	double r = inf;
	double x = inf;
	double y = inf;
	while (1.0 < r) {
		x = (2.0 * uprng(prng) - 1.0);
		y = (2.0 * uprng(prng) - 1.0);
		r = ((x * x) + (y * y));
	}

	r = sqrt((-2.0 * log(r)) / r);
	prng->next = (r * y);
	prng->cached = 1L;
	return (r * x);
}

static double grand (struct Random * const __restrict__ prng)
{
	return random_GaussianPseudoRandomNumberGenerator(prng);
}

struct m_chain_s {
	struct m_chain_s *prev;
	struct m_chain_s *next;
	void *data;
	size_t hash;
	size_t size;
};

static struct m_chain_s m_chain;
static size_t m_size = 0;
static size_t m_count = 0;

static struct m_chain_s *Util_Chain (struct m_chain_s *node)
{
	struct m_chain_s *next = (m_chain.next)? m_chain.next : NULL;
	if (next) {
		next->prev = node;
	}

	node->next = next;
	node->prev = &m_chain;
	m_chain.next = node;
	return node;
}

static struct m_chain_s *Util_Remove (struct m_chain_s *node)
{
	struct m_chain_s *prev = node->prev;
	struct m_chain_s *next = node->next;
	if (next) {
		next->prev = prev;
	}

	prev->next = next;
	node->next = NULL;
	node->prev = NULL;
	node->data = NULL;
	free(node);
	node = NULL;
	return node;
}

static void *Util_Free (void *p)
{
	if (!p) {
		return NULL;
	}

	struct m_chain_s *node = ((struct m_chain_s*) p) - 1;
	if (node->hash != HASH) {
		fprintf(stderr, "Util_Free: unregistered object error\n");
		return p;
	}

	size_t const size = node->size;
	node = Util_Remove(node);

	m_size -= size;
	--m_count;

	return NULL;
}

static void Util_Clear (void)
{
	struct m_chain_s *next = NULL;
	for (struct m_chain_s *node = m_chain.next; node; node = next) {
		next = node->next;
		void *data = node->data;
		node = (struct m_chain_s*) Util_Free(data);
	}

	m_size = 0;
	m_count = 0;
}

static void *Util_Malloc (size_t const sz)
{
	size_t const size = sizeof(struct m_chain_s) + sz;
	void *p = malloc(size);
	if (!p) {
		fprintf(stderr, "Util_Malloc: %s\n", strerror(errno));
		return NULL;
	}

	struct m_chain_s* node = (struct m_chain_s*) p;
	void *data = (node + 1);

	node = Util_Chain(node);
	node->data = data;
	node->hash = HASH;
	node->size = size;

	m_size += size;
	++m_count;

	return data;
}

void *util::malloc (size_t const sz)
{
	void *p = Util_Malloc(sz);
	if (!p) {
		Util_Clear();
		fprintf(stderr, "util::malloc: %s\n", strerror(errno));
		util::quit();
	}

	return p;
}

void *util::free (void *p)
{
	return Util_Free(p);
}

void util::clearall (void)
{
	Util_Clear();
}

void util::quit (void)
{
	exit(EXIT_FAILURE);
}

double util::random (struct Random * const __restrict__ prng)
{
	return grand(prng);
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
source: src/util.cpp

References:
[0] A Koenig and B Moo, Accelerated C++ Practical Programming by Example.
[1] MP Allen and DJ Tildesley, Computer Simulation of Liquids.
[2] S Kim and S Karrila, Microhydrodynamics.

*/
