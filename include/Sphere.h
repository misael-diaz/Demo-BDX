#ifndef GUARD_BDX_SPHERE_H
#define GUARD_BDX_SPHERE_H

struct ID;
struct Kind;
struct Vector;
struct BDXObject;
struct Particle;

class Sphere : Particle
{
	private:
	double a = 1.0;
	public:
	Sphere(Vector *r, ID *id, Kind *kind, double const a);
	double radius() const;
	void *operator new(size_t size);
	void operator delete(void *p);
};

#endif
