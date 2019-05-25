#pragma warning (disable:4996)

#include <stdio.h>
#define MAXN 100000
#define MODEE 1234567
int ways[MAXN + 1];

static inline int readNonNegativeInt(int* const);
int main() {
	int n, m, dst;

	readNonNegativeInt(&n);
	ways[1] = 1;

	for (int k = 1; k <= n; ++k) {
		readNonNegativeInt(&m);

		for (int j = 0; j < m; ++j) {
			readNonNegativeInt(&dst);

			ways[dst] += ways[k];
			if (ways[dst] >= MODEE)
				ways[dst] -= MODEE;
		}
	}

	printf("%d\n", ways[n]);
	return 0;
}

static inline int readNonNegativeInt(int* const integer) {
	static char ch;
	while ((ch = getchar()) < 48 || ch > 57);

	if (ch < 48 || ch > 57)
		return 0;

	(*integer) = ch - 48;
	while ((ch = getchar()) >= 48 && ch <= 57)
		(*integer) = ((*integer) * 10) + (ch - 48);

	return 1;
}
