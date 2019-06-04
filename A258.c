#pragma warning (disable:4996)

#include <stdio.h>
// ax + by = gcd(a, b)
int x, y, gcd;

int getMultiplicativeInverse(int, int);
int exgcd(int, int);
int main() {
	int K;
	scanf("%d", &K);

	while (K--) {
		int a, b, c, m, inv;
		long long d;
		scanf("%d %d %d", &m, &a, &b);

		inv = getMultiplicativeInverse(a, m);
		if (inv == -1)
			printf("No inverse, gcd(a,m)=%d\n", gcd);
		else {
			c = inv;
			d = (long long)inv * -(b % m);

			while (d < 0ll)
				d += (long long)m;
			d %= (long long)m;

			printf("%d %lld\n", c, d);
		}
	}

	return 0;
}

int getMultiplicativeInverse(int a, int b) {
	if (b == 1)
		return -1;

	gcd = exgcd(a, b);
	if (gcd == 1)
		return x < 0 ? x + b : x;
	return -1;
}

int exgcd(int a, int b) {
	if (a % b == 0) {
		x = 0;
		y = 1;
		return b;
	}

	int _gcd = exgcd(b, a % b);
	int tmp = x;

	x = y;
	y = tmp + y * -(a / b);

	return _gcd;
}
