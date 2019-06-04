#pragma warning (disable:4996)

#include <stdio.h>
// ax + by = gcd(a, b)
int x, y, gcd;

int getMultiplicativeInverse(int, int);
int exgcd(int, int);
int main() {
	int a, n, inv;

	while (~scanf("%d %d", &a, &n)) {
		inv = getMultiplicativeInverse(a, n);

		if (inv == -1)
			puts("No Inverse");
		else
			printf("%d\n", inv);
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
