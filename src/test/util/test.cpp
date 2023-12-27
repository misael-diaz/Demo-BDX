#include <cstdio>
#include <cstring>

#include "util.h"
#include "Vector.h"
#include "BDXObject.h"

void tutil1(void);
void tutil2(void);
void tutil3(void);
void tutil4(void);
void tutil5(void);
void tutil6(void);

int main ()
{
	tutil1();
	tutil2();
	tutil3();
	tutil4();
	tutil5();
	tutil6();
	return 0;
}

void tutil1 (void)
{
	const char txt[] = "string-literal";
	void *ptr = Util_Malloc(strlen(txt) + 1);

	char *dst = (char*) ptr;
	strcpy(dst, txt);
	printf("%s\n", dst);

	ptr = Util_Free(ptr);
}

void tutil2 (void)
{
	typedef struct {
		double x;
	} data_t;

	data_t data = { .x = 0 };
	void *ptr = Util_Malloc(sizeof(data_t));

	data_t *dst = (data_t*) ptr;
	dst->x = 0.0;

	printf("%f %f\n", data.x, dst->x);

	ptr = Util_Free(ptr);
}

void tutil3 (void)
{
	double *data[] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
	size_t const numel = sizeof(data) / sizeof(double);
	for (size_t i = 0; i != numel; ++i) {

		data[i] = (double*) Util_Malloc(sizeof(double));
		if (!data[i]) {
			Util_Clear();
			return;
		}

		*data[i] = ((double) i);
	}

	double sum = 0;
	for (size_t i = 0; i != numel; ++i) {
		sum += *data[i];
	}

	double const total = 0.5 * (numel - 1.0) * numel;
	if (total != sum) {
		printf("FAIL\n");
	} else {
		printf("PASS\n");
	}

	Util_Clear();
}

void tutil4 (void)
{
	Vector *vector = new Vector();
	delete(vector);
}

void tutil5 (void)
{
	size_t const numel = 8;
	Vector **vectors = (Vector**) Util_Malloc(numel * sizeof(Vector*));
	for (size_t i = 0; i != numel; ++i) {
		vectors[i] = new Vector();
		if (!vectors[i]) {
			return;
		}
	}

	Util_Clear();
}

void tutil6 (void)
{
	Vector *r = new Vector();
	BDXObject *obj = new BDXObject(r);
	delete(obj);
	Util_Clear();
}
