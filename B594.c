#pragma warning (disable:4996)

#include <stdio.h>
#include <math.h>
typedef long long ll;

static inline void printNonNegativeInt(const int* const);
int main() {
	int n, half, ways;
	ll alpha, D;
	double D_sqrt, p;

	while (~scanf("%d", &n) && n) {
		half = (n & 1) ? (n >> 1) + 1 : (n >> 1);
		ways = 0;

		for (int q = 1; q <= half; ++q) {
			alpha = -((ll)q * q) - (ll)q + ((ll)n << 1);
			D = 1 - (alpha << 2);

			if (D < 0)
				continue;

			D_sqrt = sqrt((double)D);
			if (D_sqrt - (int)D_sqrt == 0) {
				p = (1.0 + D_sqrt) / 2.0;
				if (p - (int)p == 0 && (int)p > 0)
					++ways;
			}
		}

		printNonNegativeInt(&ways), putchar('\n');
	}

	return 0;
}

static inline void printNonNegativeInt(const int* const integer) {
	if (*integer == 0) {
		putchar('0');
		return;
	}

	static char str[22];
	static int idx;
	static int number;

	number = *integer;
	idx = 0;

	while (number > 0) {
		str[idx++] = number % 10;
		number /= 10;
	}

	while (idx)
		putchar(str[--idx] + 48);

	return;
}
