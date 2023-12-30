#include <cstdio>

#include "util.h"
#include "ID.h"
#include "Kind.h"
#include "Vector.h"
#include "BDXObject.h"
#include "Particle.h"
#include "Sphere.h"
#include "Janus.h"

Janus::Janus (Vector *r,
	      Vector *u,
	      Vector *E,
	      Vector *d,
	      Vector *F,
	      Vector *T,
	      ID *id,
	      Kind *kind,
	      double const a):
	      Sphere(r, u, E, d, F, id, kind, a)
{
	this->T = T;
}

void Janus::ia (const Particle *particle)
{
	const Particle *that = particle;
	const Kind *kind = that->kind;
	kind_t const k = kind->k();
	switch(k){
		case SPHERE:
		printf("janus-sphere interaction\n");
		break;
		case JANUS:
		printf("janus-janus interaction\n");
		break;
		case SPHEROID:
		printf("janus-spheroid interaction\n");
		break;
		case CHIRAL:
		printf("janus-chiral interaction\n");
		break;
		default:
		printf("no interaction\n");
	}
}

void *Janus::operator new (size_t size)
{
	return Util_Malloc(size);
}

void Janus::operator delete (void *p)
{
	p = Util_Free(p);
}
