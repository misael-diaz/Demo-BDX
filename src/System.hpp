#ifndef BDX_DEMO_SYSTEM_HPP
#define BDX_DEMO_SYSTEM_HPP

#include "Bin.hpp"
#include "Particle.hpp"
#include "Box.hpp"

struct System
{
	long _num_bins_;
	long _num_bins_x_;
	long _num_bins_y_;
	long _num_bins_z_;
	long _num_particles_;
	double _radius_cutoff_;
	struct Bin * const * _bins_;
	struct Particle * const * _particles_;
	struct Box * _box_;
	System(
			long num_bins,
			long const num_bins_x,
			long const num_bins_y,
			long const num_bins_z,
			long const num_particles,
			double const radius_cutoff,
			struct Bin * const * const bins,
			struct Particle * const * const particles,
			struct Box * const box
	       );
	void *operator new(size_t size);
	void operator delete(void *p);
	struct Box *box();
	struct Bin * const *bins();
	struct Particle * const *particles();
	double radius_cutoff() const;
	long num_particles() const;
	long num_bins_x() const;
	long num_bins_y() const;
	long num_bins_z() const;
	long num_bins() const;
};

#endif

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
source: System.hpp

References:
[0] A Koenig and B Moo, Accelerated C++ Practical Programming by Example.
[1] MP Allen and DJ Tildesley, Computer Simulation of Liquids.
[2] S Kim and S Karrila, Microhydrodynamics.

*/
