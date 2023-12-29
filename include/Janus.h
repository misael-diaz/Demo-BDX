#ifndef GUARD_BDX_JANUS_H
#define GUARD_BDX_JANUS_H

struct ID;
struct Kind;
struct Vector;
struct BDXObject;
struct Particle;
struct Sphere;

struct Janus : Sphere
{
	public:
	Vector *T = NULL;
	Janus(Vector *r,
	      Vector *u,
	      Vector *E,
	      Vector *d,
	      Vector *F,
	      Vector *T,
	      ID *id,
	      Kind *kind,
	      double const a);
	void ia(const Particle *particle);
	void *operator new(size_t size);
	void operator delete(void *p);
};

#endif
