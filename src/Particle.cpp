#include <cstdio>
#include <cstdlib>
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
	this->dB_x = 0.0;
	this->dB_y = 0.0;
	this->dB_z = 0.0;
	this->F_x = 0.0;
	this->F_y = 0.0;
	this->F_z = 0.0;
	this->_radius_ = radius;
	this->_mobilityLinear_ = (time_step / radius);
	this->_mobilityBrownianLinear_ = sqrt((2.0 * time_step) / radius);
	this->_ForceExec_ = false;
	this->_BrownianForceExec_ = false;
	this->_BrownianShiftExec_ = false;
	this->_TranslateExec_ = false;
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
	if (this->_TranslateExec_ || !this->_ForceExec_ || !this->_BrownianShiftExec_) {
		fprintf(stderr, "%s\n", "Particle::translate: ImplementationError");
		util::clearall();
		util::quit();
	}

	this->dx = (_mobilityLinear_ * (this->F_x));
	this->dy = (_mobilityLinear_ * (this->F_y));
	this->dz = (_mobilityLinear_ * (this->F_z));

	this->x += ((this->dx) + (this->dB_x));
	this->y += ((this->dy) + (this->dB_y));
	this->z += ((this->dz) + (this->dB_z));

	this->_TranslateExec_ = true;
}

void Particle::BrownianForce (struct Random * const __restrict__ prng)
{
	if (this->_BrownianForceExec_ || !this->_ForceExec_) {
		fprintf(stderr, "%s\n", "Particle::BrownianForce: ImplementationError");
		util::clearall();
		util::quit();
	}

	this->FB_x = util::random(prng);
	this->FB_y = util::random(prng);
	this->FB_z = util::random(prng);

	this->_BrownianForceExec_ = true;
}

void Particle::BrownianShift ()
{
	if (this->_BrownianShiftExec_ || !this->_BrownianForceExec_) {
		fprintf(stderr, "%s\n", "Particle::BrownianShift: ImplementationError");
		util::clearall();
		util::quit();
	}

	this->dB_x = ((this->_mobilityBrownianLinear_) * (this->FB_x));
	this->dB_y = ((this->_mobilityBrownianLinear_) * (this->FB_y));
	this->dB_z = ((this->_mobilityBrownianLinear_) * (this->FB_z));

	this->_BrownianShiftExec_ = true;
}

double Particle::radius () const
{
	return this->_radius_;
}

void Particle::update ()
{
	if (!this->_TranslateExec_) {
		fprintf(stderr, "%s\n", "Particle::update: ImplementationError");
		util::clearall();
		util::quit();
	}

	this->_ForceExec_ = false;
	this->_BrownianForceExec_ = false;
	this->_BrownianShiftExec_ = false;
	this->_TranslateExec_ = false;
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
