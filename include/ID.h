#ifndef GUARD_BDX_ID_H
#define GUARD_BDX_ID_H

struct ID
{
	long i;
	ID();
	ID(long const i);
	void *operator new(size_t size);
	void operator delete(void *p);
};

#endif
