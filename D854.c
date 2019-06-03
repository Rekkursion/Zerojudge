#pragma warning (disable:4996)

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define MIN_ROOT (-100.0)
#define MAX_ROOT 100.0
#define ZERO_CHECK_THRESHOLD 1e-7
#define PRECISION 3
#define is_zero(a) ((a) < ZERO_CHECK_THRESHOLD)

inline double f(double, double, double, double, double);
int cmp(const void*, const void*);
int main() {
	double a, b, c, d;
	scanf("%lf %lf %lf %lf", &a, &b, &c, &d);

	double curX = MIN_ROOT;
	double f_of_x = 0.0, last_f_of_x;
	double ans[3];
	int ansIdx = 0;

	do {
		f_of_x = f(a, b, c, d, curX);
		if (is_zero(fabsl(f_of_x)))
			ans[ansIdx++] = curX;
		else
			break;
		curX += 1.0;
	} while (ansIdx < 3 && curX <= MAX_ROOT);

	last_f_of_x = f_of_x;
	for (curX += 1.0; ansIdx < 3 && curX <= MAX_ROOT; curX += 1.0) {
		f_of_x = f(a, b, c, d, curX);

		// f of current x is zero
		if (is_zero(fabsl(f_of_x))) {
			ans[ansIdx++] = curX;
			for (curX += 1.0; ansIdx < 3 && curX <= MAX_ROOT; curX += 1.0) {
				last_f_of_x = f(a, b, c, d, curX);
				if (is_zero(fabsl(last_f_of_x)))
					ans[ansIdx++] = curX;
				else
					break;
			}
		}

		// not zero
		else {
			// must have a root
			if ((last_f_of_x < 0.0 && f_of_x > 0.0) || (last_f_of_x > 0.0 && f_of_x < 0.0)) {
				double prec = 0.1;
				double x1, x2, f_of_x1, f_of_x2;
				double x = curX - 1.0;
				int finished = 0;

				for (int p = 0; p < PRECISION && !finished; ++p) {
					for (double offset = 0.0; offset < prec * 10.0; offset += prec) {
						x1 = x + offset;
						x2 = x + (offset + prec);

						f_of_x1 = f(a, b, c, d, x1);
						f_of_x2 = f(a, b, c, d, x2);

						if (is_zero(fabsl(f_of_x1))) {
							finished = 1;
							ans[ansIdx++] = x1;
							break;
						}
						if (is_zero(fabsl(f_of_x2))) {
							finished = 1;
							ans[ansIdx++] = x2;
							break;
						}

						if ((f_of_x1 < 0.0 && f_of_x2 > 0.0) || (f_of_x1 > 0.0 && f_of_x2 < 0.0)) {
							x += offset;
							break;
						}
					}

					prec *= prec;
				}

				if (!finished)
					ans[ansIdx++] = x;
			}

			last_f_of_x = f_of_x;
		}
	}

	qsort(ans, ansIdx, sizeof(double), cmp);
	for (int k = 0; k < ansIdx; ++k)
		printf("%.2lf ", ans[k]);
	putchar('\n');

	return 0;
}

double f(double a, double b, double c, double d, double x) {
	return a * (x * x * x) + b * (x * x) + c * x + d;
}

int cmp(const void* a, const void* b) {
	return *(double*)a > *(double*)b;
}
