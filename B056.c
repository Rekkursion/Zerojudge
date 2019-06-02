#pragma warning (disable:4996)

#include <stdio.h>
typedef long double ldouble;

inline void convertRGB2XYZ(int, int, int, ldouble*, ldouble*, ldouble*);
int main() {
	ldouble x, y, z, avgOfY;
	int n, r, g, b, n_squared;

	while (~scanf("%d", &n)) {
		n_squared = n * n;
		avgOfY = 0.0;

		for (int k = 0; k < n_squared; ++k) {
			scanf("%d %d %d", &r, &g, &b);
			convertRGB2XYZ(r, g, b, &x, &y, &z);
			printf("%.4llf %.4llf %.4llf\n", x, y, z);
			avgOfY += y;
		}

		avgOfY /= (ldouble)n_squared;
		printf("The average of Y is %.4llf\n", avgOfY);
	}

	return 0;
}

void convertRGB2XYZ(int r, int g, int b, ldouble* x, ldouble* y, ldouble* z) {
	*x = 0.5149 * (ldouble)r + 0.3244 * (ldouble)g + 0.1607 * (ldouble)b;
	*y = 0.2654 * (ldouble)r + 0.6704 * (ldouble)g + 0.0642 * (ldouble)b;
	*z = 0.0248 * (ldouble)r + 0.1248 * (ldouble)g + 0.8504 * (ldouble)b;
	return;
}
