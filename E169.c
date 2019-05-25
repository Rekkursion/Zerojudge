#pragma warning (disable:4996)

#include <stdio.h>
typedef unsigned long long ull;
int videos[101];

static inline int readNonNegativeInt(int* const);
int main() {
	int n, p;

	while (readNonNegativeInt(&n) && n) {
		for (int k = 0; k <= 100; ++k)
			videos[k] = 0;

		for (int k = 0; k < n; ++k) {
			readNonNegativeInt(&p);
			++videos[p % 100];
		}

		ull sum = 0ull;
		for (int l = 1; l < 50; ++l)
			sum += (ull)videos[l] * (ull)videos[100 - l];

		if (videos[0] > 1)
			sum += ((ull)videos[0] * (ull)(videos[0] - 1ull)) / 2ull;
		if(videos[50] > 1)
			sum += ((ull)videos[50] * (ull)(videos[50] - 1ull)) / 2ull;

		printf("%llu\n", sum);
	}

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
