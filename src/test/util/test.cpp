#include <cstdio>
#include <cstring>
#include <cstdlib>

#include "util.h"
#include "ID.h"
#include "Kind.h"
#include "Vector.h"
#include "BDXObject.h"
#include "Particle.h"
#include "Sphere.h"
#include "BoundingBox.h"

#define COMPILE 0
#define VERBOSE 0

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
	return 0;
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
			return;
		}
	}

	Util_Clear();
}

void tutil6 (void)
{
	Vector *r = new Vector();
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
		Kind *kind = new Kind();
		double const x = rand();
		double const y = rand();
		double const z = rand();
		Vector *r = new Vector(x, y, z);
		double const frand_max = RAND_MAX;
		double const a = rand() / frand_max;
		Sphere *sphere = new Sphere(r, id, kind, a);
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
		Kind *kind = new Kind();
		double const x = rand();
		double const y = rand();
		double const z = rand();
		Vector *r = new Vector(x, y, z);
		double const frand_max = RAND_MAX;
		double const a = rand() / frand_max;
		Sphere *sphere = new Sphere(r, id, kind, a);
		if (!sphere) {
			break;
		}

		spheres[i] = sphere;
	}

	Util_Clear();
}
#endif
