#include <cstdio>
#include <cstdlib>
#include <cmath>
#include "util.hpp"
#include "Handler.hpp"

Handler::Handler (
			long const num_bins,
			long const num_bins_x,
			long const num_bins_y,
			long const num_bins_z,
			long const num_particles,
			double const radius_cutoff,
			struct Bin * const * const bins,
			struct Particle * const * const particles,
			struct Random * const random,
			struct Box * const box
		)
{
	this->_num_bins_ = num_bins;
	this->_num_bins_x_ = num_bins_x;
	this->_num_bins_y_ = num_bins_y;
	this->_num_bins_z_ = num_bins_z;
	this->_num_particles_ = num_particles;
	this->_radius_cutoff_ = radius_cutoff;
	this->bins = bins;
	this->particles = particles;
	this->random = random;
	this->box = box;
	this->__partitioned__ = false;
}

void *Handler::operator new (size_t size)
{
	return util::malloc(size);
}

void Handler::operator delete (void *p)
{
	p = util::free(p);
}


void Handler::__kernel_interact_compute__ (
		struct Particle * const particle,
		struct Bin const * const bin)
{
	for (long idx = 0; idx != bin->size(); ++idx) {
		long const neigh_id = bin->_store_[idx];
		struct Particle const * const neighbor = (
			this->particles[neigh_id]
		);
		particle->interact_compute(
			neighbor,
			this->box->length(),
			this->box->width(),
			this->box->height(),
			this->_radius_cutoff_
		);
	}
}

void Handler::__partition_interact_compute__ (
		struct Particle * const particle,
		long const i,
		long const j,
		long const k)
{
	long const num_bins = this->_num_bins_;
	long const num_bins_x = this->_num_bins_x_;
	long const num_bins_y = this->_num_bins_y_;
	double const box_length = this->box->length();
	double const radius_cutoff = this->_radius_cutoff_;
	double const num_bins_x_f64 = (double) num_bins_x;
	double const cell_length = (box_length / num_bins_x_f64);
	long const span = ((long) ((radius_cutoff / cell_length)));
	long const beg = -span;
	long const cnt = (2L * span + 1L);
	long const msk = (num_bins_x - 1L);
	for (long duno = 0; duno != cnt; ++duno) {
		long const du = duno + beg;
		long const u = ((i + du) & msk);
		for (long dvno = 0; dvno != cnt; ++dvno) {
			long const dv = dvno + beg;
			long const v = ((j + dv) & msk);
			for (long dwno = 0; dwno != cnt; ++dwno) {
				long const dw = dwno + beg;
				long const w = ((k + dw) & msk);
				long const id_bin = (
						(num_bins_x * num_bins_y) * w +
						(num_bins_x) * v +
						u
				);
				if ((0L > id_bin) || (num_bins < id_bin)) {
					fprintf(stderr,
						"%s\n",
						"Handler::__interact_compute_kernel__: "
						"ImplError");
					util::clearall();
					util::quit();
				}
				struct Bin const * const bin = this->bins[id_bin];
				this->__kernel_interact_compute__(particle, bin);
			}
		}
	}
}

void Handler::interact_compute ()
{
	long const num_particles = this->_num_particles_;
	long const num_bins_x = this->_num_bins_x_;
	double const num_bins_x_f64 = (double) num_bins_x;
	double const box_length = this->box->length();
	double const half_length = (0.5 * box_length);
	double const cell_length = (box_length / num_bins_x_f64);
	double const cell_length_inv = (1.0 / cell_length);
	double const cl_inv = cell_length_inv;
	double const hl = half_length;
	for (long id_particle = 0; id_particle != num_particles; ++id_particle) {
		struct Particle * const particle = this->particles[id_particle];
		particle->F_x = 0.0;
		particle->F_y = 0.0;
		particle->F_z = 0.0;
	}

	for (long id_particle = 0; id_particle != num_particles; ++id_particle) {
		struct Particle * const particle = this->particles[id_particle];
		double const x = particle->x;
		double const y = particle->y;
		double const z = particle->z;
		long const i = (x + hl) * cl_inv;
		long const j = (y + hl) * cl_inv;
		long const k = (z + hl) * cl_inv;
		this->__partition_interact_compute__(
			particle,
			i,
			j,
			k
		);
		particle->_ForceExec_ = true;
	}
}

void Handler::translate ()
{
	long const num_particles = this->_num_particles_;
	for (long i = 0; i != num_particles; ++i) {
		struct Particle * const particle = this->particles[i];
		particle->translate();
	}
}

void Handler::partition ()
{
	long const num_bins = this->_num_bins_;
	long const num_bins_x = this->_num_bins_x_;
	long const num_bins_y = this->_num_bins_y_;
	long const num_bins_z = this->_num_bins_z_;
	long const num_particles = this->_num_particles_;
	double const num_bins_x_f64 = (double) num_bins_x;
	double const box_length = this->box->length();
	double const half_length = (0.5 * box_length);
	double const cell_length = (box_length / num_bins_x_f64);
	double const cell_length_inv = (1.0 / cell_length);
	double const cl_inv = cell_length_inv;
	double const hl = half_length;
	if (this->__partitioned__) {
		return;
	}
	// TODO: assert that num_bin_x, num_bin_y, and num_bin_z are exact powers of two
	if (
		(num_particles != num_bins) ||
		((num_bins_x != num_bins_y) || (num_bins_x != num_bins_z))
	) {
		fprintf(stderr, "%s\n", "Handler::partition: UXConfigError");
		util::clearall();
		util::quit();
	}

	for (long id_bin = 0; id_bin != num_bins; ++id_bin) {
		struct Bin * const bin = this->bins[id_bin];
		bin->clear();
	}

	for (long id_particle = 0; id_particle != num_particles; ++id_particle) {
		struct Particle const * const particle = this->particles[id_particle];
		double const x = particle->x;
		double const y = particle->y;
		double const z = particle->z;
		long const i = (x + hl) * cl_inv;
		long const j = (y + hl) * cl_inv;
		long const k = (z + hl) * cl_inv;
		long const id_bin = (
			(num_bins_x * num_bins_y) * k +
			(num_bins_x) * j +
			i
		);
		struct Bin * const bin = this->bins[id_bin];
		bin->push_back(id_particle);
	}
	this->__partitioned__ = true;
}

