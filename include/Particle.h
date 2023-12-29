#ifndef GUARD_BDX_PARTICLE_H
#define GUARD_BDX_PARTICLE_H

struct ID;
struct Kind;
struct Vector;
struct BDXObject;

struct Particle : BDXObject
{
	ID *id = NULL;
	Kind *kind = NULL;
	Particle(Vector *r, ID *id, Kind *kind);
	void *operator new(size_t size);
	void operator delete(void *p);
};

#endif
