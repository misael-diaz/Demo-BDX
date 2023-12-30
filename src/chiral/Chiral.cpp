#include <cstdio>

#include "util.h"
#include "ID.h"
#include "Kind.h"
#include "Vector.h"
#include "BDXObject.h"
#include "Particle.h"
#include "Spheroid.h"
#include "Chiral.h"

Chiral::Chiral (Vector *r,
		Vector *u,
		Vector *E,
		Vector *d,
		Vector *F,
		Vector *T,
		ID *id,
		Kind *kind,
		double const a,
		double const b,
		double const c):
		Spheroid(r, u, E, d, F, T, id, kind, a, b),
		c(c)
{
	return;
}

double Chiral::chiral () const
{
	return this->c;
}

void Chiral::ia (const Particle *particle)
{
	const Particle *that = particle;
	const Kind *kind = that->kind;
	kind_t const k = kind->k();
	switch(k){
		case SPHERE:
		printf("chiral-sphere interaction\n");
		break;
		case JANUS:
		printf("chiral-janus interaction\n");
		break;
		case SPHEROID:
		printf("chiral-spheroid interaction\n");
		break;
		case CHIRAL:
		printf("chiral-chiral interaction\n");
		break;
		default:
		printf("no interaction\n");
	}
}

void *Chiral::operator new (size_t size)
{
	return Util_Malloc(size);
}

void Chiral::operator delete (void *p)
{
	p = Util_Free(p);
}
