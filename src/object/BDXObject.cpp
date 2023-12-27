#include "util.h"
#include "Vector.h"
#include "BDXObject.h"

BDXObject::BDXObject (Vector *r)
{
	this->r = r;
}

void *BDXObject::operator new (size_t size)
{
	return Util_Malloc(size);
}

void BDXObject::operator delete (void *p)
{
	p = Util_Free(p);
}
