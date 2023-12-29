#ifndef GUARD_BDX_PARTICLE_H
#define GUARD_BDX_PARTICLE_H

struct ID;
struct Kind;
struct Vector;
struct BDXObject;

struct Particle : BDXObject
{
	Vector *u = NULL;
	ID *id = NULL;
	Kind *kind = NULL;
	Particle(Vector *r, Vector *u, ID *id, Kind *kind);
	virtual void ia(const Particle *particle) = 0;
	void *operator new(size_t size);
	void operator delete(void *p);
};

#endif
