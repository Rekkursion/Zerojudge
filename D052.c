#pragma warning (disable:4996)

#include <stdio.h>
#define MAXN 2000

int wagons[MAXN << 1];
int lis[MAXN << 1];

static inline int readNonNegativeInt(int* const);
inline int getLIS(const int* const);
inline int lowerBound(const int* const, const int* const, const int* const);
int main() {
	int kase, n;
	readNonNegativeInt(&kase);

	while (kase--) {
		readNonNegativeInt(&n);
		for (int k = n; k < (n << 1); ++k)
			readNonNegativeInt(&wagons[k]);
		for (int k = (n << 1) - 1, j = 0; k >= n; --k, ++j)
			wagons[j] = wagons[k];

		printf("%d\n", getLIS(&n));
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

int getLIS(const int* const N) {
	if (*N == 0)
		return 0;

	int doubled_n = (*N) << 1;
	int lisIdx = 1;

	lis[0] = wagons[0];
	for (int k = 1; k < doubled_n; ++k)
		if (wagons[k] > lis[lisIdx - 1])
			lis[lisIdx++] = wagons[k];
		else
			lis[lowerBound(lis, &lisIdx, &wagons[k])] = wagons[k];

	return lisIdx;
}

// from C++ STL
int lowerBound(const int* const arr, const int* const n, const int* const target) {
	int first = 0, middle;
	int half, len;
	len = *n;

	while (len > 0) {
		half = len >> 1;
		middle = first + half;
		if (arr[middle] < *target)
			first = middle + 1,
			len = len - half - 1;
		else
			len = half;
	}

	return first;
}
