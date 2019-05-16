#pragma warning (disable:4996)

#include <stdio.h>
#include <string.h>
#define MAXN 1000
#define MAXL 500005
typedef int bool;

int n;
int arr[MAXN + 1];
char inpString[MAXL];

void getInput();
int solve_iteration();

int main() {
	int ret;
	while (~scanf("%d", &n) && n) {
		getInput();
		ret = solve_iteration();
		printf("%d\n", ret);
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

int solve_iteration() {
	int sum = 0, maxValue = arr[0];
	int k;

	for (int s = 0; s < n; ++s) {
		sum = 0;

		// first iteration
		for (k = s; k < n; ++k) {
			if (sum < 0)
				sum = 0;
			sum += arr[k];

			if (sum > maxValue)
				maxValue = sum;
		}

		// second iteration
		for (k = 0; k < s - 1; ++k) {
			if (sum < 0)
				sum = 0;
			sum += arr[k];

			if (sum > maxValue)
				maxValue = sum;
		}
	}

	return maxValue;
}
