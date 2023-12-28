#ifndef GUARD_BDX_PARTICLE_H
#define GUARD_BDX_PARTICLE_H

struct ID;
struct Vector;
struct BDXObject;

struct Particle : BDXObject
{
	Vector *r = NULL;
	ID *id = NULL;
	Particle(Vector *r, ID *id);
	void *operator new(size_t size);
	void operator delete(void *p);
};

#endif
