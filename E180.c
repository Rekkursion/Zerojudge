#pragma warning (disable:4996)

#include <stdio.h>
#define MAXN 10000

int priceList[MAXN + 1];

int main() {
	int n, own, total;
	while (~scanf("%d", &n) && n) {
		for (int k = 0; k < n; ++k)
			scanf("%d", &priceList[k]);
		priceList[n] = 0;

		total = 0;
		own = -1;
		for (int k = 0; k < n; ++k) {
			if (priceList[k + 1] > priceList[k] && own < 0)
				own = priceList[k];
			if (priceList[k + 1] < priceList[k] && own >= 0)
				total += priceList[k] - own,
				own = -1;
		}

		printf("%d\n", total);
	}

	return 0;
}
