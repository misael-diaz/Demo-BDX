#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include <cmath>
#include <time.h>
#include "util.hpp"

#define HASH ((size_t) 0xdb0f1d1d0dec2023)

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
