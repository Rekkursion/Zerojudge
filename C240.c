#pragma warning (disable:4996)

#include <stdio.h>
#include <string.h>
#define MAXW 10000
#define MAXN 10000
#define max(a, b) ((a) < (b) ? (b) : (a))
int dp[MAXW + 1];
int values[MAXN], weights[MAXN];

int main() {
	int n, w;
	while (~scanf("%d %d", &n, &w)) {
		for (int k = 0; k < n; ++k)
			scanf("%d %d", &values[k], &weights[k]);

		memset(dp, 0, sizeof(int) * (w + 1));
		for (int k = 0; k < n; ++k) {
			for (int j = w; j >= weights[k]; --j) {
				int anotherChoice = dp[j - weights[k]] + values[k];
				dp[j] = max(dp[j], anotherChoice);
			}
		}

		printf("%d\n", dp[w]);
	}

	return 0;
}
