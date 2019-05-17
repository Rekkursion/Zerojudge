#pragma warning (disable:4996)

#include <stdio.h>
#include <string.h>
#define MAXL 1000000
int digitsNum[10];
int alternativeSolutionDigitsNum[10];
char score[MAXL + 1], prevScore[MAXL + 1];
char solution[MAXL + 1];

int main() {
	scanf("%s %s", score, prevScore);

	int scoreLen = strlen(score);
	for (int k = 0; k < scoreLen; ++k)
		++digitsNum[score[k] - 48];

	int useAlternative = 0;
	int solutionIdx = 0;
	int altSolutionIdx = 0;
	int altSolutionKeyDigit = 0;

	for (int k = 0; k < scoreLen; ++k) {
		int preScoreDig = prevScore[k] - 48;
		int hasEquals = (digitsNum[preScoreDig] > 0 ? preScoreDig : 0);
		int hasBigger = 0;

		for (int dig = preScoreDig + 1; dig <= 9; ++dig) {
			if (digitsNum[dig] > 0) {
				hasBigger = dig;
				break;
			}
		}

		// only < current digit of previous score
		if (!hasEquals && !hasBigger) {
			useAlternative = 1;
			break;
		}

		// only > current digit of previous score
		else if (!hasEquals && hasBigger) {
			useAlternative = 0;
			--digitsNum[hasBigger];

			solution[solutionIdx++] = hasBigger + 48;
			for (int dig = 1; dig <= 9; ++dig) {
				while (digitsNum[dig]) {
					solution[solutionIdx++] = dig + 48;
					--digitsNum[dig];
				}
			}
			solution[solutionIdx] = '\0';
			break;
		}

		// only = current digit of previous score
		else if (hasEquals && !hasBigger) {
			// the last digit of score and previous score
			if (k == scoreLen - 1) {
				useAlternative = 1;
				break;
			}

			// still have digits to go on
			else {
				useAlternative = 0;
				solution[solutionIdx++] = hasEquals + 48;
				--digitsNum[hasEquals];
			}
		}

		// > or = current digit of previous score
		else {
			// the last digit of score and previous score
			if (k == scoreLen - 1) {
				useAlternative = 0;
				solution[solutionIdx++] = hasBigger + 48;
				break;
			}

			// still have digits to go on
			else {
				// deal with the bigger case
				altSolutionKeyDigit = hasBigger;
				altSolutionIdx = solutionIdx;
				for (int dig = 1; dig <= 9; ++dig)
					alternativeSolutionDigitsNum[dig] = digitsNum[dig] - (dig == hasBigger);

				// deal with the equals case
				--digitsNum[hasEquals];
				solution[solutionIdx++] = hasEquals + 48;
			}
		}
	}

	// use alternative solution as answer
	if (useAlternative) {
		if (altSolutionKeyDigit == 0)
			puts("QQ");
		else {
			for (int k = 0; k < altSolutionIdx; ++k)
				putchar(solution[k]);
			putchar(altSolutionKeyDigit + 48);

			for (int dig = 1; dig <= 9; ++dig)
				while (alternativeSolutionDigitsNum[dig])
					putchar(dig + 48), --alternativeSolutionDigitsNum[dig];
			puts("");
		}
	}

	// use solution as answer
	else {
		solution[solutionIdx] = '\0';
		puts(solution);
	}

	return 0;
}
