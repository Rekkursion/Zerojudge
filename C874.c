#pragma warning (disable:4996)

#include <stdio.h>
#include <string.h>
#define MAXN 120
#define MAXL 2002

char sideNum[MAXN + 1][MAXL];
char triNum[MAXN + 1][MAXL];
char acumNum[MAXN + 1][MAXL];
int tmp[MAXL];

void solve();
void bigAdd(char*, char*, char*);
int main() {
	solve();

	int n;
	while (~scanf("%d", &n))
		printf("%s\n", acumNum[n]);

	return 0;
}

void solve() {
	strcpy(sideNum[1], "3");
	strcpy(triNum[1], "1");
	strcpy(acumNum[1], "1");
	for (int k = 2; k <= MAXN; ++k) {
		strcpy(sideNum[k], sideNum[k - 1]);
		for (int i = 0; i < 3; ++i)
			bigAdd(sideNum[k], sideNum[k - 1], sideNum[k]);
		bigAdd(sideNum[k - 1], triNum[k - 1], triNum[k]);
		bigAdd(acumNum[k - 1], triNum[k], acumNum[k]);
	}

	return;
}

void bigAdd(char* a, char* b, char* dst) {
	memset(tmp, 0, sizeof(tmp));

	int aLen = strlen(a), av;
	int bLen = strlen(b), bv;
	int i = 0, carry = 0, sum = 0;

	for (int k = aLen - 1, j = bLen - 1; k >= 0 || j >= 0 || carry; --k, --j) {
		av = k < 0 ? 0 : a[k] - 48;
		bv = j < 0 ? 0 : b[j] - 48;

		sum = av + bv + carry;
		if (sum >= 10) {
			tmp[i++] = sum - 10;
			carry = 1;
		}
		else {
			tmp[i++] = sum;
			carry = 0;
		}
	}

	int start = 0, d = 0;
	for (int k = i; k >= 0; --k) {
		if (!start && tmp[k])
			start = 1;
		if (start)
			dst[d++] = tmp[k] + 48;
	}
	if (d == 0)
		dst[d++] = '0';
	dst[d] = '\0';

	return;
}
