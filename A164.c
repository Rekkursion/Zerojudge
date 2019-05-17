#pragma warning (disable:4996)

#include <stdio.h>
#include <string.h>
#define MAXN 200002
#define MAXL 2000002
typedef int bool;
typedef long long ll;

int n;
int arr[MAXN + 1];
char inpString[MAXL];

typedef struct AnswerStructure {
	ll val;
	int leftIdx, rightIdx;
}Answer;
Answer newAnswer(ll val, int lIdx, int rIdx) {
	Answer ret;
	ret.val = val;
	ret.leftIdx = lIdx;
	ret.rightIdx = rIdx;
	return ret;
}

void getInput();
Answer solve_iteration(int, int);

int main() {
	Answer ret;
	int q, l, r, kase = 0;

	while (~scanf("%d %d", &n, &q)) {
		getInput();
		printf("Case %d:\n", ++kase);

		for (int k = 0; k < q; ++k) {
			scanf("%d %d", &l, &r);

			ret = solve_iteration(l - 1, r - 1);
			printf("%d %d %lld\n", ret.leftIdx + 1, ret.rightIdx + 1, ret.val);
		}
	}

	return 0;
}

void getInput() {
	getchar();

	int k, inpLen, num, arrIdx = 0;
	bool started;
	bool isNegative;

	while (arrIdx < n) {
		gets(inpString);
		inpLen = strlen(inpString);

		num = 0;
		started = 0, isNegative = 0;

		for (k = 0; k < inpLen; ++k) {
			if (inpString[k] == ' ') {
				if (!started)
					continue;

				if (isNegative) {
					num = -num;
					isNegative = 0;
				}

				arr[arrIdx++] = num;
				num = 0;
				started = 0;
			}

			else if (inpString[k] == '-')
				isNegative = 1;

			else if (inpString[k] >= '0' && inpString[k] <= '9') {
				started = 1;
				num = (num * 10) + (inpString[k] - 48);
			}
		}
		if (started)
			arr[arrIdx++] = (isNegative) ? -num : num;
	}

	return;
}

Answer solve_iteration(int _l, int _r) {
	ll sum = 0ll, maxValue = arr[_l];
	int k, leftIdx = _l, rightIdx = _l, tmpLeftIdx = _l;

	for (k = _l; k <= _r; ++k) {
		if (sum < 0ll) {
			sum = 0ll;
			tmpLeftIdx = k;
		}
		sum += (ll)arr[k];

		if (sum > maxValue) {
			maxValue = sum;
			leftIdx = tmpLeftIdx;
			rightIdx = k;
		}
	}

	return newAnswer(maxValue, leftIdx, rightIdx);
}
