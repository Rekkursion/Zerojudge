#pragma warning (disable:4996)

#include <stdio.h>
#define MAXN 20

int bagList[MAXN];
int n, k, target, found;

void dfs(int, int, int);
int main() {
	int zeroNum;

	while (~scanf("%d %d %d", &n, &k, &target)) {
		zeroNum = 0;
		for (int i = 0; i < n; ++i) {
			scanf("%d", &bagList[i]);
			if (bagList[i] == 0)
				++zeroNum;
		}

		if (target == 0)
			found = (zeroNum >= k);
		else {
			found = 0;
			dfs(0, 0, 0);
		}

		puts(found ? "YES" : "NO");
	}

	return 0;
}

void dfs(int bagIdx, int curBagNum, int curMoney) {
	if (found)
		return;

	if (curBagNum == k) {
		if (curMoney == target)
			found = 1;
		return;
	}

	if (curMoney >= target)
		return;

	if (bagIdx >= n)
		return;

	for (int i = bagIdx; i < n; ++i) {
		if (curBagNum + 1 == k && curMoney + bagList[i] != target)
			continue;
		if (curBagNum < k && curMoney + bagList[i] <= target)
			dfs(i + 1, curBagNum + 1, curMoney + bagList[i]);
	}

	return;
}
