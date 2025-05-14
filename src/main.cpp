#include <cstdio>
#include <cstring>
#include "bdx.hpp"
#include "sys.hpp"
#include "util.hpp"
#include "HardSphere.hpp"
#include "Handler.hpp"

int main (void)
{
	struct Random random = {
		.id = BDX_ID_PRNG,
		.state = 0L,
		.seeded = 0L,
		.cycles = 0L,
		.period = BDX_RAND_PERIOD,
		.draws = 0LU,
		.cached = 0L,
		.next = 0L,
	};
	struct Random *prng = &random;
	double constexpr time_begin = 0.0;
	double constexpr time_end = 1.0;
	double constexpr time_step = 1.52587890625e-05;
	double constexpr num_steps = ((time_end - time_begin) / time_step);
	size_t const sz = BDX_NUM_PARTICLES * sizeof(struct Particle*);
	struct Particle **particles = (struct Particle**) util::malloc(sz);
	if (!particles) {
		fprintf(stderr, "%s\n", "BDX: ContainerMallocError");
		util::quit();
	}

	struct Box *box = new Box(box_length, box_width, box_height);
	if (!box) {
		fprintf(stderr, "%s\n", "BDX: BoxMallocError");
		util::clearall();
		util::quit();
	}

	struct Handler *handler = new Handler(BDX_NUM_PARTICLES, particles, prng, box);
	if (!handler) {
		fprintf(stderr, "%s\n", "BDX: HandlerMallocError");
		util::clearall();
		util::quit();
	}

	// initialization
	memset(particles, 0, sz);
	for (long id = 0; id != BDX_NUM_PARTICLES; ++id) {
		constexpr long kind = BDX_KIND_HS;
		constexpr long group = 1L;
		constexpr long feat = BDX_FEAT_HS;
		constexpr long msk = BDX_MSK_CELL;
		constexpr long shf = BDX_SHF_CELL;
		long const i = (id & msk);
		long const j = ((id >> shf) & msk);
		long const k = (((id >> shf) >> shf) & msk);
		double const i_f64 = i;
		double const j_f64 = j;
		double const k_f64 = k;
		double const x = (((i_f64 * cl) + cc) - hl);
		double const y = (((j_f64 * cl) + cc) - hl);
		double const z = (((k_f64 * cl) + cc) - hl);
		double const radius = 1.0;
		double const repulsionHS = 1.0;
		double const r = radius;
		double const dt = time_step;

		struct Particle *particle = new HardSphere(
			kind,
			group,
			feat,
			id,
			x,
			y,
			z,
			r,
			dt,
			repulsionHS
		);

		if (!particle) {
			fprintf(stderr, "%s\n", "BDX: ParticleMallocError");
			util::clearall();
			util::quit();
		}

		particles[id] = particle;
	}

	double constexpr contact_distance_particles = 2.0;
	double const min_distance_particles = handler->mindist();
	if (min_distance_particles < contact_distance_particles) {
		fprintf(stderr, "%s\n", "BDX: ParticleOverlapError");
		fprintf(stderr, "BDX: min particle-distance: %lf\n", handler->mindist());
		util::clearall();
		util::quit();
	}

	double const min_image_distance_particles = handler->mindistp();
	if (min_image_distance_particles < contact_distance_particles) {
		fprintf(stderr, "%s\n", "BDX: ParticleOverlapError");
		fprintf(stderr,
			"BDX: min particle-distance: %lf\n",
			min_image_distance_particles);
		util::clearall();
		util::quit();
	}

	handler->check_overlap();

	double mindist = 0;
	if (min_distance_particles > min_image_distance_particles) {
		mindist = min_image_distance_particles;
	} else {
		mindist = min_distance_particles;
	}

	fprintf(stdout, "BDX: min particle-distance: %lf\n", mindist);

	// main BDX loop
	for (long step = 0; step != num_steps; ++step) {
		handler->interact_compute();
		handler->BrownianForce();
		handler->BrownianShift();
		handler->translate();
		handler->PBC();
		handler->update();
	}

	util::clearall();
	fprintf(stdout, "%s\n", "BDX: DONE");
	return 0;
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
source: src/main.cpp

References:
[0] A Koenig and B Moo, Accelerated C++ Practical Programming by Example.
[1] MP Allen and DJ Tildesley, Computer Simulation of Liquids.
[2] S Kim and S Karrila, Microhydrodynamics.

*/
