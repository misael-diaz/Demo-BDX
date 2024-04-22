#include "util.h"
#include "Driver.h"
#include "Brownian.h"
#include "Handler.h"
#include "Particle.h"
#include "System.h"
#include "BDX.h"

Driver::Driver ()
{
	return;
}

void Driver::bind (BDX *app)
{
	this->app = app;
}

void *Driver::operator new (size_t size)
{
	return util::malloc(size);
}

void Driver::operator delete (void *p)
{
	p = util::free(p);
}

void Driver::BrownianMotion ()
{
	struct Brownian *Brownian = this->app->system->Brownian;
	Brownian->generate();
	Handler *h = this->app->system->handler;
	for (Particle **particles = h->begin(); particles != h->end(); ++particles) {
		Particle *p = *particles;
		p->BrownianMotion();
	}
}

void Driver::contain ()
{
	System *system = this->app->system;
	system->contain();
}

void Driver::buildVerletList ()
{
	Handler *h = this->app->system->handler;
	for (Particle **particles = h->begin(); particles != h->end(); ++particles) {
		Particle *p = *particles;
		p->buildVerletList(h->begin(), h->end());
	}
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
source: src/driver/Driver.cpp

References:
[0] A Koenig and B Moo, Accelerated C++ Practical Programming by Example.
[1] MP Allen and DJ Tildesley, Computer Simulation of Liquids.
[2] S Kim and S Karrila, Microhydrodynamics.

*/
