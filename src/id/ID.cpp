#include "util.h"
#include "ID.h"

ID::ID () : i(0)
{
	return;
}

ID::ID (long const i) : i(i)
{
	return;
}

void *ID::operator new (size_t size)
{
	return Util_Malloc(size);
}

void ID::operator delete (void *p)
{
	p = Util_Free(p);
}
