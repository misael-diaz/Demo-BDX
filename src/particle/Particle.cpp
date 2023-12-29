#include "util.h"
#include "ID.h"
#include "Kind.h"
#include "Vector.h"
#include "BDXObject.h"
#include "Particle.h"

Particle::Particle (Vector *r, ID *id, Kind *kind) : BDXObject(r)
{
	this->id = id;
	this->kind = kind;
}

void *Particle::operator new (size_t size)
{
	return Util_Malloc(size);
}

void Particle::operator delete (void *p)
{
	p = Util_Free(p);
}
