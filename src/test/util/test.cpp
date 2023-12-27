#include <cstdio>
#include <cstring>

#include "util.h"

void tutil1(void);
void tutil2(void);
void tutil3(void);

int main ()
{
	tutil1();
	tutil2();
	tutil3();
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
