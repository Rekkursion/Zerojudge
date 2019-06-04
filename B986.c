#pragma warning (disable:4996)

#include <stdio.h>
// ax + by = gcd(a, b)
// must init: x = 0, y = 1
int x, y;

int exgcd(int, int);
int main() {
	int a, b, gcd;
	scanf("%d %d", &a, &b);

	gcd = exgcd(a, b);
	//printf("%d * %d + %d * %d = %d\n", a, x, b, y, gcd);

	printf("%d\n", x < 0 ? x + b : x);

	return 0;
}

int exgcd(int a, int b) {
	if (a % b == 0) {
		x = 0;
		y = 1;
		return b;
	}

	int gcd = exgcd(b, a % b);
	int tmp = x;

	x = y;
	y = tmp + y * -(a / b);

	return gcd;
}
