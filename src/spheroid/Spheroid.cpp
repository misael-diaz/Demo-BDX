#include <cstdio>

#include "util.h"
#include "ID.h"
#include "Kind.h"
#include "Vector.h"
#include "BDXObject.h"
#include "Particle.h"
#include "Spheroid.h"

Spheroid::Spheroid (Vector *r,
		    Vector *u,
		    Vector *E,
		    Vector *d,
		    Vector *F,
		    Vector *T,
		    ID *id,
		    Kind *kind,
		    double const a,
		    double const b):
		    Particle(r, u, E, d, id, kind),
		    a(a),
		    b(b)
{
	this->F = F;
	this->T = T;
}

double Spheroid::radius_minor () const
{
	return this->a;
}

double Spheroid::radius_major () const
{
	return this->b;
}

void Spheroid::ia (const Particle *particle)
{
	const Particle *that = particle;
	const Kind *kind = that->kind;
	kind_t const k = kind->k();
	switch(k){
		case SPHERE:
		printf("spheroid-sphere interaction\n");
		break;
		case JANUS:
		printf("spheroid-janus interaction\n");
		break;
		case SPHEROID:
		printf("spheroid-spheroid interaction\n");
		break;
		case CHIRAL:
		printf("spheroid-chiral interaction\n");
		break;
		default:
		printf("no interaction\n");
	}
}

void *Spheroid::operator new (size_t size)
{
	return Util_Malloc(size);
}

void Spheroid::operator delete (void *p)
{
	p = Util_Free(p);
}
