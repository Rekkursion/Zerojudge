#pragma warning (disable:4996)

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#define MAX_PRIME 100000
#define max(u, v) ((u) < (v) ? (v) : (u))
//#define QQ
typedef unsigned long long ull;

ull primeFactorList[MAX_PRIME], maxPrimeFactor;
bool isPrime[MAX_PRIME];
ull primeList[MAX_PRIME], primeNum;

void sieve();
void reduct(ull*, ull*);
ull getGcd(ull, ull);
ull getPrimeFactors(ull, ull);
int main() {
	sieve();

	ull a, b, c, d, m, n, t, u;
	while (~scanf("%llu %llu %llu %llu", &a, &b, &c, &d)) {
		reduct(&a, &b), reduct(&c, &d);

#ifdef QQ
		printf("a = %llu | b = %llu | c = %llu | d = %llu\n", a, b, c, d);
		printf("h = %llu\n", d);
#endif

		t = getPrimeFactors(a, c);
		m = 1ull;
		for (int k = 0; k < primeNum && primeList[k] <= maxPrimeFactor; ++k) {
			ull prime = primeList[k];
			ull exp = primeFactorList[prime];

			if (exp >= d)
				m *= (ull)pow((double)prime, (double)(exp / d));
			t *= (ull)pow((double)prime, (double)(exp % d));
		}

		u = getPrimeFactors(b, c);
		n = 1ull;
		for (int k = 0; k < primeNum && primeList[k] <= maxPrimeFactor; ++k) {
			ull prime = primeList[k];
			ull exp = primeFactorList[prime];

			if (exp >= d)
				n *= (ull)pow((double)prime, (double)(exp / d));
			u *= (ull)pow((double)prime, (double)(exp % d));
		}

#ifdef QQ
		ull remain_of_a_exp_c = getPrimeFactors(a, c);
		for (int k = 0; k < primeNum && primeList[k] <= maxPrimeFactor; ++k) {
			if (primeFactorList[primeList[k]])
				printf("%llu^%llu * ", primeList[k], primeFactorList[primeList[k]]);
		}
		printf("%llu\n", remain_of_a_exp_c);
		ull remain_of_b_exp_c = getPrimeFactors(b, c);
		for (int k = 0; k < primeNum && primeList[k] <= maxPrimeFactor; ++k) {
			if (primeFactorList[primeList[k]])
				printf("%llu^%llu * ", primeList[k], primeFactorList[primeList[k]]);
		}
		printf("%llu\n", remain_of_b_exp_c);
		printf("m = %llu | t = %llu\n", m, t);
		printf("n = %llu | u = %llu\n", n, u);
#endif

		if (m == 1ull && n == 1ull && t == 1ull && u == 1ull)
			puts("1");

		else if (m == 1ull && n == 1ull) {
			if (d > 1ull)
				printf("_/%llu(", d);

			if (u == 1ull)
				printf("%llu", t);
			else
				printf("%llu/%llu", t, u);

			if (d > 1ull)
				puts(")");
			else
				putchar('\n');
		}

		else if (t == 1ull && u == 1ull) {
			if (n == 1ull)
				printf("%llu\n", m);
			else
				printf("%llu/%llu\n", m, n);
		}

		else {
			if (n == 1ull)
				printf("%llu", m);
			else
				printf("%llu/%llu", m, n);

			if (d > 1ull)
				printf("_/%llu(", d);

			if (u == 1ull)
				printf("%llu", t);
			else
				printf("%llu/%llu", t, u);

			if (d > 1ull)
				puts(")");
			else
				putchar('\n');
		}
	}

	return 0;
}

void sieve() {
	for (int k = 3; k < MAX_PRIME; ++k)
		isPrime[k] = (k & 1) ? true : false;
	isPrime[2] = true;

	for (int k = 3; k * k < MAX_PRIME; k += 2) {
		if (isPrime[k]) {
			int j = 2;
			while (k * j < MAX_PRIME)
				isPrime[k * j] = false, ++j;
		}
	}

	primeList[0] = 2;
	primeNum = 1;
	for (int k = 3; k < MAX_PRIME; k += 2) {
		if (isPrime[k])
			primeList[primeNum++] = k;
	}

	return;
}

void reduct(ull* x, ull* y) {
	ull gcd = getGcd(*x, *y);
	*x /= gcd;
	*y /= gcd;

	return;
}

ull getGcd(ull x, ull y) {
	return x % y == 0ull ? y : getGcd(y, x % y);
}

ull getPrimeFactors(ull num, ull exp) {
	memset(primeFactorList, 0, sizeof(primeFactorList));

	for (int k = 0; k < primeNum && num > 0; ++k) {
		ull prime = primeList[k];

		if (num % prime == 0ull) {
			while (num % prime == 0ull)
				++primeFactorList[prime], num /= prime;
			primeFactorList[prime] *= exp;

			maxPrimeFactor = max(maxPrimeFactor, prime);
		}
	}

	return num;
}
