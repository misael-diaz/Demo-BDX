#include <cstdio>
#include <cstring>
#include <cstdlib>

#include "util.h"
#include "os.h"
#include "Stack.h"
#include "LMP.h"

static size_t lmp_SizeDataFile (FILE *f)
{
        fseek(f, 0L, SEEK_SET);
        size_t const beg = ftell(f);
        fseek(f, 0L, SEEK_END);
        size_t const end = ftell(f);
        size_t const size = (end - beg);
        fseek(f, 0L, SEEK_SET);
        return size;
}

void *lmp::load (void)
{
	FILE **lmp = (FILE**) util::fopen("data.lmp", "r");
	if (!lmp) {
		os::error("lmp::load: IO ERROR\n");
		return NULL;
	}

	size_t const len = lmp_SizeDataFile(*lmp);
	size_t const sz = (len + 1);
	void *data = util::malloc(sz);
	memset(data, 0, sz);

	size_t const chunk = 1;
	size_t const bytes = fread(data, chunk, len, *lmp);
	if (len != bytes) {
		os::error("lmp::load: IO READ ERROR\n");
		util::fclose(lmp);
		return NULL;
	}

	util::fclose(lmp);
	return data;
}

static size_t lmp_readln (const char **txt)
{
	size_t tokens = 0;
	const char *iter = *txt;
	while (*iter && *iter != '\n') {
		if (*iter == ' ') {
			++tokens;
		}
		++iter;
	}

	if (iter != *txt) {
		++tokens;
	}

	*txt = ++iter;
	return tokens;
}

static void *lmp_TokenizeString (const char **txt)
{
	if (**txt == ' ' || **txt == '\n') {
		++*txt;
	}

	const char *b = *txt;
	while (**txt && **txt != ' ' && **txt != '\n') {
		++*txt;
	}

	const char *e = *txt;
	size_t const len = (e - b);
	size_t const sz = (len + 1);
	void *token = util::malloc(sz);
	if (!token) {
		os::error("lmp_TokenizeString: error\n");
		return NULL;
	}

	memset(token, 0, sz);
	memcpy(token, b, len);
	return token;
}

static void lmp_TokenizeLine (const char **txt, Stack *stack)
{
	while (**txt && **txt != '\n') {

		void *token = lmp_TokenizeString(txt);
		if (!token) {
			util::clearall();
			os::error("lmp_TokenizeLine: error\n");
			exit(EXIT_FAILURE);
		}

		os::print("token: %s\n", (const char*) token);
		double *p = (double*) util::malloc(sizeof(double));
		if (!p) {
			util::clearall();
			os::error("lmp_TokenizeLine: error\n");
			exit(EXIT_FAILURE);
		}

		*p = atof((const char*) token);
		stack->add((void*) p);
		util::free(token);
	}

	if (**txt) {
		++*txt;
	}
}

static size_t lmp_Tokenize (const char **txt, Stack *stack)
{
	size_t count = 0;
	do {
		lmp_TokenizeLine(txt, stack);
		++count;
	} while (**txt && **txt != '\n');

	return count;
}

size_t lmp::parse (const void *data, Stack *stack)
{
	const char *txt[] = {(const char*) data};
	size_t tokens = 0;
	const char *prev = NULL;
	do {
		prev = *txt;
		tokens = lmp_readln(txt);
		os::print("tokens: %zu\n", tokens);
	} while (tokens != 8);

	*txt = prev;

	return lmp_Tokenize(txt, stack);
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
source: src/kind/Kind.cpp

References:
[0] A Koenig and B Moo, Accelerated C++ Practical Programming by Example.
[1] MP Allen and DJ Tildesley, Computer Simulation of Liquids.
[2] S Kim and S Karrila, Microhydrodynamics.

*/
