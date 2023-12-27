#ifndef GUARD_BDX_OBJECT_H
#define GUARD_BDX_OBJECT_H

struct Vector;

struct BDXObject {
	Vector *r = NULL;
	BDXObject(Vector *r);
	void *operator new(size_t size);
	void operator delete(void *p);
};

#endif
