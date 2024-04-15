#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

#include "os.h"
#include "util.h"
#include "LMP.h"
#include "Stack.h"
#include "ID.h"
#include "Kind.h"
#include "Vector.h"
#include "BDXObject.h"
#include "Particle.h"
#include "Sphere.h"
#include "Janus.h"
#include "Spheroid.h"
#include "Chiral.h"
#include "BoundingBox.h"
#include "Brownian.h"
#include "Handler.h"
#include "Prompt.h"
#include "Config.h"
#include "Timer.h"
#include "Random.h"
#include "Looper.h"
#include "Driver.h"
#include "Integrator.h"
#include "Logger.h"
#include "System.h"
#include "List.h"
#include "BDX.h"

#define COMPILE 0
#define VERBOSE 0
#define ASPECT_RATIO 3.0

void tutil1(void);
void tutil2(void);
void tutil3(void);
void tutil4(void);
void tutil5(void);
void tutil6(void);
void tutil7(void);
void tutil8(void);
void tutil9(void);
void tutil10(void);
void tutil11(void);
void tutil12(void);
void tutil13(void);
void tutil14(void);
void tutil15(void);
void tutil16(void);
void tutil17(void);
void tutil18(void);
void tutil19(void);
void tutil20(void);
void tutil21(void);

#ifdef GXX
Particle *_Particle(Vector *r,
		    Vector *u,
		    Vector *E,
		    Vector *d,
		    Vector *F,
		    Vector *T,
		    List *list,
		    ID *id,
		    Kind *kind,
		    double const a,
		    double const b,
		    double const c)
__attribute__ ((nonnull (1, 2, 3, 4, 5, 6, 7, 8, 9)));
#else
Particle *_Particle(Vector *r,
		    Vector *u,
		    Vector *E,
		    Vector *d,
		    Vector *F,
		    Vector *T,
		    List *list,
		    ID *id,
		    Kind *kind,
		    double const a,
		    double const b,
		    double const c);
#endif

int main ()
{
	tutil1();
	tutil2();
	tutil3();
	tutil4();
	tutil5();
	tutil6();
	tutil7();
	tutil8();
	tutil9();
	tutil10();
	tutil11();
	tutil12();
	tutil13();
	tutil14();
	tutil15();
	tutil16();
	tutil17();
	tutil18();
	tutil19();
	tutil20();
	tutil21();
	util::clearall();
	return 0;
}

Particle *_Particle (Vector *r,
		     Vector *u,
		     Vector *E,
		     Vector *d,
		     Vector *F,
		     Vector *T,
		     List *list,
		     ID *id,
		     Kind *kind,
		     double const a,
		     double const b,
		     double const c)
{
	Particle *particle = NULL;
	kind_t const k = kind->k();
	switch(k)
	{
		case SPHERE:
		particle = new Sphere(r, u, E, d, F, T, list, id, kind, a);
		break;

		case JANUS:
		particle = new Janus(r, u, E, d, F, T, list, id, kind, a);
		break;

		case SPHEROID:
		particle = new Spheroid(r, u, E, d, F, T, list, id, kind, a, b);
		break;

		case CHIRAL:
		particle = new Chiral(r, u, E, d, F, T, list, id, kind, a, b, c);
		break;

		default:
		particle = new Sphere(r, u, E, d, F, T, list, id, kind, a);
	}

	return particle;
}

void tutil1 (void)
{
	const char txt[] = "string-literal";
	void *ptr = util::malloc(strlen(txt) + 1);

	char *dst = (char*) ptr;
	strcpy(dst, txt);
	printf("%s\n", dst);

	ptr = util::free(ptr);
}

void tutil2 (void)
{
	typedef struct {
		double x;
	} data_t;

	data_t data = { .x = 0 };
	void *ptr = util::malloc(sizeof(data_t));

	data_t *dst = (data_t*) ptr;
	dst->x = 0.0;

	printf("%f %f\n", data.x, dst->x);

	ptr = util::free(ptr);
}

