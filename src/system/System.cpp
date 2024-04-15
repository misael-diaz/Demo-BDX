#include "os.h"
#include "util.h"
#include "Brownian.h"
#include "BoundingBox.h"
#include "Handler.h"
#include "Vector.h"
#include "Particle.h"
#include "GFORTRAN.h"
#include "System.h"

System::System (BoundingBox *bb, struct Brownian *Brownian, Handler *handler)
{
	this->bb = bb;
	this->Brownian = Brownian;
	this->handler = handler;
	this->Brownian->bind(this);
}

void System::bind (BDX *app)
{
	this->app = app;
}

void *System::operator new (size_t size)
{
	return util::malloc(size);
}

void System::operator delete (void *p)
{
	p = util::free(p);
}

void container (double *x, double const *len)
{
	const double t = (*x / *len);
	*x -= *len * fanint(&t);
}

void System::contain ()
{
	Handler *h = this->handler;
	for (Particle **particles = h->begin(); particles != h->end(); ++particles) {
		double const l = this->bb->length();
		double const w = this->bb->width();
		double const h = this->bb->height();
		Particle *particle = *particles;
		container(&particle->r->x, &l);
		container(&particle->r->y, &w);
		container(&particle->r->z, &h);
	}
}

/*

BDX                                             December 31, 2023

Copyright (C) 2023 Misael Díaz-Maldonado

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
source: src/system/System.cpp

References:
[0] A Koenig and B Moo, Accelerated C++ Practical Programming by Example.
[1] MP Allen and DJ Tildesley, Computer Simulation of Liquids.
[2] S Kim and S Karrila, Microhydrodynamics.

*/
