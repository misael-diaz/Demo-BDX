#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cerrno>
#include "util.h"

#define HEAD ((size_t) 0xffffffffffffffff)
#define HASH ((size_t) 0xdb0f1d1d0dec2023)

typedef struct m_chain_s {
	struct m_chain_s *prev;
	struct m_chain_s *next;
	void *data;
	size_t hash;
	size_t size;
} m_chain_t;

typedef struct f_chain_s {
	struct f_chain_s *prev;
	struct f_chain_s *next;
	FILE **fhandle;
} f_chain_t;

static m_chain_t m_chain;
static size_t m_size = 0;
static size_t m_count = 0;

static f_chain_t f_chain;
static size_t f_count = 0;

static m_chain_t *Util_Chain (m_chain_t *node)
{
	m_chain_t *next = (m_chain.next)? m_chain.next : NULL;
	if (next) {
		next->prev = node;
	}

	node->next = next;
	node->prev = &m_chain;
	m_chain.next = node;
	return node;
}

static m_chain_t *Util_Remove (m_chain_t *node)
{
	m_chain_t *prev = node->prev;
	m_chain_t *next = node->next;
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

	m_chain_t *node = ((m_chain_t*) p) - 1;
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
	m_chain_t *next = NULL;
	for (m_chain_t *node = m_chain.next; node; node = next) {
		next = node->next;
		void *data = node->data;
		node = (m_chain_t*) Util_Free(data);
	}

	m_size = 0;
	m_count = 0;
}

static void *Util_Malloc (size_t const sz)
{
	size_t const size = sizeof(m_chain_t) + sz;
	void *p = malloc(size);
	if (!p) {
		fprintf(stderr, "Util_Malloc: %s\n", strerror(errno));
		return NULL;
	}

	m_chain_t* node = (m_chain_t*) p;
	void *data = (node + 1);

	node = Util_Chain(node);
	node->data = data;
	node->hash = HASH;
	node->size = size;

	m_size += size;
	++m_count;

	return data;
}

char *Util_CopyString (const char *string)
{
	size_t const len = strlen(string);
	size_t const sz = (len + 1);
	void *ptr = Util_Malloc(sz);
	if (!ptr) {
		fprintf(stderr, "Util_CopyString: error\n");
		return NULL;
	}

	const char *src = string;
	char *dst = (char*) ptr;
	return strcpy(dst, src);
}

static f_chain_t *Util_ChainFile (f_chain_t *node)
{
	f_chain_t *next = (f_chain.next)? f_chain.next : NULL;
	if (next) {
		next->prev = node;
	}

	node->next = next;
	node->prev = &f_chain;
	f_chain.next = node;
	return node;
}

static void *Util_CloseFile (void *vfhandle)
{
	if (!vfhandle) {
		return vfhandle;
	}

	f_chain_t *node = (((f_chain_t*) vfhandle) - 1);
	FILE **fhandle = node->fhandle;
	if (fhandle && *fhandle) {
		int rc = fclose(*fhandle);
		if (rc) {
			fprintf(stderr, "Util_CloseFile: %s\n", strerror(errno));
		}
	}

	f_chain_t* prev = node->prev;
	f_chain_t* next = node->next;
	if (next) {
		next->prev = prev;
	}

	prev->next = next;
	node->prev = NULL;
	node->next = NULL;
	node->fhandle = NULL;
	void *vnode = (void *) node;
	vnode = Util_Free(vnode);
	node = NULL;

	--f_count;

	return NULL;
}

static void Util_CloseFiles (void)
{
	f_chain_t *next = NULL;
	for (f_chain_t *node = f_chain.next; node; node = next) {
		next = node->next;
		void *vfhandle = node->fhandle;
		node = (f_chain_t*) Util_CloseFile(vfhandle);
	}

	f_count = 0;
}

static void *Util_OpenFile (const char *filename, const char *mode)
{
	FILE *file = fopen(filename, mode);
	if (!file) {
		fprintf(stderr, "Util_OpenFile: %s\n", strerror(errno));
		return NULL;
	}

	size_t const size = sizeof(f_chain_t) + sizeof(FILE**);
	void* vnode = (f_chain_t*) Util_Malloc(size);
	if (!vnode) {
		fclose(file);
		fprintf(stderr, "Util_OpenFile: malloc error\n");
		return NULL;
	}

	memset(vnode, 0, size);
	f_chain_t *node = (f_chain_t*) vnode;
	node = Util_ChainFile(node);
	void *vfhandle = (node + 1);
	FILE **fhandle = (FILE**) vfhandle;
	*fhandle = file;
	node->fhandle = fhandle;

	++f_count;

	return node->fhandle;
}

void *util::fopen (const char *filename, const char *mode)
{
	void *p = Util_OpenFile(filename, mode);
	if (!p) {
		Util_CloseFiles();
		Util_Clear();
		fprintf(stderr, "util::fopen: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	return p;
}

void *util::fclose (void *vfhandle)
{
	return Util_CloseFile(vfhandle);
}

void util::fcloseall (void)
{
	Util_CloseFiles();
}

void *util::malloc (size_t const sz)
{
	void *p = Util_Malloc(sz);
	if (!p) {
		Util_CloseFiles();
		Util_Clear();
		fprintf(stderr, "util::malloc: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
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

char *util::strcpy (const char *string)
{
	char *p = Util_CopyString(string);
	if (!p) {
		Util_CloseFiles();
		Util_Clear();
		fprintf(stderr, "util::strcpy: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	return p;
}

/*

BDX                                             December 31, 2023

Copyright (C) 2023 Misael Díaz-Maldonado
Copyright (C) 2024 UCF-Research Group

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
source: src/util/util.cpp

References:
[0] A Koenig and B Moo, Accelerated C++ Practical Programming by Example.
[1] MP Allen and DJ Tildesley, Computer Simulation of Liquids.
[2] S Kim and S Karrila, Microhydrodynamics.

*/
