#include <cstdio>
#include <cstring>
#include <cstdlib>

#include "os.h"
#include "util.h"
#include "Stack.h"
#include "ID.h"
#include "Kind.h"
#include "Vector.h"
#include "BDXObject.h"
#include "Particle.h"
#include "Sphere.h"
#include "Janus.h"
#include "Spheroid.h"
#include "Chiral.h"
#include "BoundingBox.h"
#include "Brownian.h"
#include "Handler.h"
#include "System.h"
#include "List.h"

#define COMPILE 0
#define VERBOSE 0
#define ASPECT_RATIO 3.0

void tutil1(void);
void tutil2(void);
void tutil3(void);
void tutil4(void);
void tutil5(void);
void tutil6(void);
void tutil7(void);
void tutil8(void);
void tutil9(void);
void tutil10(void);
void tutil11(void);
void tutil12(void);
void tutil13(void);
void tutil14(void);
void tutil15(void);

#ifdef GXX
Particle *_Particle(Vector *r,
		    Vector *u,
		    Vector *E,
		    Vector *d,
		    Vector *F,
		    List *list,
		    ID *id,
		    Kind *kind,
		    double const a,
		    double const b,
		    double const c)
__attribute__ ((nonnull (1, 2, 3, 4, 5, 6, 7, 8)));
#else
Particle *_Particle(Vector *r,
		    Vector *u,
		    Vector *E,
		    Vector *d,
		    Vector *F,
		    List *list,
		    ID *id,
		    Kind *kind,
		    double const a,
		    double const b,
		    double const c);
#endif

int main ()
{
	tutil1();
	tutil2();
	tutil3();
	tutil4();
	tutil5();
	tutil6();
	tutil7();
	tutil8();
	tutil9();
	tutil10();
	tutil11();
	tutil12();
	tutil13();
	tutil14();
	tutil15();
	Util_Clear();
	return 0;
}

Particle *_Particle (Vector *r,
		     Vector *u,
		     Vector *E,
		     Vector *d,
		     Vector *F,
		     List *list,
		     ID *id,
		     Kind *kind,
		     double const a,
		     double const b,
		     double const c)
{
	Vector *T = NULL;
	Particle *particle = NULL;
	kind_t const k = kind->k();
	switch(k)
	{
		case SPHERE:
		particle = new Sphere(r, u, E, d, F, list, id, kind, a);
		if (!particle) {
			return NULL;
		}

		break;

		case JANUS:
		T = new Vector();
		if (!T) {
			return NULL;
		}

		particle = new Janus(r, u, E, d, F, T, list, id, kind, a);
		if (!particle) {
			return NULL;
		}

		break;

		case SPHEROID:
		T = new Vector();
		if (!T) {
			return NULL;
		}

		particle = new Spheroid(r, u, E, d, F, T, list, id, kind, a, b);
		if (!particle) {
			return NULL;
		}

		break;

		case CHIRAL:
		T = new Vector();
		if (!T) {
			return NULL;
		}

		particle = new Chiral(r, u, E, d, F, T, list, id, kind, a, b, c);
		if (!particle) {
			return NULL;
		}

		break;

		default:
		particle = new Sphere(r, u, E, d, F, list, id, kind, a);
		if (!particle) {
			return NULL;
		}
	}

	return particle;
}

void tutil1 (void)
{
	const char txt[] = "string-literal";
	void *ptr = Util_Malloc(strlen(txt) + 1);

	char *dst = (char*) ptr;
	strcpy(dst, txt);
	printf("%s\n", dst);

	ptr = Util_Free(ptr);
}

void tutil2 (void)
{
	typedef struct {
		double x;
	} data_t;

	data_t data = { .x = 0 };
	void *ptr = Util_Malloc(sizeof(data_t));

	data_t *dst = (data_t*) ptr;
	dst->x = 0.0;

	printf("%f %f\n", data.x, dst->x);

	ptr = Util_Free(ptr);
}

void tutil3 (void)
{
	double *data[] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
	size_t const numel = sizeof(data) / sizeof(double);
	for (size_t i = 0; i != numel; ++i) {

		data[i] = (double*) Util_Malloc(sizeof(double));
		if (!data[i]) {
			Util_Clear();
			return;
		}

		*data[i] = ((double) i);
	}

	double sum = 0;
	for (size_t i = 0; i != numel; ++i) {
		sum += *data[i];
	}

	double const total = 0.5 * (numel - 1.0) * numel;
	if (total != sum) {
		printf("FAIL\n");
	} else {
		printf("PASS\n");
	}

	Util_Clear();
}

