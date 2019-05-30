#pragma warning (disable:4996)

#include <stdio.h>
#define MAXM 200002
#define abs(a) ((a) < 0 ? (-(a)) : (a))

int binList[MAXM];
int numList[MAXM + 1];
int ansList[MAXM + 1];

int main() {
	int n, m;
	scanf("%d %d", &n, &m);

	for (int k = 0; k < m; ++k)
		scanf("%d", &binList[k]);

	for (int k = 0; k < n; ++k) {
		for (int j = 0; j <= m; ++j)
			scanf("%d", &numList[j]);

		int curNum = numList[m];
		int isAns = 1;
		for (int j = m - 1, i = m - 1; j >= 0; --j, --i) {
			if ((curNum >= numList[j]) != binList[i]) {
				isAns = 0;
				break;
			}
			curNum = abs(numList[j] - numList[j + 1]);
		}

		if (isAns) {
			for (int j = 0; j <= m; ++j)
				ansList[j] = numList[j];
		}
	}

	for (int k = 0; k <= m; ++k)
		printf("%d ", ansList[k]);
	putchar('\n');

	return 0;
}
