#pragma warning (disable:4996)

#include <stdio.h>

int main() {
	int n, upBound;
	while (~scanf("%d", &n) && n) {
		if (n == 1) {
			puts("1");
			continue;
		}

		upBound = 1;
		while (upBound < n)
			upBound <<= 1;
		printf("%d\n", (n - (upBound >> 1)) << 1);
	}

	return 0;
}