void tutil4 (void)
{
	Vector *vector = new Vector();
	delete(vector);
}

void tutil5 (void)
{
	size_t const numel = 8;
	Vector **vectors = (Vector**) Util_Malloc(numel * sizeof(Vector*));
	for (size_t i = 0; i != numel; ++i) {
		vectors[i] = new Vector();
		if (!vectors[i]) {
			break;
		}
	}

	Util_Clear();
}

void tutil6 (void)
{
	Vector *r = new Vector();
	if (!r) {
		Util_Clear();
		return;
	}

	BDXObject *obj = new BDXObject(r);
	delete(obj);
	Util_Clear();
}

#if COMPILE
void tutil7 (void)
{
	ID *id = new ID();
	Kind *kind = new Kind();
	Vector *r = new Vector();
	Particle *particle = new Particle(r, id, kind);
	delete(particle);
	Util_Clear();
}
#else
void tutil7 (void)
{
	return;
}
#endif

#if COMPILE
void tutil8 (void)
{
	size_t const numel = 256;
	size_t const size = numel * sizeof(Particle*);
	Particle **particles = (Particle**) Util_Malloc(size);
	if (!particles) {
		return;
	}

	for (size_t i = 0; i != numel; ++i) {

		ID *id = new ID(i);
		Kind *kind = new Kind();
		double const x = rand();
		double const y = rand();
		double const z = rand();
		Vector *r = new Vector(x, y, z);
		Particle *particle = new Particle(r, id, kind);
		if (!particle) {
			break;
		}

		particles[i] = particle;
	}

	Util_Clear();
}
#else
void tutil8 (void)
{
	return;
}
#endif

void tutil9 (void)
{
	Vector *r = new Vector();
	if (!r) {
		return;
	}

	double const length = 16;
	double const width = 16;
	double const height = 32;
	BoundingBox *bb = new BoundingBox(r, length, width, height);
	delete(bb);
	Util_Clear();
}

#if VERBOSE
void tutil10 (void)
{
	size_t const numel = 256;
	size_t const size = numel * sizeof(Sphere*);
	Sphere **spheres = (Sphere**) Util_Malloc(size);
	if (!spheres) {
		return;
	}

	for (size_t i = 0; i != numel; ++i) {

		ID *id = new ID(i);
		if (!id) {
			break;
		}

		Kind *kind = new Kind();
		if (!kind) {
			break;
		}

		double const x = rand();
		double const y = rand();
		double const z = rand();
		Vector *r = new Vector(x, y, z);
		if (!r) {
			break;
		}

		Vector *u = new Vector();
		if (!u) {
			break;
		}

		Vector *E = new Vector();
		if (!E) {
			break;
		}

		Vector *d = new Vector(0, 0, 1);
		if (!d) {
			break;
		}

		Vector *F = new Vector();
		if (!F) {
			break;
		}

		Stack *stack = new Stack();
		if (!stack) {
			break;
		}

		List *list = new List(stack);
		if (!list) {
			break;
		}

		double const frand_max = RAND_MAX;
		double const a = rand() / frand_max;
		Sphere *sphere = new Sphere(r, u, E, d, F, list, id, kind, a);
		if (!sphere) {
			break;
		}

		printf("radius: %f\n", sphere->radius());
		spheres[i] = sphere;
	}

	Util_Clear();
}
#else
void tutil10 (void)
{
	size_t const numel = 256;
	size_t const size = numel * sizeof(Sphere*);
	Sphere **spheres = (Sphere**) Util_Malloc(size);
	if (!spheres) {
		return;
	}

	for (size_t i = 0; i != numel; ++i) {

		ID *id = new ID(i);
		if (!id) {
			break;
		}

		Kind *kind = new Kind();
		if (!kind) {
			break;
		}

		double const x = rand();
		double const y = rand();
		double const z = rand();
		Vector *r = new Vector(x, y, z);
		if (!r) {
			break;
		}

		Vector *u = new Vector();
		if (!u) {
			break;
		}

		Vector *E = new Vector();
		if (!E) {
			break;
		}

		Vector *d = new Vector(0, 0, 1);
		if (!d) {
			break;
		}

		Vector *F = new Vector();
		if (!F) {
			break;
		}

		Stack *stack = new Stack();
		if (!stack) {
			break;
		}

		List *list = new List(stack);
		if (!list) {
			break;
		}

		double const frand_max = RAND_MAX;
		double const a = rand() / frand_max;
		Sphere *sphere = new Sphere(r, u, E, d, F, list, id, kind, a);
		if (!sphere) {
			break;
		}

		spheres[i] = sphere;
	}

	Util_Clear();
}
#endif

