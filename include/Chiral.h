#ifndef GUARD_BDX_CHIRAL_H
#define GUARD_BDX_CHIRAL_H

struct ID;
struct Kind;
struct Vector;
struct BDXObject;
struct Particle;
struct Spheroid;

struct Chiral : Spheroid
{
	protected:
	double c = 1.0;
	public:
	Chiral(Vector *r,
	       Vector *u,
	       Vector *E,
	       Vector *d,
	       Vector *F,
	       Vector *T,
	       ID *id,
	       Kind *kind,
	       double const a,
	       double const b,
	       double const c);
	double chiral() const;
	void ia(const Particle *particle);
	void *operator new(size_t size);
	void operator delete(void *p);
};

#endif
