#ifndef BDX_DEMO_PARTICLE_HPP
#define BDX_DEMO_PARTICLE_HPP

#include "util.hpp"
#include "BDXObject.hpp"

struct Particle : BDXObject
{
	long _kind_;
	long _group_;
	long _feat_;
	long _id_;
	/* displacement vector */
	double dx;
	double dy;
	double dz;
	/* Brownian displacement vector */
	double dB_x;
	double dB_y;
	double dB_z;
	/* force vector */
	double F_x;
	double F_y;
	double F_z;
	/* Brownian force vector */
	double FB_x;
	double FB_y;
	double FB_z;
	double _radius_;
	double _mobilityLinear_;
	double _mobilityBrownianLinear_;
	bool _ForceExec_;
	bool _BrownianForceExec_;
	bool _BrownianShiftExec_;
	bool _TranslateExec_;
	Particle(
			long const kind,
			long const group,
			long const feat,
			long const id,
			double const x,
			double const y,
			double const z,
			double const radius,
			double const time_step
		);
	void *operator new(size_t size);
	void operator delete(void *p);
	long kind() const;
	long group() const;
	long feat() const;
	long id() const;
	double radius() const;
	double contact(struct Particle const * const particle) const;
	double sqdist(struct Particle const * const particle) const;
	double MinImageBase(double const dx, double const L) const;
	double MinImageX(struct Particle const * const particle, double const L) const;
	double MinImageY(struct Particle const * const particle, double const W) const;
	double MinImageZ(struct Particle const * const particle, double const H) const;
	double MinImage(struct Particle const * const particle,
			double const L,
			double const W,
			double const H) const;
	virtual void interact_compute(struct Particle const * const Particle,
			double const L,
			double const W,
			double const H,
			double const R) = 0;
	void PBC(double const L, double const W, double const H);
	void BrownianForce(struct Random * const __restrict__ random);
	void BrownianShift();
	void translate();
	void update();
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
source: Particle.hpp

References:
[0] A Koenig and B Moo, Accelerated C++ Practical Programming by Example.
[1] MP Allen and DJ Tildesley, Computer Simulation of Liquids.
[2] S Kim and S Karrila, Microhydrodynamics.

*/
