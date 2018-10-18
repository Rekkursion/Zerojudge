#include <stdio.h>
#include <string.h>
#define MAXL 1001
#define FRACTION_LENGTH 50
#define pause system("PAUSE")
//#define QQ
//#define QQQ
char inp[MAXL], ans[MAXL], tmpc[MAXL], res[MAXL];
char dividend[MAXL], divisor[MAXL], guessed[MAXL];
int tmpi[MAXL];

char* squareRoot(char*);
char* deletePreZero(char*);
char* multiple(char*, char*);
int compare(char*, char*);
char* add(char*, char*);
char* minuz(char*, char*);
int main () {
	
	while(~scanf("%s", inp)) {
		squareRoot(inp);
		printf("%s\n", ans);
	}
	
	return 0;
}

char* squareRoot(char* num) {
	int k, len = strlen(num), cursor, disorLen, dendLen, guess, ansLen;
	int inFractionPart, cnt;
	
	// ex: 125 -> 0125, 2389 -> 2389
	if(len & 1) {
		tmpc[0] = '0'; tmpc[1] = 0;
		strcat(tmpc, num);
		strcpy(num, tmpc);
	}
	
	divisor[0] = '0'; divisor[1] = 0;
	dividend[0] = '0'; dividend[1] = 0;
	cursor = 0;
	disorLen = dendLen = 1; ansLen = 0;
	inFractionPart = cnt = 0;
	
	while(1) {
		if(inFractionPart == 1) {
			cnt++;
			
			if(cnt >= FRACTION_LENGTH)
				break;
		}
		
		if(cursor >= len) {
			
			if(inFractionPart == 0) {
				ans[ansLen] = '.';
				ansLen++;
			}
			inFractionPart = 1;
			
			
			divisor[disorLen++] = '0';
			divisor[disorLen++] = '0';
			divisor[disorLen] = 0;
			
			deletePreZero(divisor);
			disorLen = strlen(divisor);
		}
		else {
			divisor[disorLen] = num[cursor];
			disorLen++; cursor++;
			divisor[disorLen] = num[cursor];
			disorLen++; cursor++;
			divisor[disorLen] = 0;
			
			deletePreZero(divisor);
			disorLen = strlen(divisor);
		}
		
		#ifdef QQ
		printf("divisor = |%s|\n==================\n", divisor);
		#endif
		
		for(guess = 9; guess >= 0; guess--) {
			dividend[dendLen++] = (char)(guess + 48);
			dividend[dendLen] = 0;
			deletePreZero(dividend);
			dendLen = strlen(dividend);
			
			tmpc[0] = (char)(guess + 48);
			tmpc[1] = 0;
			
			strcpy(guessed, multiple(dividend, tmpc));
			
			#ifdef QQ
			printf("dividend = |%s|, guessing = |%s|, multiple = |%s|\n", dividend, tmpc, guessed);
			pause;
			#endif
			
			if(compare(guessed, divisor) <= 0)
				break;
			
			dendLen--;
		}
		
		#ifdef QQ
		printf("guessed = |%s|\n", guessed);
		pause;
		#endif
		
		strcpy(dividend, add(dividend, tmpc)); dendLen = strlen(dividend);
		strcpy(divisor, minuz(divisor, guessed)); disorLen = strlen(divisor);
		
		#ifdef QQQ
		printf("%d", guess);
		#endif
		
		ans[ansLen] = (char)(guess + 48);
		ansLen++;
	}
	
	#ifdef QQQ
	puts("");
	#endif
	
	ans[ansLen] = 0;
	deletePreZero(ans);
	
	return ans;
}

char* deletePreZero(char* str) {
	if(str[0] != '0')
		return str;
	
	int k, i, len = strlen(str);
	
	for(k = 0; k < len; k++) {
		if(str[k] != '0')
			break;
	}
	if(k >= len) {
		str[0] = '0'; str[1] = 0;
		return str;
	}
	
	for(i = 0; k < len; i++, k++)
		str[i] = str[k];
	str[i] = 0;
	
	return str;
}

char* multiple(char* a, char* b) {
	
	if(a[0] == '0' || b[0] == '0') {
		res[0] = '0'; res[1] = 0;
		return res;
	}
	
	int k, j, len1 = strlen(a), len2 = strlen(b), i, h;
	
	for(k = 0; k < len1 + len2 + 12; k++)
		tmpi[k] = 0;
	
	for(k = len1 - 1, i = 0; k >= 0; i++, k--) {
		for(j = len2 - 1, h = i; j >= 0; h++, j--)
			tmpi[h] += (int)(a[k] - 48) * (int)(b[j] - 48);
	}
	
	for(k = 0; k < h; k++) {
		if(tmpi[k] >= 10) {
			tmpi[k + 1] += tmpi[k] / 10;
			tmpi[k] %= 10;
		}
	}
	
	for(k += 6; k >= 0; k--) {
		if(tmpi[k] != 0)
			break;
	}
	
	for(i = 0; k >= 0; i++, k--)
		res[i] = tmpi[k] + 48;
	res[i] = 0;
	deletePreZero(res);
	
	return res;
}

int compare(char* a, char* b) {
	a = deletePreZero(a);
	b = deletePreZero(b);
	
	int lenA = strlen(a), lenB = strlen(b);
	
	if(lenA < lenB)
		return (-1);
	
	if(lenA > lenB)
		return 1;
	
	int k;
	
	for(k = 0; k < lenA; k++) {
		if(a[k] < b[k])
			return (-1);
		
		if(a[k] > b[k])
			return 1;
	}
	
	// the same
	return 0;
}

char* add(char* a, char* b) {
	int k, j, i, len1 = strlen(a), len2 = strlen(b), ia, ib;
	
	for(k = 0; k < len1 + len2 + 15; k++)
		tmpi[k] = 0;
	
	i = 0;
	for(k = len1 - 1, j = len2 - 1; k >= 0 || j >= 0; k--, j--) {
		ia = (k < 0) ? 0 : (int)(a[k] - 48);
		ib = (j < 0) ? 0 : (int)(b[j] - 48);
		
		tmpi[i++] = ia + ib;
	}
	
	for(k = 0; k < i; k++) {
		if(tmpi[k] >= 10) {
			tmpi[k + 1]++;
			tmpi[k] -= 10;
		}
	}
	
	for(k += 5; k >= 0; k--) {
		if(tmpi[k] != 0)
			break;
	}
	
	for(i = 0; k >= 0; i++, k--)
		res[i] = (char)(tmpi[k] + 48);
	res[i] = 0;
	deletePreZero(res);
	
	return res;
}

char* minuz(char* a, char* b) {
	int k, j, i, len1 = strlen(a), len2 = strlen(b), ia, ib;
	
	for(k = 0; k < len1 + len2 + 15; k++)
		tmpi[k] = 0;
	
	i = 0;
	for(k = len1 - 1, j = len2 - 1; k >= 0 || j >= 0; k--, j--) {
		ia = (k < 0) ? 0 : (int)(a[k] - 48);
		ib = (j < 0) ? 0 : (int)(b[j] - 48);
		
		tmpi[i++] = ia - ib;
	}
	
	for(k = 0; k < i; k++) {
		if(tmpi[k] < 0) {
			tmpi[k + 1]--;
			tmpi[k] += 10;
		}
	}
	
	for(k += 5; k >= 0; k--) {
		if(tmpi[k] != 0)
			break;
	}
	
	for(i = 0; k >= 0; i++, k--)
		res[i] = (char)(tmpi[k] + 48);
	res[i] = 0;
	deletePreZero(res);
	
	return res;
}
