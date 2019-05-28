#pragma warning (disable:4996)

#include <stdio.h>
#define TAX_THRESHOLD 10000ll
#define TAX 800ll
typedef long long ll;

int main() {
	int integer, floatingPoint;
	ll orig, off;

	while (~scanf("%d%*c%d", &integer, &floatingPoint)) {
		orig = ((ll)integer * 100ll) + (ll)floatingPoint;

		if (orig <= 10000ll)
			off = (orig * 9ll) / 10ll;
		else if (orig <= 50000ll)
			off = (orig * 8ll) / 10ll;
		else
			off = (orig * 6ll) / 10ll;

		if (orig < TAX_THRESHOLD)
			off += TAX;

		printf("$%lld.%02lld\n", off / 100ll, off % 100ll);
	}

	return 0;
}
