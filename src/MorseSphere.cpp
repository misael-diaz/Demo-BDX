#include <cmath>
#include <cstdio>
#include <cstdlib>
#include "bdx.hpp"
#include "util.hpp"
#include "MorseSphere.hpp"

MorseSphere::MorseSphere (
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
			double const epsilonLJ,
			double const epsilonMP,
			double const rangeMP,
			double const equilibriumDistanceMP
		) :
	LennardJonesSphere(
			kind,
			group,
			feat,
			id,
			x,
			y,
			z,
			radius,
			time_step,
			repulsionHS,
			epsilonLJ
		 )
{
	this->_epsilonMP_ = epsilonMP;
	this->_rangeMP_ = rangeMP;
	this->_equilibriumDistanceMP_ = equilibriumDistanceMP;
	this->_sigmaMP_ = (0.5 * radius);
}

void *MorseSphere::operator new (size_t size)
{
	return util::malloc(size);
}

void MorseSphere::operator delete (void *p)
{
	p = util::free(p);
}

// we shift the MP force so that it vanishes (smoothly) at the cutoff radius
void MorseSphere::MP (
		struct Particle const * const particle,
		double const L,
		double const W,
		double const H,
		double const radius_cutoff)
{
	struct Particle const * const that = particle;
	if (!(that->_feat_ & BDX_FEAT_MP)) {
		fprintf(stderr, "%s\n", "MorseSphere::MP: UXConfigError");
		util::clearall();
		util::quit();
	}
	struct MorseSphere const * const other = (
		(struct MorseSphere const*) particle
	);
	double const epsilon = (0.5 * (this->_epsilonMP_ + other->_epsilonMP_));
	double const range = (0.5 * (this->_rangeMP_ + other->_rangeMP_));
	double const equilibriumDistance = (
		0.5 * (this->_equilibriumDistanceMP_ + other->_equilibriumDistanceMP_)
	);
	double const M_d = epsilon;
	double const M_r = range;
	double const M_r_inv = (1.0 / M_r);
	double const r_eq = equilibriumDistance;
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
	double F_x_c = 0.0;
	double F_y_c = 0.0;
	double F_z_c = 0.0;
	if (rc2 > r2) {
		double const r = sqrt(r2);
		double const r_inv = (1.0 / r);
		double const dx_c = (dx * r_inv * rc);
		double const dy_c = (dy * r_inv * rc);
		double const dz_c = (dz * r_inv * rc);
		double const M_exp = exp((r_eq - r) * M_r_inv);
		double const M_exp_c = exp((r_eq - rc) * M_r_inv);

		F_x = -2.0 * M_d * dx * (1.0 - M_exp) * M_exp * (M_r_inv * r_inv);
		F_y = -2.0 * M_d * dy * (1.0 - M_exp) * M_exp * (M_r_inv * r_inv);
		F_z = -2.0 * M_d * dz * (1.0 - M_exp) * M_exp * (M_r_inv * r_inv);

		F_x_c = 2.0 * M_d * dx_c * (1.0 - M_exp_c) * M_exp_c * (M_r_inv * rc_inv);
		F_y_c = 2.0 * M_d * dy_c * (1.0 - M_exp_c) * M_exp_c * (M_r_inv * rc_inv);
		F_z_c = 2.0 * M_d * dz_c * (1.0 - M_exp_c) * M_exp_c * (M_r_inv * rc_inv);

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

void MorseSphere::interact_compute (
		struct Particle const * const particle,
		double const L,
		double const W,
		double const H,
		double const radius_cutoff)
{
	double const rc = radius_cutoff;
	struct Particle const * const that = particle;
	if (that == this) {
		return;
	}
	this->HS(particle, L, W, H, rc);
	if (!(that->_feat_ & BDX_FEAT_LJ)) {
		return;
	}
	this->LJ(particle, L, W, H, rc);
	if (!(that->_feat_ & BDX_FEAT_MP)) {
		return;
	}
	this->MP(particle, L, W, H, rc);
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
source: src/MorseSphere.cpp

References:
[0] A Koenig and B Moo, Accelerated C++ Practical Programming by Example.
[1] MP Allen and DJ Tildesley, Computer Simulation of Liquids.
[2] S Kim and S Karrila, Microhydrodynamics.

*/
