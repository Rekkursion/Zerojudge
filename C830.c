#pragma warning (disable:4996)

#include <stdio.h>
#include <string.h>
#define MAXL 22
char a[MAXL], b[MAXL];
char a_int[MAXL], b_int[MAXL], a_deci[MAXL], b_deci[MAXL];
char c_int[MAXL], c_deci[MAXL];

inline int indexOf(char*, int, char);
inline void subString(char*, int, int, char*);
inline int decimalAddition(char*, char*, char*);
inline void integerAddition(char*, char*, int, char*);
int main() {
	gets(a); gets(b);

	int lenA = strlen(a);
	int lenB = strlen(b);
	int dotIdxA = indexOf(a, lenA, '.');
	int dotIdxB = indexOf(b, lenB, '.');
	int hasCarryFromDecimal = 0;

	// need to do decimal addition
	if (dotIdxA >= 0 || dotIdxB >= 0) {
		if (dotIdxA < 0)
			strcpy(a_deci, "0");
		else
			subString(a, dotIdxA + 1, lenA - dotIdxA - 1, a_deci);

		if (dotIdxB < 0)
			strcpy(b_deci, "0");
		else
			subString(b, dotIdxB + 1, lenB - dotIdxB - 1, b_deci);

		hasCarryFromDecimal = decimalAddition(a_deci, b_deci, c_deci);
	}
	// NO need to do
	else
		strcpy(c_deci, "0");

	// integer addition
	if (dotIdxA >= 0)
		subString(a, 0, dotIdxA, a_int);
	else
		strcpy(a_int, a);

	if (dotIdxB >= 0)
		subString(b, 0, dotIdxB, b_int);
	else
		strcpy(b_int, b);

	integerAddition(a_int, b_int, hasCarryFromDecimal, c_int);

	// print out
	printf("%s", c_int);
	if (!(c_deci[0] == '0' && c_deci[1] == '\0'))
		putchar('.'), puts(c_deci);
	putchar('\n');

	return 0;
}

int indexOf(char* str, int len, char ch) {
	for (int k = 0; k < len; ++k) {
		if (str[k] == ch)
			return k;
	}
	return -1;
}

void subString(char* str, int startIdx, int len, char* ret) {
	for (int k = startIdx, j = 0; j < len; ++k, ++j)
		ret[j] = str[k];
	ret[len] = '\0';
	return;
}

int decimalAddition(char* dec1, char* dec2, char* ret) {
	int dec1_len = strlen(dec1);
	int dec2_len = strlen(dec2);
	int carry = 0;

	if (dec1_len < dec2_len) {
		for (int k = dec1_len; k < dec2_len; ++k)
			dec1[k] = '0';
		dec1[dec2_len] = '\0';
		dec1_len = dec2_len;
	}
	if (dec2_len < dec1_len) {
		for (int j = dec2_len; j < dec1_len; ++j)
			dec2[j] = '0';
		dec2[dec1_len] = '\0';
		dec2_len = dec1_len;
	}

	for (int i = dec1_len - 1; i >= 0; --i) {
		int sum = (dec1[i] - 48) + (dec2[i] - 48) + carry;

		if (sum >= 7) {
			carry = 1;
			sum -= 7;
		}
		else
			carry = 0;

		ret[i] = sum + 48;
	}
	ret[dec1_len] = '\0';

	for (int i = dec1_len - 1; i >= 0; --i) {
		if (ret[i] == '0')
			ret[i] = '\0';
		else
			break;
	}
	if (ret[0] == '\0')
		ret[0] = '0';

	return carry;
}

void integerAddition(char* int1, char* int2, int hasCarryFromDecimal, char* ret) {
	int len1 = strlen(int1);
	int len2 = strlen(int2);
	int tmp[MAXL];
	int carry = 0;

	for (int k = 0; k < MAXL; ++k)
		tmp[k] = 0;

	int i = 0;
	for (int k = len1 - 1, j = len2 - 1; k >= 0 || j >= 0 || carry; --k, --j) {
		int v1 = k < 0 ? 0 : int1[k] - 48;
		int v2 = j < 0 ? 0 : int2[j] - 48;
		int sum = v1 + v2 + carry + (i == 0 && hasCarryFromDecimal);

		if (sum >= 7) {
			sum -= 7;
			carry = 1;
		}
		else
			carry = 0;

		tmp[i++] = sum;
	}

	int start = 0;
	carry = 0;
	for (int k = i; k >= 0; --k) {
		if (!start && tmp[k])
			start = 1;
		if (start)
			ret[carry++] = tmp[k] + 48;
	}
	if (carry == 0)
		ret[carry++] = '0';
	ret[carry] = '\0';

	return;
}
