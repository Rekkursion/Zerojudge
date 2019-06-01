#pragma warning (disable:4996)

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

inline void swap(int*, int*);
inline double heronsFormula(int, int, int);
inline double getSquaredDistance(double, double, double, double);
int cmp(const void*, const void*);
int main() {
	int n;
	double lenA, lenB, lenC, lens[3];
	double area, p, q, g_x, g_y, ga_squared, gb_squared, gc_squared;

	while (~scanf("%d", &n) && n) {
		while (n--) {
			scanf("%lf %lf %lf", &lens[0], &lens[1], &lens[2]);

			qsort(lens, 3, sizeof(double), cmp);
			lenB = lens[0];
			lenA = lens[1];
			lenC = lens[2];

			area = heronsFormula(lenA, lenB, lenC);
			q = (2.0 * area) / lenC;
			p = sqrt((lenA * lenA) - (q * q));

			g_x = (p + lenC) / 3.0;
			g_y = q / 3.0;

			ga_squared = getSquaredDistance(0.0, 0.0, p, q);
			gb_squared = getSquaredDistance(lenC, 0.0, p, q);
			gc_squared = getSquaredDistance(0.0, 0.0, lenC, 0.0);

			printf("%.1lf\n", (ga_squared + gb_squared + gc_squared) / 3.0);
		}
	}

	return 0;
}

inline void swap(int* x, int* y) {
	int* tmp = x; x = y; y = tmp;
	return;
}

inline double heronsFormula(int a, int b, int c) {
	double s = ((double)a + b + c) / 2.0;
	return sqrt(s * (s - a) * (s - b) * (s - c));
}

inline double getSquaredDistance(double pt1_x, double pt1_y, double pt2_x, double pt2_y) {
	return ((pt1_x - pt2_x) * (pt1_x - pt2_x)) + ((pt1_y - pt2_y) * (pt1_y - pt2_y));
}

int cmp(const void* a, const void* b) {
	return (*((double*)a)) - (*((double*)b));
}