#if VERBOSE
void tutil11 (void)
{
	size_t const numel = 256;
	size_t const size = numel * sizeof(Particle*);
	Particle **particles = (Particle**) Util_Malloc(size);
	if (!particles) {
		return;
	}

	for (size_t i = 0; i != numel; ++i) {

		ID *id = new ID(i);
		if (!id) {
			Util_Clear();
			return;
		}

		double const min_k = 0;
		double const max_k = 4;
		double const k = min_k + (max_k - min_k) * (rand() / ((double) RAND_MAX));
		Kind *kind = new Kind((kind_t) k);
		if (!kind) {
			Util_Clear();
			return;
		}

		double const x = rand();
		double const y = rand();
		double const z = rand();
		Vector *r = new Vector(x, y, z);
		if (!r) {
			Util_Clear();
			return;
		}

		Vector *u = new Vector();
		if (!u) {
			Util_Clear();
			return;
		}

		Vector *E = new Vector();
		if (!E) {
			Util_Clear();
			return;
		}

		Vector *d = new Vector(0, 0, 1);
		if (!d) {
			Util_Clear();
			return;
		}

		Vector *F = new Vector();
		if (!F) {
			Util_Clear();
			return;
		}

		Stack *stack = new Stack();
		if (!stack) {
			break;
		}

		List *list = new List(stack);
		if (!list) {
			break;
		}

		double const frand_max = RAND_MAX;
		double const a = rand() / frand_max;
		double const b = ASPECT_RATIO * a;
		double const c = rand() / frand_max;

		Particle *particle = _Particle(r, u, E, d, F, list, id, kind, a, b, c);
		if (!particle) {
			Util_Clear();
			return;
		}

		particles[i] = particle;
	}

	const Particle **it = ((const Particle**) particles);
	for (size_t i = 1; i != numel; ++i) {
		const Particle *p = *it;
		const char *fmt = "%s %d\n";
		printf(fmt,
		       Kind::stringify(p->kind),
		       Kind::enumerator(Kind::stringify(p->kind)));
		++it;
	}

	Particle *particle = particles[0];
	for (size_t i = 1; i != numel; ++i) {
		particle->ia(particles[i]);
	}

	Util_Clear();
}
#else
void tutil11 (void)
{
	size_t const numel = 256;
	size_t const size = numel * sizeof(Particle*);
	Particle **particles = (Particle**) Util_Malloc(size);
	if (!particles) {
		return;
	}

	for (size_t i = 0; i != numel; ++i) {

		ID *id = new ID(i);
		if (!id) {
			break;
		}

		double const min_k = 0;
		double const max_k = 4;
		double const k = min_k + (max_k - min_k) * (rand() / ((double) RAND_MAX));
		Kind *kind = new Kind((kind_t) k);
		if (!kind) {
			break;
		}

		double const x = rand();
		double const y = rand();
		double const z = rand();
		Vector *r = new Vector(x, y, z);
		if (!r) {
			break;
		}

		Vector *u = new Vector();
		if (!u) {
			break;
		}

		Vector *E = new Vector();
		if (!E) {
			break;
		}

		Vector *d = new Vector(0, 0, 1);
		if (!d) {
			break;
		}

		Vector *F = new Vector();
		if (!F) {
			break;
		}

		Stack *stack = new Stack();
		if (!stack) {
			break;
		}

		List *list = new List(stack);
		if (!list) {
			break;
		}

		double const frand_max = RAND_MAX;
		double const a = rand() / frand_max;
		double const b = ASPECT_RATIO * a;
		double const c = rand() / frand_max;

		Particle *particle = _Particle(r, u, E, d, F, list, id, kind, a, b, c);
		if (!particle) {
			break;
		}

		particles[i] = particle;
	}

	Util_Clear();
}
#endif

