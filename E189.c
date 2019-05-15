#pragma warning (disable:4996)

#include <stdio.h>
char answerSheet[2][4] = { "NO", "YES" };

int main() {
	int n;
	while (~scanf("%d", &n)) {
		int oddSum = 0, evenSum = 0;

		for (int k = 0; k < 32; ++k) {
			if (k & 1)
				oddSum += ((n >> k) & 1);
			else
				evenSum += ((n >> k) & 1);

			if (oddSum >= 3)
				oddSum -= 3;
			if (evenSum >= 3)
				evenSum -= 3;
		}

		printf("%s\n", answerSheet[(oddSum - evenSum == 0)]);
	}

	return 0;
}
