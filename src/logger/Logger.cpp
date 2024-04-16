#include <cstdio>
#include <cstring>
#include "os.h"
#include "util.h"
#include "Looper.h"
#include "Logger.h"
#include "System.h"
#include "BoundingBox.h"
#include "Particle.h"
#include "Handler.h"
#include "BDX.h"

Logger::Logger ()
{
	return;
}

void Logger::bind (BDX *app)
{
	this->app = app;
}

void *Logger::operator new (size_t size)
{
	return util::malloc(size);
}

void Logger::operator delete (void *p)
{
	p = util::free(p);
}

void Logger::params () const
{
	BoundingBox *bb = this->app->system->bb;
	Handler *handler = this->app->system->handler;
	constexpr char PostProcessingBDXParamsFile[] = "ppBDXParams.txt";
	FILE **f = (FILE**) util::fopen(PostProcessingBDXParamsFile, "w");
	fprintf(*f, "GLOBAL_TIME_START: %.15e\n", GLOBAL_TIME_START);
	fprintf(*f, "GLOBAL_TIME_END: %.15e\n", GLOBAL_TIME_END);
	fprintf(*f, "GLOBAL_TIME_STEP: %.15e\n", GLOBAL_TIME_STEP);
	fprintf(*f, "SYSTEM_BOX_LENGTH: %.15e\n", bb->length());
	fprintf(*f, "SYSTEM_BOX_WIDTH: %.15e\n", bb->width());
	fprintf(*f, "SYSTEM_BOX_HEIGHT: %.15e\n", bb->height());
	fprintf(*f, "NUM_PARTICLES: %zu\n", handler->numel());
	util::fclose(f);
}

void Logger::txt () const
{
	constexpr char name[] = "particles-";
	constexpr char ext[] = ".txt";
	char anum[16];
	memset(anum, 0, 16);
	Looper *looper = this->app->looper;
	size_t const step = looper->step();
	sprintf(anum, "%015zu", step);
	constexpr size_t len = 1 + (strlen(name) + strlen(ext) + 16);
	char filename[len];
	filename[0] = 0;
	strcat(filename, name);
	strcat(filename, anum);
	strcat(filename, ext);

	FILE **stream = (FILE**) util::fopen(filename, "w");
	Handler *h = this->app->system->handler;
	for (Particle **particles = h->begin(); particles != h->end(); ++particles) {
		Particle *particle = *particles;
		particle->txt(*stream);
	}

	util::fclose(stream);
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
source: src/logger/Logger.cpp

References:
[0] A Koenig and B Moo, Accelerated C++ Practical Programming by Example.
[1] MP Allen and DJ Tildesley, Computer Simulation of Liquids.
[2] S Kim and S Karrila, Microhydrodynamics.

*/
