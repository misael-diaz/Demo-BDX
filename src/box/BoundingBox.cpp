#include "util.h"
#include "Vector.h"
#include "BDXObject.h"
#include "BoundingBox.h"

BoundingBox::BoundingBox (Vector *r,
			  double const l,
			  double const w,
			  double const h) :
			  BDXObject(r),
			  l(l),
			  w(w),
			  h(h)
{
	return;
}

double BoundingBox::length() const
{
	return this->l;
}

double BoundingBox::width() const
{
	return this->w;
}

double BoundingBox::height() const
{
	return this->h;
}

void *BoundingBox::operator new (size_t size)
{
	return Util_Malloc(size);
}

void BoundingBox::operator delete (void *p)
{
	p = Util_Free(p);
}