void Handler::BrownianForce ()
{
	long const num_particles = this->_num_particles_;
	for (long i = 0; i != num_particles; ++i) {
		struct Particle * const particle = this->particles[i];
		particle->BrownianForce(this->random);
	}
}

void Handler::BrownianShift ()
{
	long const num_particles = this->_num_particles_;
	for (long i = 0; i != num_particles; ++i) {
		struct Particle * const particle = this->particles[i];
		particle->BrownianShift();
	}
}

void Handler::update ()
{
	long const num_particles = this->_num_particles_;
	for (long i = 0; i != num_particles; ++i) {
		struct Particle * const particle = this->particles[i];
		particle->update();
	}
	this->__partitioned__ = false;
}

double Handler::mindist () const
{
	double min = INFINITY;
	long const num_particles = this->_num_particles_;
	for (long i = 0; i != (num_particles - 1L); ++i) {
		struct Particle const * const particle = this->particles[i];
		for (long j = (i + 1L); j != num_particles; ++j) {
			struct Particle const * const other_particle = this->particles[j];
			double const sqd = particle->sqdist(other_particle);
			if (min > sqd) {
				min = sqd;
			}
		}
	}
	return sqrt(min);
}

double Handler::mindistp () const
{
	double min = INFINITY;
	double const L = this->box->length();
	double const W = this->box->width();
	double const H = this->box->height();
	double const HL = (0.5 * L);
	double const HW = (0.5 * W);
	double const HH = (0.5 * H);
	double const HL2 = (HL * HL);
	double const HW2 = (HW * HW);
	double const HH2 = (HH * HH);
	long const num_particles = this->_num_particles_;
	for (long i = 0; i != (num_particles - 1L); ++i) {
		struct Particle const * const particle = this->particles[i];
		for (long j = (i + 1L); j != num_particles; ++j) {
			struct Particle const * const other_particle = this->particles[j];
			double const dx = particle->MinImageX(other_particle, L);
			double const dy = particle->MinImageY(other_particle, W);
			double const dz = particle->MinImageZ(other_particle, H);
			double const dx2 = (dx * dx);
			double const dy2 = (dy * dy);
			double const dz2 = (dz * dz);
			if (
				(HL2 < dx2) ||
				(HW2 < dy2) ||
				(HH2 < dz2)
			   ) {
				fprintf(stderr,
					"Handler::mindistp: %s\n",
					"ImplMinImageError");
				util::clearall();
				util::quit();
			}
			double const sqd = particle->MinImage(other_particle, L, W, H);
			if (min > sqd) {
				min = sqd;
			}
		}
	}
	return sqrt(min);
}

void Handler::check_overlap () const
{
	long const num_particles = this->_num_particles_;
	double const L = this->box->length();
	double const W = this->box->width();
	double const H = this->box->height();
	double const HL = (0.5 * L);
	double const HW = (0.5 * W);
	double const HH = (0.5 * H);
	double const HL2 = (HL * HL);
	double const HW2 = (HW * HW);
	double const HH2 = (HH * HH);
	for (long i = 0; i != (num_particles - 1L); ++i) {
		struct Particle const * const particle = this->particles[i];
		for (long j = (i + 1L); j != num_particles; ++j) {
			struct Particle const * const other_particle = this->particles[j];
			double const dx = particle->MinImageX(other_particle, L);
			double const dy = particle->MinImageY(other_particle, W);
			double const dz = particle->MinImageZ(other_particle, H);
			double const dx2 = (dx * dx);
			double const dy2 = (dy * dy);
			double const dz2 = (dz * dz);
			if (
				(HL2 < dx2) ||
				(HW2 < dy2) ||
				(HH2 < dz2)
			   ) {
				fprintf(stderr,
					"Handler::mindistp: %s\n",
					"ImplMinImageError");
				util::clearall();
				util::quit();
			}
			double const sqd = particle->MinImage(other_particle, L, W, H);
			double const contact = particle->contact(other_particle);
			double const contact2 = (contact * contact);
			if (contact2 > sqd) {
				fprintf(stderr,
					"Handler::check_overlap: %s\n",
					"ParticleOverlapError");
				util::clearall();
				util::quit();
			}
		}
	}
	fprintf(stdout, "%s\n", "Handler::check_overlap: DONE");
}

void Handler::PBC ()
{
	double const L = this->box->length();
	double const W = this->box->width();
	double const H = this->box->height();
	long const num_particles = this->_num_particles_;
	for (long i = 0; i != num_particles; ++i) {
		struct Particle * const particle = this->particles[i];
		particle->PBC(L, W, H);
	}
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
source: src/Handler.cpp

References:
[0] A Koenig and B Moo, Accelerated C++ Practical Programming by Example.
[1] MP Allen and DJ Tildesley, Computer Simulation of Liquids.
[2] S Kim and S Karrila, Microhydrodynamics.

*/
