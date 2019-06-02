#pragma warning (disable:4996)

#include <stdio.h>

inline int countIntegerPoint(int, int, int, int);
inline int gcd(int, int);
int main() {
	int x1, y1, x2, y2, x3, y3;
	while (~scanf("%d %d %d %d %d %d", &x1, &y1, &x2, &y2, &x3, &y3) && (x1 || y1 || x2 || y2 || x3 || y3))
		printf("%d\n", countIntegerPoint(x1, y1, x2, y2) + countIntegerPoint(x2, y2, x3, y3) + countIntegerPoint(x1, y1, x3, y3) + 3);

	return 0;
}

int countIntegerPoint(int x1, int y1, int x2, int y2) {
	// a vertical line
	if (x1 == x2)
		return abs(y1 - y2) - 1;

	// a horizontal line
	if (y1 == y2)
		return abs(x1 - x2) - 1;

	// a slashed line
	return gcd(abs(y1 - y2), abs(x1 - x2)) - 1;
}

int gcd(int a, int b) {
	return a % b == 0 ? b : gcd(b, a % b);
}
