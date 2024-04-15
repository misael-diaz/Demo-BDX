#include "util.h"
#include "BDX.h"
#include "Handler.h"
#include "System.h"
#include "Vector.h"
#include "Random.h"
#include "Particle.h"
#include "Brownian.h"

Brownian::Brownian ()
{
	return;
}

void Brownian::bind (System *system)
{
	this->system = system;
}

void *Brownian::operator new (size_t size)
{
	return util::malloc(size);
}

void Brownian::operator delete (void *p)
{
	p = util::free(p);
}

static void BrownianForce (double *x, const double *r)
{
	*x = *r;
}

void Brownian::generate ()
{
	Random *rand = this->system->app->random;
	Handler *h = this->system->handler;
	for (Particle **particles = h->begin(); particles != h->end(); ++particles) {
		Particle *particle = *particles;
		double const x = rand->fetch();
		double const y = rand->fetch();
		double const z = rand->fetch();
		BrownianForce(&particle->F->x, &x);
		BrownianForce(&particle->F->y, &y);
		BrownianForce(&particle->F->z, &z);
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
source: src/Brownian/Brownian.cpp

References:
[0] A Koenig and B Moo, Accelerated C++ Practical Programming by Example.
[1] MP Allen and DJ Tildesley, Computer Simulation of Liquids.
[2] S Kim and S Karrila, Microhydrodynamics.

*/
