#include <cmath>
#include <cstdio>
#include <cstdlib>
#include "bdx.hpp"
#include "sys.hpp"
#include "util.hpp"
#include "LennardJonesSphere.hpp"

LennardJonesSphere::LennardJonesSphere (
			long const kind,
			long const group,
			long const feat,
			long const id,
			double const x,
			double const y,
			double const z,
			double const radius,
			double const time_step,
			double const repulsionHS,
			double const epsilonLJ
		) :
	HardSphere(
			kind,
			group,
			feat,
			id,
			x,
			y,
			z,
			radius,
			time_step,
			repulsionHS
		 )
{
	this->_epsilonLJ_ = epsilonLJ;
	this->_sigmaLJ_ = (0.5 * radius);
}

void *LennardJonesSphere::operator new (size_t size)
{
	return util::malloc(size);
}

void LennardJonesSphere::operator delete (void *p)
{
	p = util::free(p);
}

// we shift the LJ force so that it vanishes (smoothly) at the cutoff radius
void LennardJonesSphere::LJ (
		struct Particle const * const particle,
		double const L,
		double const W,
		double const H)
{
	struct Particle const * const that = particle;
	if (!(that->_feat_ & BDX_FEAT_LJ)) {
		fprintf(stderr, "%s\n", "LennardJonesSphere::LJ: UXConfigError");
		util::clearall();
		util::quit();
	}
	// DEV: this is temporary hack so that we can reuse as much code as possible
	if (
			(box_length != L) ||
			(box_width  != W) ||
			(box_height != H)
	   ) {
		fprintf(stderr, "%s\n", "LennardJonesSphere::LJ: UXBoxDimensionError");
		util::clearall();
		util::quit();
	}
	struct LennardJonesSphere const * const other = (
		(struct LennardJonesSphere const*) particle
	);
	double const epsilon = (0.5 * (this->_epsilonLJ_ + other->_epsilonLJ_));
	double const contact = this->contact(that);
	double const sigma = contact;
	double const sigma6 = (
		sigma *
		sigma *
		sigma *
		sigma *
		sigma *
		sigma
	);
	double const kappa = (6.0 * epsilon * sigma6);
	double const radius_cutoff = cell_length;
	double const rc = radius_cutoff;
	double const rc2 = (rc * rc);
	double const rc_inv = (1.0 / rc);
	double const dx = this->MinImageX(that, L);
	double const dy = this->MinImageY(that, W);
	double const dz = this->MinImageZ(that, H);
	double const r2 = (
			(dx * dx) +
			(dy * dy) +
			(dz * dz)
	);
	double F_x = 0.0;
	double F_y = 0.0;
	double F_z = 0.0;
	if (rc2 > r2) {
		double const r = sqrt(r2);
		double const r_inv = (1.0 / r);
		double const r8_inv = (
			r_inv *
			r_inv *
			r_inv *
			r_inv *
			r_inv *
			r_inv *
			r_inv *
			r_inv
		);
		double const rc8_inv = (
			rc_inv *
			rc_inv *
			rc_inv *
			rc_inv *
			rc_inv *
			rc_inv *
			rc_inv *
			rc_inv
		);
		double const dx_c = (dx * r_inv * rc);
		double const dy_c = (dy * r_inv * rc);
		double const dz_c = (dz * r_inv * rc);
		double const F = kappa * r8_inv;
		double const F_c = kappa * rc8_inv;
		double F_x_c = -F_c;
		double F_y_c = -F_c;
		double F_z_c = -F_c;
		F_x = F;
		F_y = F;
		F_z = F;
		F_x *= dx;
		F_y *= dy;
		F_z *= dz;
		F_x_c *= dx_c;
		F_y_c *= dy_c;
		F_z_c *= dz_c;
		F_x += F_x_c;
		F_y += F_y_c;
		F_z += F_z_c;
	} else {
		F_x = 0;
		F_y = 0;
		F_z = 0;
	}
	this->F_x += F_x;
	this->F_y += F_y;
	this->F_z += F_z;
}

void LennardJonesSphere::interact_compute (
		struct Particle const * const particle,
		double const L,
		double const W,
		double const H)
{
	struct Particle const * const that = particle;
	if (that == this) {
		return;
	}
	this->HS(particle, L, W, H);
	if (!(that->_feat_ & BDX_FEAT_LJ)) {
		return;
	}
	this->LJ(particle, L, W, H);
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
source: src/LennardJonesSphere.cpp

References:
[0] A Koenig and B Moo, Accelerated C++ Practical Programming by Example.
[1] MP Allen and DJ Tildesley, Computer Simulation of Liquids.
[2] S Kim and S Karrila, Microhydrodynamics.

*/
