#include <cstdio>
#include <cstdlib>
#include <cmath>
#include "sys.hpp"
#include "util.hpp"
#include "Handler.hpp"

Handler::Handler (
			long const num_bins,
			long const num_bins_x,
			long const num_bins_y,
			long const num_bins_z,
			long const num_particles,
			struct Bin * const * const bins,
			struct Particle * const * const particles,
			struct Random * const random,
			struct Box * const box
		)
{
	this->num_bins = num_bins;
	this->num_bins_x = num_bins_x;
	this->num_bins_y = num_bins_y;
	this->num_bins_z = num_bins_z;
	this->num_particles = num_particles;
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

void Handler::interact_compute ()
{
	long const msk = (num_cell_x - 1L);
	for (long id_particle = 0; id_particle != this->num_particles; ++id_particle) {
		struct Particle * const particle = this->particles[id_particle];
		double const x = particle->x;
		double const y = particle->y;
		double const z = particle->z;
		long const i = (x + hl) * cl_inv;
		long const j = (y + hl) * cl_inv;
		long const k = (z + hl) * cl_inv;
		for (long du = -1; du != 2; ++du) {
			long const u = ((i + du) & msk);
			for (long dv = -1; dv != 2; ++dv) {
				long const v = ((j + dv) & msk);
				for (long dw = -1; dw != 2; ++dw) {
					long const w = ((k + dw) & msk);
					long const id_bin = (
							(num_bins_x * num_bins_y) * w +
							(num_bins_x) * v +
							u
					);
					if ((0L > id_bin) || (num_bins < id_bin)) {
						fprintf(stderr,
							"%s\n",
							"Handler::partition: ImplError");
						util::clearall();
						util::quit();
					}
					struct Bin const * const bin = this->bins[id_bin];
					for (long idx = 0; idx != bin->size(); ++idx) {
						long const neigh_id = bin->_store_[idx];
						struct Particle * const neighbor = (
							this->particles[neigh_id]
						);
						particle->interact_compute(
							neighbor,
							this->box->length(),
							this->box->width(),
							this->box->height()
						);
					}
				}
			}
		}
		particle->_ForceExec_ = true;
	}
}

void Handler::translate ()
{
	for (long i = 0; i != this->num_particles; ++i) {
		struct Particle * const particle = this->particles[i];
		particle->translate();
	}
}

void Handler::partition ()
{
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

	for (long id_bin = 0; id_bin != this->num_bins; ++id_bin) {
		struct Bin * const bin = this->bins[id_bin];
		bin->clear();
	}

	for (long id_particle = 0; id_particle != this->num_particles; ++id_particle) {
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
	for (long i = 0; i != this->num_particles; ++i) {
		struct Particle * const particle = this->particles[i];
		particle->BrownianForce(this->random);
	}
}

void Handler::BrownianShift ()
{
	for (long i = 0; i != this->num_particles; ++i) {
		struct Particle * const particle = this->particles[i];
		particle->BrownianShift();
	}
}

void Handler::update ()
{
	for (long i = 0; i != this->num_particles; ++i) {
		struct Particle * const particle = this->particles[i];
		particle->update();
	}
	this->__partitioned__ = false;
}

double Handler::mindist () const
{
	double min = INFINITY;
	for (long i = 0; i != (this->num_particles - 1L); ++i) {
		struct Particle const * const particle = this->particles[i];
		for (long j = (i + 1L); j != this->num_particles; ++j) {
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
	for (long i = 0; i != (this->num_particles - 1L); ++i) {
		struct Particle const * const particle = this->particles[i];
		for (long j = (i + 1L); j != this->num_particles; ++j) {
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
	double const L = this->box->length();
	double const W = this->box->width();
	double const H = this->box->height();
	double const HL = (0.5 * L);
	double const HW = (0.5 * W);
	double const HH = (0.5 * H);
	double const HL2 = (HL * HL);
	double const HW2 = (HW * HW);
	double const HH2 = (HH * HH);
	for (long i = 0; i != (this->num_particles - 1L); ++i) {
		struct Particle const * const particle = this->particles[i];
		for (long j = (i + 1L); j != this->num_particles; ++j) {
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
	for (long i = 0; i != this->num_particles; ++i) {
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
