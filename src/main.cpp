#include <cstdio>
#include <cstring>
#include "bdx.hpp"
#include "util.hpp"
#include "HardSphere.hpp"
#include "Handler.hpp"

int main (void)
{
	struct Random random = {};
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

	struct Handler *handler = new Handler(BDX_NUM_PARTICLES, particles);
	if (!handler) {
		fprintf(stderr, "%s\n", "BDX: HandlerMallocError");
		util::clearall();
		util::quit();
	}

	// initialization
	memset(particles, 0, sz);
	for (long i = 0; i != BDX_NUM_PARTICLES; ++i) {
		long const feat = BDX_FEAT_HS;
		double const x = 0;
		double const y = 0;
		double const z = 0;
		double const radius = 1.0;
		double const repulsionHS = 1.0;
		double const r = radius;
		double const dt = time_step;

		struct Particle *particle = new HardSphere(
			feat,
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

		particles[i] = particle;
	}

	// main BDX loop
	for (long step = 0; step != num_steps; ++step) {
		handler->interact_compute();
		handler->BrownianForce(&random);
		handler->BrownianShift();
		handler->translate();
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
