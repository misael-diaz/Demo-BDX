#include <cmath>
#include "util.hpp"
#include "Particle.hpp"

Particle::Particle (
			long const feat,
			double const x,
			double const y,
			double const z,
			double const radius,
			double const time_step
		) :
	BDXObject(
			x,
			y,
			z
		 )
{
	this->_feat_ = feat;
	this->dx = 0.0;
	this->dy = 0.0;
	this->dz = 0.0;
	this->F_x = 0.0;
	this->F_y = 0.0;
	this->F_z = 0.0;
	this->_radius_ = radius;
	this->_mobilityLinear_ = (time_step / radius);
	this->_mobilityBrownianLinear_ = sqrt((2.0 * time_step) / radius);
}

void *Particle::operator new (size_t size)
{
	return util::malloc(size);
}

void Particle::operator delete (void *p)
{
	p = util::free(p);
}

void Particle::translate ()
{
	this->x += this->dx;
	this->y += this->dy;
	this->z += this->dz;
}

// TODO: implement by adding the Brownian force to the force vector
void Particle::BrownianForce ()
{
	this->F_x += 0.0;
	this->F_y += 0.0;
	this->F_z += 0.0;
}

double Particle::radius () const
{
	return this->_radius_;
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
source: src/Particle.cpp

References:
[0] A Koenig and B Moo, Accelerated C++ Practical Programming by Example.
[1] MP Allen and DJ Tildesley, Computer Simulation of Liquids.
[2] S Kim and S Karrila, Microhydrodynamics.

*/
