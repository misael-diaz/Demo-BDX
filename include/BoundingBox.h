#ifndef GUARD_BDX_BOUNDING_BOX_H
#define GUARD_BDX_BOUNDING_BOX_H

struct Vector;
struct BDXObject;

class BoundingBox : BDXObject
{
	private:
	Vector *r = NULL;
	double l = 0;
	double w = 0;
	double h = 0;
	public:
	BoundingBox(Vector *r, double const l, double const w, double const h);
	double length() const;
	double width() const;
	double height() const;
	void *operator new(size_t size);
	void operator delete(void *p);
};

#endif
