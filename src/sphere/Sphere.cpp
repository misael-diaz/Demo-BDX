#include <cstdio>

#include "util.h"
#include "ID.h"
#include "Kind.h"
#include "Vector.h"
#include "BDXObject.h"
#include "Particle.h"
#include "Sphere.h"

Sphere::Sphere (Vector *r,
		Vector *u,
		ID *id,
		Kind *kind,
		double const a):
		Particle(r, u, id, kind),
		a(a)
{
	return;
}

double Sphere::radius () const
{
	return this->a;
}

void Sphere::ia (const Particle *particle)
{
	const Particle *that = particle;
	const Kind *kind = that->kind;
	kind_t const k = kind->k();
	switch(k){
		case SPHERE:
		printf("sphere-sphere interaction\n");
		break;
		case JANUS:
		printf("sphere-janus interaction\n");
		break;
		case SPHEROID:
		printf("sphere-spheroid interaction\n");
		break;
		default:
		printf("defaults to sphere-sphere interaction\n");
	}
}

void *Sphere::operator new (size_t size)
{
	return Util_Malloc(size);
}

void Sphere::operator delete (void *p)
{
	p = Util_Free(p);
}