#if VERBOSE
void tutil12 (void)
{
	int rc = 0;
	Stack *stack = new Stack();
	if (!stack) {
		Util_Clear();
		return;
	}

	size_t const numel = 1024;
	for (size_t i = 0; i != numel; ++i) {

		ID *id = new ID(i);
		if (!id) {
			break;
		}

		double const min_k = 0;
		double const max_k = 4;
		double const k = min_k + (max_k - min_k) * (rand() / ((double) RAND_MAX));
		Kind *kind = new Kind((kind_t) k);
		if (!kind) {
			break;
		}

		double const x = rand();
		double const y = rand();
		double const z = rand();
		Vector *r = new Vector(x, y, z);
		if (!r) {
			break;
		}

		Vector *u = new Vector();
		if (!u) {
			break;
		}

		Vector *E = new Vector();
		if (!E) {
			break;
		}

		Vector *d = new Vector(0, 0, 1);
		if (!d) {
			break;
		}

		Vector *F = new Vector();
		if (!F) {
			break;
		}

		Stack *stack = new Stack();
		if (!stack) {
			break;
		}

		List *list = new List(stack);
		if (!list) {
			break;
		}

		double const frand_max = RAND_MAX;
		double const a = rand() / frand_max;
		double const b = ASPECT_RATIO * a;
		double const c = rand() / frand_max;

		Particle *particle = _Particle(r, u, E, d, F, list, id, kind, a, b, c);
		if (!particle) {
			break;
		}

		rc = stack->add((void*) particle);
		if (rc != 0) {
			Util_Clear();
			return;
		}
	}

	for (const void **it = (const void**) stack->begin(); it != stack->end(); ++it) {
		const Particle *particle = (const Particle*) *it;
		printf("%s\n", Kind::stringify(particle->kind));
	}

	if (stack->numel() != numel) {
		printf("FAIL\n");
	} else {
		printf("PASS\n");
	}

	if (stack->numel() != stack->cap()) {
		printf("FAIL\n");
	} else {
		printf("PASS\n");
	}

	printf("numel: %lu\n", stack->numel());
	printf("capacity: %lu\n", stack->cap());

	Util_Clear();
}
#else
void tutil12 (void)
{
	int rc = 0;
	Stack *stack = new Stack();
	if (!stack) {
		Util_Clear();
		return;
	}

	size_t const numel = 1024;
	for (size_t i = 0; i != numel; ++i) {

		ID *id = new ID(i);
		if (!id) {
			break;
		}

		double const min_k = 0;
		double const max_k = 4;
		double const k = min_k + (max_k - min_k) * (rand() / ((double) RAND_MAX));
		Kind *kind = new Kind((kind_t) k);
		if (!kind) {
			break;
		}

		double const x = rand();
		double const y = rand();
		double const z = rand();
		Vector *r = new Vector(x, y, z);
		if (!r) {
			break;
		}

		Vector *u = new Vector();
		if (!u) {
			break;
		}

		Vector *E = new Vector();
		if (!E) {
			break;
		}

		Vector *d = new Vector(0, 0, 1);
		if (!d) {
			break;
		}

		Vector *F = new Vector();
		if (!F) {
			break;
		}

		Stack *stack = new Stack();
		if (!stack) {
			break;
		}

		List *list = new List(stack);
		if (!list) {
			break;
		}

		double const frand_max = RAND_MAX;
		double const a = rand() / frand_max;
		double const b = ASPECT_RATIO * a;
		double const c = rand() / frand_max;

		Particle *particle = _Particle(r, u, E, d, F, list, id, kind, a, b, c);
		if (!particle) {
			break;
		}

		rc = stack->add((void*) particle);
		if (rc != 0) {
			Util_Clear();
			return;
		}
	}

	Util_Clear();
}
#endif

