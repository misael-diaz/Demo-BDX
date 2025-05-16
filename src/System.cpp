#include <cstdio>
#include <cstdlib>
#include <cmath>
#include "util.hpp"
#include "System.hpp"

System::System (
			long const num_bins,
			long const num_bins_x,
			long const num_bins_y,
			long const num_bins_z,
			long const num_particles,
			double const radius_cutoff,
			struct Bin * const * const bins,
			struct Particle * const * const particles,
			struct Box * const box
		)
{
	this->_num_bins_ = num_bins;
	this->_num_bins_x_ = num_bins_x;
	this->_num_bins_y_ = num_bins_y;
	this->_num_bins_z_ = num_bins_z;
	this->_num_particles_ = num_particles;
	this->_radius_cutoff_ = radius_cutoff;
	this->_bins_ = bins;
	this->_particles_ = particles;
	this->_box_ = box;
}

void *System::operator new (size_t size)
{
	return util::malloc(size);
}

void System::operator delete (void *p)
{
	p = util::free(p);
}

struct Box *System::box ()
{
	return this->_box_;
}

struct Bin * const *System::bins ()
{
	return this->_bins_;
}

struct Particle * const *System::particles ()
{
	return this->_particles_;
}

double System::radius_cutoff () const
{
	return this->_radius_cutoff_;
}

long System::num_particles () const
{
	return this->_num_particles_;
}

long System::num_bins_x () const
{
	return this->_num_bins_x_;
}

long System::num_bins_y () const
{
	return this->_num_bins_y_;
}

long System::num_bins_z () const
{
	return this->_num_bins_z_;
}

long System::num_bins () const
{
	return this->_num_bins_;
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
source: src/System.cpp

References:
[0] A Koenig and B Moo, Accelerated C++ Practical Programming by Example.
[1] MP Allen and DJ Tildesley, Computer Simulation of Liquids.
[2] S Kim and S Karrila, Microhydrodynamics.

*/
