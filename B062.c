#pragma warning (disable:4996)

#include <stdio.h>
#define MAXN 50
#define MAXCITY 32

char adjMat[MAXCITY][MAXCITY + 1];
int dp[MAXCITY][MAXN + 1];

int main() {
	int cityNum, src, dst, maxLength;

	while (~scanf("%d", &cityNum)) {
		for (int r = 0; r < cityNum; ++r)
			scanf("%s", adjMat[r]);
		scanf("%d %d %d", &src, &dst, &maxLength);
		--src; --dst;

		for (int r = 0; r < cityNum; ++r)
			dp[r][0] = 0;
		dp[src][0] = 1;

		for (int n = 1; n <= maxLength; ++n) {
			for (int city = 0; city < cityNum; ++city) {
				int connectedNum = 0;
				for (int a = 0; a < cityNum; ++a) {
					if (adjMat[city][a] == '1')
						connectedNum += dp[a][n - 1];
				}
				dp[city][n] = connectedNum;
			}
		}

		int res = 0;
		for (int n = 0; n <= maxLength; ++n)
			res += dp[dst][n];
		printf("%d\n", res);
	}

	return 0;
}
