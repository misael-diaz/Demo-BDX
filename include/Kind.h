#ifndef GUARD_BDX_KIND_H
#define GUARD_BDX_KIND_H

typedef enum {
	SPHERE,
	JANUS,
	SPHEROID
} kind_t;

struct Kind
{
	kind_t kind;
	Kind();
	Kind(kind_t const kind);
	kind_t k(void) const;
	void *operator new(size_t size);
	void operator delete(void *p);
};

#endif
