#include <cstdio>
#include <cstdarg>

#include "os.h"

static void os_print (FILE *stream, const char *fmt, va_list args)
{
	vfprintf(stream, fmt, args);
}

void os::print (const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	os_print(stdout, fmt, args);
	va_end(args);
}

void os::error (const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	os_print(stderr, fmt, args);
	va_end(args);
}

void os::prompt (const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	os_print(stderr, fmt, args);
	va_end(args);
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
source: src/os/os.cpp

References:
[0] A Koenig and B Moo, Accelerated C++ Practical Programming by Example.
[1] MP Allen and DJ Tildesley, Computer Simulation of Liquids.
[2] S Kim and S Karrila, Microhydrodynamics.

*/
