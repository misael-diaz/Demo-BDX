#ifndef GUARD_BDX_VECTOR_H
#define GUARD_BDX_VECTOR_H

struct Vector {
	double x;
	double y;
	double z;
	Vector();
	Vector(double const x, double const y, double const z);
	void *operator new(size_t size);
	void operator delete(void *p);
};

#endif
