#include "util.h"
#include "Vector.h"

Vector::Vector() : x(0), y(0), z(0)
{
	return;
}

Vector::Vector(double const x0, double const y0, double const z0) : x(x0), y(y0), z(z0)
{
	return;
}

void *Vector::operator new (size_t size)
{
	return Util_Malloc(size);
}

void Vector::operator delete (void *p)
{
	p = Util_Free(p);
}
