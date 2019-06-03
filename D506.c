#pragma warning (disable:4996)

#include <stdio.h>
#include <string.h>
#define MAXL 80000
#define BASE 1000000000
typedef long long ll;
ll ans[MAXL], ansIdx;
ll tmp[MAXL], tmpIdx;
ll base7[MAXL], base7Idx;

inline void solve();
inline void bigPow(ll*, int, ll*, int, ll*, int*);
int main() {
	solve();
	return 0;
}


void solve() {
	int exp = 86495;

	ans[0] = 1; ansIdx = 1;
	base7[0] = 7; base7Idx = 1;

	while (exp > 0) {
		if (exp & 1)
			bigPow(ans, ansIdx, base7, base7Idx, ans, &ansIdx);

		exp >>= 1;
		bigPow(base7, base7Idx, base7, base7Idx, base7, &base7Idx);
	}

	printf("%lld", ans[0]);
	for (int k = 1; k < ansIdx; ++k)
		printf("%09lld", ans[k]);
	putchar('\n');

	return;
}

void bigPow(ll * a, int aLen, ll * b, int bLen, ll * dst, int* dstLen) {
	memset(tmp, 0, sizeof(tmp));

	int k, j, i = 0, h = 0;
	for (k = aLen - 1, i = 0; k >= 0; --k, ++i) {
		for (j = bLen - 1, h = i; j >= 0; --j, ++h) {
			ll v = a[k] * b[j];

			tmp[h] += v;
			if (tmp[h] >= (ll)BASE) {
				tmp[h + 1] += tmp[h] / (ll)BASE;
				tmp[h] %= (ll)BASE;
			}
		}
	}

	int start = 0;
	for (i = h + 3, k = 0; i >= 0; --i) {
		if (!start && tmp[i])
			start = 1;
		if (start)
			dst[k++] = tmp[i];
	}
	*dstLen = k;

	return;
}
