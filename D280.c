#pragma warning (disable:4996)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXN 20
#define MAXM 120
#define MAXL 101
char dp[MAXM + 1][MAXN + 1][MAXL];

void calcAnswer();
char* bigAdd(char*, char*);
int main() {
	calcAnswer();

	int K;
	scanf("%d", &K);

	while (K--) {
		int n, m;
		scanf("%d %d", &n, &m);

		if (n == 0 && m == 0)
			puts("1");
		else if (n <= 0 || m <= 0)
			puts("0");
		else
			puts(dp[m][n]);
	}

	return 0;
}

void calcAnswer() {
	// initialize
	for (int m = 1; m <= MAXM; ++m) {
		for (int n = 1; n <= MAXN; ++n) {
			dp[m][n][0] = (n == 1 && m <= 6) ? '1' : '0';
			dp[m][n][1] = '\0';
		}
	}

	// dynamic programming
	for (int n = 2; n <= MAXN; ++n) {
		for (int m = n; m <= MAXM; ++m) {
			for (int k = m - 1; k >= 1 && k >= m - 6; --k)
				strcpy(dp[m][n], bigAdd(dp[m][n], dp[k][n - 1]));
			if (dp[m][n][0] == '0' && dp[m][n][1] == '\0')
				break;
		}
	}

	return;
}

char* bigAdd(char* a, char* b) {
	char* ret = (char*)malloc(sizeof(char) * MAXL);
	int* tmp = (int*)malloc(sizeof(int) * MAXL);
	int tmpIdx = 0, carry = 0;
	int lenA = strlen(a), lenB = strlen(b);

	for (int k = lenA - 1, j = lenB - 1; k >= 0 || j >= 0 || carry > 0; --k, --j) {
		int va = (k < 0) ? 0 : a[k] - 48;
		int vb = (j < 0) ? 0 : b[j] - 48;
		tmp[tmpIdx++] = (va + vb + carry) % 10;
		carry = ((va + vb + carry) >= 10);
	}

	int start = 0;
	for (carry = 0; tmpIdx >= 0; --tmpIdx) {
		if (!start && tmp[tmpIdx] != 0)
			start = 1;
		if (start)
			ret[carry++] = tmp[tmpIdx] + 48;
	}
	if (carry == 0)
		ret[carry++] = '0';
	ret[carry] = '\0';

	return ret;
}
