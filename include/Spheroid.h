#ifndef GUARD_BDX_SPHEROID_H
#define GUARD_BDX_SPHEROID_H

struct ID;
struct Kind;
struct Vector;
struct BDXObject;
struct Particle;

struct Spheroid : Particle
{
	protected:
	double a = 1.0;
	double b = 3.0;
	public:
	Vector *F = NULL;
	Vector *T = NULL;
	Spheroid(Vector *r,
	         Vector *u,
	         Vector *E,
	         Vector *d,
	         Vector *F,
	         Vector *T,
	         ID *id,
	         Kind *kind,
	         double const a,
		 double const b);
	double radius_minor() const;
	double radius_major() const;
	void ia(const Particle *particle);
	void *operator new(size_t size);
	void operator delete(void *p);
};

#endif
