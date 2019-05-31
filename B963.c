#pragma warning (disable:4996)

#include <stdio.h>
#include <string.h>
#define MAXL 2002
#define get_ten_base_number(ch) ((ch) >= 48 && (ch) <= 57 ? (ch) - 48 : ((ch) >= 65 && (ch) <= 90 ? (ch) - 55 : (ch) - 87))
#define get_certain_base_char(n) ((n) <= 9 ? (n) + 48 : (n) + 55)
char a[MAXL], b[MAXL], result[MAXL];

inline int convertToTenBaseNumber(char*, int);
inline void convertFromTenBaseNumber(int, int, char*);
int main() {
	int base_a, base_b, toBase;
	int tenBaseNumber_a, tenBaseNumber_b, tenBaseResult;

	while (~scanf("%d %s %d %s %d", &base_a, a, &base_b, b, &toBase)) {
		tenBaseNumber_a = convertToTenBaseNumber(a, base_a);
		tenBaseNumber_b = convertToTenBaseNumber(b, base_b);

		tenBaseResult = tenBaseNumber_a + tenBaseNumber_b;
		convertFromTenBaseNumber(tenBaseResult, toBase, result);

		puts(result);
	}

	return 0;
}

int convertToTenBaseNumber(char* numStr, int fromBase) {
	int numStrLen = strlen(numStr);
	int exp = 1, ret = 0;

	if (numStrLen == 0)
		return 0;

	for (int k = numStrLen - 1; k >= 0; --k) {
		ret += get_ten_base_number(numStr[k]) * exp;
		exp *= fromBase;
	}

	return ret;
}

void convertFromTenBaseNumber(int tenBaseNum, int toBase, char* ret) {
	int tmp[MAXL];

	for (int k = 0; k < MAXL; ++k)
		tmp[k] = 0;

	int i = 0;
	while (tenBaseNum > 0) {
		tmp[i++] = tenBaseNum % toBase;
		tenBaseNum /= toBase;
	}

	int start = 0, j = 0;
	for (int k = i; k >= 0; --k) {
		if (!start && tmp[k])
			start = 1;
		if (start)
			ret[j++] = get_certain_base_char(tmp[k]);
	}
	if (j == 0)
		ret[j++] = '0';
	ret[j] = '\0';

	return;
}
