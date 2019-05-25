#pragma warning (disable:4996)

#include <stdio.h>
#define MAXN 18
#define max(a, b) ((a) < (b) ? (b) : (a))
typedef long long ll;
int arr[MAXN];

int main() {
	ll posProduct, negProduct, maxProduct;
	int n, kase = 0;

	while (~scanf("%d", &n)) {
		for (int k = 0; k < n; ++k)
			scanf("%d", &arr[k]);

		maxProduct = posProduct = negProduct = 0ll;
		for (int k = 0; k < n; ++k) {
			// number is not zero
			if (arr[k] != 0)
				if (arr[k] > 0) {
					posProduct = posProduct == 0ll ? (ll)arr[k] : posProduct * (ll)arr[k];
					negProduct *= (ll)arr[k];
				}
				else {
					ll temp = posProduct * (ll)arr[k];

					posProduct = negProduct * (ll)arr[k];
					negProduct = temp == 0ll ? (ll)arr[k] : temp;
				}

			// number is zero
			else {
				maxProduct = max(maxProduct, posProduct);

				while (k < n && arr[k++] == 0);
				--k;
				posProduct = negProduct = 0ll;
			}

			maxProduct = max(maxProduct, posProduct);
		}

		printf("Case #%d: The maximum product is %lld.\n\n", ++kase, maxProduct);
	}

	return 0;
}
