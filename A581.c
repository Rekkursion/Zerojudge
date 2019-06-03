#pragma warning (disable:4996)

#include <stdio.h>
#include <math.h>
#define MIN_ROOT 0.0
#define MAX_ROOT 1.0
#define ZERO_CHECK_THRESHOLD 1e-7
#define STEP_SIZE 0.01
#define PRECISION1 0.001
#define PRECISION2 0.0001
#define PRECISION3 0.00001
#define is_zero(a) ((a) < ZERO_CHECK_THRESHOLD)

inline double f(double*, double*, double*, double*, double*, double*, double);
int main() {
	double p, q, r, s, t, u;
	while (~scanf("%lf %lf %lf %lf %lf %lf", &p, &q, &r, &s, &t, &u)) {
		double x1, x2, f_of_x1, f_of_x2;
		double ans = 0.0;
		int finished = 0;

		for (double offset = 0.0; offset < 1.0 && !finished; offset += STEP_SIZE) {
			x1 = MIN_ROOT + offset;
			x2 = x1 + STEP_SIZE;

			f_of_x1 = f(&p, &q, &r, &s, &t, &u, x1);
			f_of_x2 = f(&p, &q, &r, &s, &t, &u, x2);

			if (is_zero(fabs(f_of_x1))) {
				ans = x1;
				finished = 1;
				break;
			}
			if (is_zero(fabs(f_of_x2))) {
				ans = x2;
				finished = 1;
				break;
			}

			if ((f_of_x1 < 0.0 && f_of_x2 > 0.0) || (f_of_x1 > 0.0 && f_of_x2 < 0.0)) {
				ans = x1;
				finished = 1;
				break;
			}
		}

		for (double offset = 0.0; offset < PRECISION1 * 10.0; offset += PRECISION1) {
			x1 = ans + offset;
			x2 = x1 + PRECISION1;

			f_of_x1 = f(&p, &q, &r, &s, &t, &u, x1);
			f_of_x2 = f(&p, &q, &r, &s, &t, &u, x2);

			if ((f_of_x1 < 0.0 && f_of_x2 > 0.0) || (f_of_x1 > 0.0 && f_of_x2 < 0.0)) {
				ans = x1;
				finished = 1;
				break;
			}
		}

		for (double offset = 0.0; offset < PRECISION2 * 10.0; offset += PRECISION2) {
			x1 = ans + offset;
			x2 = x1 + PRECISION2;

			f_of_x1 = f(&p, &q, &r, &s, &t, &u, x1);
			f_of_x2 = f(&p, &q, &r, &s, &t, &u, x2);

			if ((f_of_x1 < 0.0 && f_of_x2 > 0.0) || (f_of_x1 > 0.0 && f_of_x2 < 0.0)) {
				ans = x1;
				finished = 1;
				break;
			}
		}

		for (double offset = 0.0; offset < PRECISION3 * 10.0; offset += PRECISION3) {
			x1 = ans + offset;
			x2 = x1 + PRECISION3;

			f_of_x1 = f(&p, &q, &r, &s, &t, &u, x1);
			f_of_x2 = f(&p, &q, &r, &s, &t, &u, x2);

			if ((f_of_x1 < 0.0 && f_of_x2 > 0.0) || (f_of_x1 > 0.0 && f_of_x2 < 0.0)) {
				ans = x1;
				finished = 1;
				break;
			}
		}

		if (finished)
			printf("%.4lf\n", ans);
		else
			puts("No solution");
	}

	return 0;
}

double f(double* p, double* q, double* r, double* s, double* t, double* u, double x) {
	return (*p)* exp(-x) + (*q) * sin(x) + (*r) * cos(x) + (*s) * tan(x) + (*t) * (x * x) + (*u);
}