void tutil3 (void)
{
	double *data[] = {NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};
	size_t const numel = sizeof(data) / sizeof(double);
	for (size_t i = 0; i != numel; ++i) {
		data[i] = (double*) util::malloc(sizeof(double));
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

	util::clearall();
}

void tutil4 (void)
{
	Vector *vector = new Vector();
	delete(vector);
}

void tutil5 (void)
{
	size_t const numel = 8;
	Vector **vectors = (Vector**) util::malloc(numel * sizeof(Vector*));
	for (size_t i = 0; i != numel; ++i) {
		vectors[i] = new Vector();
	}

	util::clearall();
}

void tutil6 (void)
{
	Vector *r = new Vector();
	BDXObject *obj = new BDXObject(r);
	delete(obj);
	util::clearall();
}

#if COMPILE
void tutil7 (void)
{
	ID *id = new ID();
	Kind *kind = new Kind();
	Vector *r = new Vector();
	Particle *particle = new Particle(r, id, kind);
	delete(particle);
	util::clearall();
}
#else
void tutil7 (void)
{
	return;
}
#endif

#if COMPILE
void tutil8 (void)
{
	size_t const numel = 256;
	size_t const size = numel * sizeof(Particle*);
	Particle **particles = (Particle**) util::malloc(size);
	for (size_t i = 0; i != numel; ++i) {
		ID *id = new ID(i);
		Kind *kind = new Kind();
		double const x = rand();
		double const y = rand();
		double const z = rand();
		Vector *r = new Vector(x, y, z);
		Particle *particle = new Particle(r, id, kind);
		particles[i] = particle;
	}

	util::clearall();
}
#else
void tutil8 (void)
{
	return;
}
#endif

void tutil9 (void)
{
	Vector *r = new Vector();
	double const length = 16;
	double const width = 16;
	double const height = 32;
	BoundingBox *bb = new BoundingBox(r, length, width, height);
	delete(bb);
	util::clearall();
}

#if VERBOSE
void tutil10 (void)
{
	size_t const numel = 256;
	size_t const size = numel * sizeof(Sphere*);
	Sphere **spheres = (Sphere**) util::malloc(size);
	for (size_t i = 0; i != numel; ++i) {
		ID *id = new ID(i);
		Kind *kind = new Kind();
		double const x = rand();
		double const y = rand();
		double const z = rand();
		Vector *r = new Vector(x, y, z);
		Vector *u = new Vector();
		Vector *E = new Vector();
		Vector *d = new Vector(0, 0, 1);
		Vector *F = new Vector();
		Vector *T = new Vector();
		Stack *stack = new Stack();
		List *list = new List(stack);
		double const frand_max = RAND_MAX;
		double const a = rand() / frand_max;
		Sphere *sphere = new Sphere(r, u, E, d, F, T, list, id, kind, a);
		printf("radius: %f\n", sphere->radius());
		spheres[i] = sphere;
	}

	util::clearall();
}
#else
void tutil10 (void)
{
	size_t const numel = 256;
	size_t const size = numel * sizeof(Sphere*);
	Sphere **spheres = (Sphere**) util::malloc(size);
	for (size_t i = 0; i != numel; ++i) {
		ID *id = new ID(i);
		Kind *kind = new Kind();
		double const x = rand();
		double const y = rand();
		double const z = rand();
		Vector *r = new Vector(x, y, z);
		Vector *u = new Vector();
		Vector *E = new Vector();
		Vector *d = new Vector(0, 0, 1);
		Vector *F = new Vector();
		Vector *T = new Vector();
		Stack *stack = new Stack();
		List *list = new List(stack);
		double const frand_max = RAND_MAX;
		double const a = rand() / frand_max;
		Sphere *sphere = new Sphere(r, u, E, d, F, T, list, id, kind, a);
		spheres[i] = sphere;
	}

	util::clearall();
}
#endif

#if VERBOSE
void tutil11 (void)
{
	size_t const numel = 256;
	size_t const size = numel * sizeof(Particle*);
	Particle **particles = (Particle**) util::malloc(size);
	for (size_t i = 0; i != numel; ++i) {
		ID *id = new ID(i);
		double const min_k = 0;
		double const max_k = 4;
		double const k = min_k + (max_k - min_k) * (rand() / ((double) RAND_MAX));
		Kind *kind = new Kind((kind_t) k);
		double const x = rand();
		double const y = rand();
		double const z = rand();
		Vector *r = new Vector(x, y, z);
		Vector *u = new Vector();
		Vector *E = new Vector();
		Vector *d = new Vector(0, 0, 1);
		Vector *F = new Vector();
		Vector *T = new Vector();
		Stack *stack = new Stack();
		List *list = new List(stack);
		double const frand_max = RAND_MAX;
		double const a = rand() / frand_max;
		double const b = ASPECT_RATIO * a;
		double const c = rand() / frand_max;
		Particle *particle = _Particle(r, u, E, d, F, T, list, id, kind, a, b, c);
		particles[i] = particle;
	}

	const Particle **it = ((const Particle**) particles);
	for (size_t i = 1; i != numel; ++i) {
		const Particle *p = *it;
		const char *fmt = "%s %d\n";
		printf(fmt,
		       Kind::stringify(p->kind),
		       Kind::enumerator(Kind::stringify(p->kind)));
		++it;
	}

	Particle *particle = particles[0];
	for (size_t i = 1; i != numel; ++i) {
		particle->ia(particles[i]);
	}

	util::clearall();
}
#else
void tutil11 (void)
{
	size_t const numel = 256;
	size_t const size = numel * sizeof(Particle*);
	Particle **particles = (Particle**) util::malloc(size);
	for (size_t i = 0; i != numel; ++i) {
		ID *id = new ID(i);
		double const min_k = 0;
		double const max_k = 4;
		double const k = min_k + (max_k - min_k) * (rand() / ((double) RAND_MAX));
		Kind *kind = new Kind((kind_t) k);
		double const x = rand();
		double const y = rand();
		double const z = rand();
		Vector *r = new Vector(x, y, z);
		Vector *u = new Vector();
		Vector *E = new Vector();
		Vector *d = new Vector(0, 0, 1);
		Vector *F = new Vector();
		Vector *T = new Vector();
		Stack *stack = new Stack();
		List *list = new List(stack);
		double const frand_max = RAND_MAX;
		double const a = rand() / frand_max;
		double const b = ASPECT_RATIO * a;
		double const c = rand() / frand_max;
		Particle *particle = _Particle(r, u, E, d, F, T, list, id, kind, a, b, c);
		particles[i] = particle;
	}

	util::clearall();
}
#endif

#if VERBOSE
void tutil12 (void)
{
	int rc = 0;
	Stack *stack = new Stack();
	size_t const numel = 1024;
	for (size_t i = 0; i != numel; ++i) {
		ID *id = new ID(i);
		double const min_k = 0;
		double const max_k = 4;
		double const k = min_k + (max_k - min_k) * (rand() / ((double) RAND_MAX));
		Kind *kind = new Kind((kind_t) k);
		double const x = rand();
		double const y = rand();
		double const z = rand();
		Vector *r = new Vector(x, y, z);
		Vector *u = new Vector();
		Vector *E = new Vector();
		Vector *d = new Vector(0, 0, 1);
		Vector *F = new Vector();
		Vector *T = new Vector();
		Stack *stack = new Stack();
		List *list = new List(stack);
		double const frand_max = RAND_MAX;
		double const a = rand() / frand_max;
		double const b = ASPECT_RATIO * a;
		double const c = rand() / frand_max;
		Particle *particle = _Particle(r, u, E, d, F, T, list, id, kind, a, b, c);
		stack->add((void*) particle);
	}

	for (const void **it = (const void**) stack->begin(); it != stack->end(); ++it) {
		const Particle *particle = (const Particle*) *it;
		printf("%s\n", Kind::stringify(particle->kind));
	}

	if (stack->numel() != numel) {
		printf("FAIL\n");
	} else {
		printf("PASS\n");
	}

	if (stack->numel() != stack->cap()) {
		printf("FAIL\n");
	} else {
		printf("PASS\n");
	}

	printf("numel: %lu\n", stack->numel());
	printf("capacity: %lu\n", stack->cap());

	util::clearall();
}
#else
void tutil12 (void)
{
	size_t const numel = 1024;
	for (size_t i = 0; i != numel; ++i) {
		ID *id = new ID(i);
		double const min_k = 0;
		double const max_k = 4;
		double const k = min_k + (max_k - min_k) * (rand() / ((double) RAND_MAX));
		Kind *kind = new Kind((kind_t) k);
		double const x = rand();
		double const y = rand();
		double const z = rand();
		Vector *r = new Vector(x, y, z);
		Vector *u = new Vector();
		Vector *E = new Vector();
		Vector *d = new Vector(0, 0, 1);
		Vector *F = new Vector();
		Vector *T = new Vector();
		Stack *stack = new Stack();
		List *list = new List(stack);
		double const frand_max = RAND_MAX;
		double const a = rand() / frand_max;
		double const b = ASPECT_RATIO * a;
		double const c = rand() / frand_max;
		Particle *particle = _Particle(r, u, E, d, F, T, list, id, kind, a, b, c);
		stack->add((void*) particle);
	}

	util::clearall();
}
#endif

#if VERBOSE
void tutil13 (void)
{
	int rc = 0;
	Stack *stack = new Stack();
	Handler *handler = new Handler(stack);
	size_t const numel = 1024;
	for (size_t i = 0; i != numel; ++i) {
		ID *id = new ID(i);
		double const min_k = 0;
		double const max_k = 4;
		double const k = min_k + (max_k - min_k) * (rand() / ((double) RAND_MAX));
		Kind *kind = new Kind((kind_t) k);
		double const x = rand();
		double const y = rand();
		double const z = rand();
		Vector *r = new Vector(x, y, z);
		Vector *u = new Vector();
		Vector *E = new Vector();
		Vector *d = new Vector(0, 0, 1);
		Vector *F = new Vector();
		Vector *T = new Vector();
		Stack *stack = new Stack();
		List *list = new List(stack);
		double const frand_max = RAND_MAX;
		double const a = rand() / frand_max;
		double const b = ASPECT_RATIO * a;
		double const c = rand() / frand_max;
		Particle *particle = _Particle(r, u, E, d, F, T, list, id, kind, a, b, c);
		handler->add(particle);
	}

	const Particle **begin = handler->begin();
	const Particle **end = handler->end();
	for (const Particle **iter = begin; iter != end; ++iter) {
		const Particle *particle = (const Particle*) *iter;
		printf("%s\n", Kind::stringify(particle->kind));
	}

	util::clearall();
}
#else
void tutil13 (void)
{
	Stack *stack = new Stack();
	Handler *handler = new Handler(stack);
	size_t const numel = 1024;
	for (size_t i = 0; i != numel; ++i) {
		ID *id = new ID(i);
		double const min_k = 0;
		double const max_k = 4;
		double const k = min_k + (max_k - min_k) * (rand() / ((double) RAND_MAX));
		Kind *kind = new Kind((kind_t) k);
		double const x = rand();
		double const y = rand();
		double const z = rand();
		Vector *r = new Vector(x, y, z);
		Vector *u = new Vector();
		Vector *E = new Vector();
		Vector *d = new Vector(0, 0, 1);
		Vector *F = new Vector();
		Vector *T = new Vector();
		Stack *stack = new Stack();
		List *list = new List(stack);
		double const frand_max = RAND_MAX;
		double const a = rand() / frand_max;
		double const b = ASPECT_RATIO * a;
		double const c = rand() / frand_max;
		Particle *particle = _Particle(r, u, E, d, F, T, list, id, kind, a, b, c);
		handler->add(particle);
	}

	util::clearall();
}
#endif

void tutil14(void)
{
	Vector *r = new Vector();
	double const length = 16;
	double const width = 16;
	double const height = 32;
	BoundingBox *bb = new BoundingBox(r, length, width, height);
	struct Brownian *Brownian = new struct Brownian();
	Stack *stack = new Stack();
	Handler *handler = new Handler(stack);
	System *system = new System(bb, Brownian, handler);
	delete(system);
	util::clearall();
}

void tutil15 (void)
{
	Vector *r = new Vector();
	double const length = 16;
	double const width = 16;
	double const height = 32;
	BoundingBox *bb = new BoundingBox(r, length, width, height);
	struct Brownian *Brownian = new struct Brownian();
	Stack *stack = new Stack();
	Handler *handler = new Handler(stack);
	System *system = new System(bb, Brownian, handler);
	Prompt *prompt = new Prompt();
	Config *config = new Config();
	Timer *timer = new Timer();
	Random *random = new Random(random::NORMAL);
	Looper *looper = new Looper();
	Driver *driver = new Driver();
	Integrator *integrator = new Integrator();
	Logger *logger = new Logger();
	BDX *App = new BDX(prompt,
			   config,
			   timer,
			   random,
			   looper,
			   driver,
			   integrator,
			   logger,
			   system);

	config->load();
	config->parse();
	config->config();
	delete(App);
	util::clearall();
}


void tutil16 (void)
{
	Vector *r = new Vector();
	double const length = 16;
	double const width = 16;
	double const height = 32;
	BoundingBox *bb = new BoundingBox(r, length, width, height);
	struct Brownian *Brownian = new struct Brownian();
	Stack *stack = new Stack();
	Handler *handler = new Handler(stack);
	System *system = new System(bb, Brownian, handler);
	Prompt *prompt = new Prompt();
	Config *config = new Config();
	Timer *timer = new Timer();
	Random *random = new Random(random::NORMAL);
	Looper *looper = new Looper();
	Driver *driver = new Driver();
	Integrator *integrator = new Integrator();
	Logger *logger = new Logger();
	BDX *App = new BDX(prompt,
			   config,
			   timer,
			   random,
			   looper,
			   driver,
			   integrator,
			   logger,
			   system);

	config->load();
	config->parse();
	config->config();
	App->_exec_ = true;
	App->looper->loop();
	util::clearall();
}

void tutil17 (void)
{
	Stack *stk = new Stack();
	void *data = lmp::load();
	size_t const num_particles = lmp::parse(data, stk);
	for (double **it = (double**) stk->begin(); it != (double**) stk->end(); ++it) {
		os::print("%f\n", **it);
	}
	os::print("particles: %zu\n", num_particles);
	util::clearall();
}

void tutil18 (void)
{
	Random *r = new Random(random::NORMAL);
	size_t const numel = 0x80000;
	size_t const size = numel * sizeof(double);
	double *x = (double*) util::malloc(size);
	ssize_t *y = (ssize_t*) util::malloc(numel * sizeof(ssize_t));
	size_t bins = 13;
	ssize_t hist_size = bins * sizeof(ssize_t);
	ssize_t *hist = (ssize_t*) util::malloc(hist_size);
	memset(hist, 0, hist_size);

	for (size_t i = 0; i != numel; ++i) {
		x[i] = r->fetch();
	}

	for (size_t i = 0; i != numel; ++i) {
		if (x[i] < -6.0) {
			y[i] = -6;
		} else if (x[i] > 6) {
			y[i] = 6;
		} else {
			y[i] = (ssize_t) floor(x[i]);
		}
	}

	for (size_t i = 0; i != numel; ++i) {
		ssize_t const bin = (6 + y[i]);
		++hist[bin];
	}

	double avg = 0;
	for (size_t i = 0; i != numel; ++i) {
		avg += x[i];
	}
	avg /= ((double) numel);

	double std = 0;
	for (size_t i = 0; i != numel; ++i) {
		std += (avg - x[i]) * (avg - x[i]);
	}
	std /= (((double) numel) - 1.0);
	std = sqrt(std);

	FILE **f = (FILE**) util::fopen("hist.txt", "w");
	for (size_t bin = 0; bin != bins; ++bin) {
		fprintf(*f, "%zd\n", hist[bin]);
	}

	printf("avg: %f\n", avg);
	printf("std: %f\n", std);
	printf("histogram of Gaussian random numbers has been exported to hist.txt\n");
	f = (FILE**) util::fclose(f);
	util::clearall();
}

void tutil19 (void)
{
	Vector *r = new Vector();
	double const length = 0;
	double const width = 0;
	double const height = 0;
	BoundingBox *bb = new BoundingBox(r, length, width, height);
	struct Brownian *Brownian = new struct Brownian();
	Stack *stack = new Stack();
	Handler *handler = new Handler(stack);
	System *system = new System(bb, Brownian, handler);
	Prompt *prompt = new Prompt();
	Config *config = new Config();
	Timer *timer = new Timer();
	Random *random = new Random(random::NORMAL);
	Looper *looper = new Looper();
	Driver *driver = new Driver();
	Integrator *integrator = new Integrator();
	Logger *logger = new Logger();
	BDX *App = new BDX(prompt,
			   config,
			   timer,
			   random,
			   looper,
			   driver,
			   integrator,
			   logger,
			   system);

	config->load();
	config->parse();
	config->config();

	stack = new Stack();
	void *data = lmp::load();
	size_t const num_particles = lmp::parse(data, stack);
	const double **it = (const double**) stack->begin();
	for (size_t i = 0; i != num_particles; ++i) {
		double const a = 1.0;
		ID *id = new ID(i);
		Kind *kind = new Kind(SPHERE);

		it += 2; // skips LAMMPS ID and Group

		const double **coords = it;
		double const x = *coords[0];
		double const y = *coords[1];
		double const z = *coords[2];

		it += 3;

		Vector *r = new Vector(x, y, z);
		Vector *u = new Vector();
		Vector *E = new Vector();
		Vector *d = new Vector(0, 0, 1);
		Vector *F = new Vector();
		Vector *T = new Vector();
		Stack *stack = new Stack();
		List *list = new List(stack);
		Particle *particle = _Particle(r, u, E, d, F, T, list, id, kind, a, 0, 0);
		handler->add(particle);

		it += 3; // skips optional director (of zeros)
	}

	App->_exec_ = true;
	App->looper->loop();
	util::clearall();
}

void tutil20 (void)
{
	FILE **conf = (FILE**) util::fopen("conf.json", "r");
	FILE **lmp = (FILE**) util::fopen("data.lmp", "r");
	conf = (FILE**) util::fclose(conf);
	lmp = (FILE**) util::fclose(lmp);
	util::fcloseall();
	util::clearall();
}

/*

void tutil21(void)
- imports LAMMPS (unit) spheres data
- performs a 15 minute simulation test run
- checks that no particle is outside the system boundaries when the BDX simulation ends
- displays the outcome of the test on the console

*/

void tutil21 (void)
{
	double const length = 0;
	double const width = 0;
	double const height = 0;
	BoundingBox *bb = new BoundingBox(new Vector(), length, width, height);
	struct Brownian *Brownian = new struct Brownian();
	Handler *handler = new Handler(new Stack());
	System *system = new System(bb, Brownian, handler);
	Prompt *prompt = new Prompt();
	Config *config = new Config();
	ssize_t const walltime = 15 * 60;
	Timer *timer = new Timer(walltime);
	Random *random = new Random(random::NORMAL);
	Looper *looper = new Looper();
	Driver *driver = new Driver();
	Integrator *integrator = new Integrator();
	Logger *logger = new Logger();
	BDX *App = new BDX(prompt,
			   config,
			   timer,
			   random,
			   looper,
			   driver,
			   integrator,
			   logger,
			   system);

	os::print("configuring BDX App\n");
	config->load();
	config->parse();
	config->config();

	Stack *stack = new Stack();
	void *data = lmp::load();
	size_t const num_particles = lmp::parse(data, stack);
	const double **it = (const double**) stack->begin();
	for (size_t i = 0; i != num_particles; ++i) {
		double const a = 1.0;
		ID *id = new ID(i);
		Kind *kind = new Kind(SPHERE);

		it += 2; // skips LAMMPS ID and Group

		const double **coords = it;
		double const x = *coords[0];
		double const y = *coords[1];
		double const z = *coords[2];

		it += 3;

		Vector *r = new Vector(x, y, z);
		Vector *u = new Vector();
		Vector *E = new Vector();
		Vector *d = new Vector(0, 0, 1);
		Vector *F = new Vector();
		Vector *T = new Vector();
		List *list = new List(new Stack());
		Particle *particle = _Particle(r, u, E, d, F, T, list, id, kind, a, 0, 0);
		handler->add(particle);

		it += 3; // skips optional director (of zeros)
	}

	os::print("executing BDX test-run\n");
	App->_exec_ = true;
	App->looper->loop();

	ssize_t fails = 0;
	Handler *h = handler;
	for (Particle **particles = h->begin(); particles != h->end(); ++particles) {

		Particle *p = *particles;

		if (p->r->x < -0.5 * bb->length() || p->r->x > 0.5 * bb->length()) {
			++fails;
			break;
		}

		if (p->r->y < -0.5 * bb->width() || p->r->y > 0.5 * bb->width()) {
			++fails;
			break;
		}

		if (p->r->z < -0.5 * bb->height() || p->r->z > 0.5 * bb->height()) {
			++fails;
			break;
		}
	}

	os::print("particle-container-test: ");
	if (fails != 0) {
		os::print("FAIL\n");
	} else {
		os::print("PASS\n");
	}

	util::clearall();
}

/*

BDX                                             December 31, 2023

Copyright (C) 2023 Misael Díaz-Maldonado
Copyright (C) 2024 UCF-Research Group

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.

author: @misael-diaz
source: src/test/util/test.cpp

References:
[0] A Koenig and B Moo, Accelerated C++ Practical Programming by Example.
[1] MP Allen and DJ Tildesley, Computer Simulation of Liquids.
[2] S Kim and S Karrila, Microhydrodynamics.

*/