#if VERBOSE
void tutil13 (void)
{
	int rc = 0;
	Stack *stack = new Stack();
	if (!stack) {
		Util_Clear();
		return;
	}

	Handler *handler = new Handler(stack);
	if (!handler) {
		Util_Clear();
		return;
	}

	size_t const numel = 1024;
	for (size_t i = 0; i != numel; ++i) {

		ID *id = new ID(i);
		if (!id) {
			break;
		}

		double const min_k = 0;
		double const max_k = 4;
		double const k = min_k + (max_k - min_k) * (rand() / ((double) RAND_MAX));
		Kind *kind = new Kind((kind_t) k);
		if (!kind) {
			break;
		}

		double const x = rand();
		double const y = rand();
		double const z = rand();
		Vector *r = new Vector(x, y, z);
		if (!r) {
			break;
		}

		Vector *u = new Vector();
		if (!u) {
			break;
		}

		Vector *E = new Vector();
		if (!E) {
			break;
		}

		Vector *d = new Vector(0, 0, 1);
		if (!d) {
			break;
		}

		Vector *F = new Vector();
		if (!F) {
			break;
		}

		Stack *stack = new Stack();
		if (!stack) {
			break;
		}

		List *list = new List(stack);
		if (!list) {
			break;
		}

		double const frand_max = RAND_MAX;
		double const a = rand() / frand_max;
		double const b = ASPECT_RATIO * a;
		double const c = rand() / frand_max;

		Particle *particle = _Particle(r, u, E, d, F, list, id, kind, a, b, c);
		if (!particle) {
			break;
		}

		rc = handler->add(particle);
		if (rc != 0) {
			Util_Clear();
			return;
		}
	}

	const Particle **begin = handler->begin();
	const Particle **end = handler->end();
	for (const Particle **iter = begin; iter != end; ++iter) {
		const Particle *particle = (const Particle*) *iter;
		printf("%s\n", Kind::stringify(particle->kind));
	}

	Util_Clear();
}
#else
void tutil13 (void)
{
	int rc = 0;
	Stack *stack = new Stack();
	if (!stack) {
		Util_Clear();
		return;
	}

	Handler *handler = new Handler(stack);
	if (!handler) {
		Util_Clear();
		return;
	}

	size_t const numel = 1024;
	for (size_t i = 0; i != numel; ++i) {

		ID *id = new ID(i);
		if (!id) {
			break;
		}

		double const min_k = 0;
		double const max_k = 4;
		double const k = min_k + (max_k - min_k) * (rand() / ((double) RAND_MAX));
		Kind *kind = new Kind((kind_t) k);
		if (!kind) {
			break;
		}

		double const x = rand();
		double const y = rand();
		double const z = rand();
		Vector *r = new Vector(x, y, z);
		if (!r) {
			break;
		}

		Vector *u = new Vector();
		if (!u) {
			break;
		}

		Vector *E = new Vector();
		if (!E) {
			break;
		}

		Vector *d = new Vector(0, 0, 1);
		if (!d) {
			break;
		}

		Vector *F = new Vector();
		if (!F) {
			break;
		}

		Stack *stack = new Stack();
		if (!stack) {
			break;
		}

		List *list = new List(stack);
		if (!list) {
			break;
		}

		double const frand_max = RAND_MAX;
		double const a = rand() / frand_max;
		double const b = ASPECT_RATIO * a;
		double const c = rand() / frand_max;

		Particle *particle = _Particle(r, u, E, d, F, list, id, kind, a, b, c);
		if (!particle) {
			break;
		}

		rc = handler->add(particle);
		if (rc != 0) {
			Util_Clear();
			return;
		}
	}

	Util_Clear();
}
#endif

void tutil14(void)
{
	Vector *r = new Vector();
	if (!r) {
		Util_Clear();
		return;
	}

	double const length = 16;
	double const width = 16;
	double const height = 32;
	BoundingBox *bb = new BoundingBox(r, length, width, height);
	if (!bb) {
		Util_Clear();
		return;
	}

	struct Brownian *Brownian = new struct Brownian();
	if (!Brownian) {
		Util_Clear();
		return;
	}

	Stack *stack = new Stack();
	if (!stack) {
		Util_Clear();
		return;
	}

	Handler *handler = new Handler(stack);
	if (!handler) {
		Util_Clear();
		return;
	}

	System *system = new System(bb, Brownian, handler);
	if (!system) {
		Util_Clear();
		return;
	}

	Util_Clear();
}

void tutil15 (void)
{
	return;
}

/*

BDX                                             December 31, 2023

Copyright (C) 2023 Misael Díaz-Maldonado
Copyright (C) 2024 UCF-Research Group

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
source: src/test/util/test.cpp

References:
[0] A Koenig and B Moo, Accelerated C++ Practical Programming by Example.
[1] MP Allen and DJ Tildesley, Computer Simulation of Liquids.
[2] S Kim and S Karrila, Microhydrodynamics.

*/
