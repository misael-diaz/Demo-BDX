#include "util.h"
#include "ID.h"
#include "Vector.h"
#include "BDXObject.h"
#include "Particle.h"
#include "Sphere.h"

Sphere::Sphere (Vector *r, ID *id, double const a) : Particle(r, id), a(a)
{
	return;
}

double Sphere::radius () const
{
	return this->a;
}

void *Sphere::operator new (size_t size)
{
	return Util_Malloc(size);
}

void Sphere::operator delete (void *p)
{
	p = Util_Free(p);
}
