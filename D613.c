#pragma warning (disable:4996)

#include <stdio.h>
#include <stdbool.h>
#define MAX_PRIME_NUM 100000
#define MAX_PRIME 1299709
bool isPrime[MAX_PRIME + 1];
int primeList[MAX_PRIME_NUM + 17];

inline void sieve();
inline int lowerBound(const int* const);
int main() {
	sieve();

	int n, primeIdx;
	while (~scanf("%d", &n) && n) {
		if (isPrime[n])
			puts("0");
		else
			primeIdx = lowerBound(&n),
			printf("%d\n", primeList[primeIdx] - primeList[primeIdx - 1]);
	}

	return 0;
}

void sieve() {
	for (int k = 3; k <= MAX_PRIME; ++k)
		isPrime[k] = (k & 1) ? true : false;
	isPrime[2] = true;

	for (int k = 3; k * k <= MAX_PRIME; k += 2) {
		if (isPrime[k]) {
			int j = 2;
			while (k * j <= MAX_PRIME)
				isPrime[k * j] = false, ++j;
		}
	}

	int primeNum = 1;

	primeList[0] = 2;
	for (int k = 3; k <= MAX_PRIME; ++k) {
		if (isPrime[k])
			primeList[primeNum++] = k;
	}

	return;
}

// from C++ STL
int lowerBound(const int* const target) {
	int first = 0, middle;
	int half, len;
	len = MAX_PRIME_NUM;

	while (len > 0) {
		half = len >> 1;
		middle = first + half;
		if (primeList[middle] < *target)
			first = middle + 1,
			len = len - half - 1;
		else
			len = half;
	}

	return first;
}
