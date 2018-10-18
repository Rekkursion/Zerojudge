#include <stdio.h>
#include <string.h>
#define MAXL 33
//#define QQ
char p[MAXL], q[MAXL], a[MAXL], b[MAXL], g[MAXL];
char remain[MAXL], quot[MAXL], sub[MAXL];

void gcd();
void bigDivision(char*, char*);
int cmp(char*, char*);
void bigMinus(char*, char*);
int main () {
	int t;
	scanf("%d", &t);
	
	while(t--) {
		scanf("%s %*s %s", p, q);
		
		gcd();
		
		#ifdef QQ
		printf("gcd = %s\n", g);
		#endif
		
		bigDivision(p, g);
		strcpy(p, quot);
		bigDivision(q, g);
		strcpy(q, quot);
		
		printf("%s / %s\n", p, q);
	}
	
	return 0;
}

void gcd() {
	strcpy(a, p);
	strcpy(b, q);
	
	while(1) {
		bigDivision(a, b);
		
		if(!strcmp(remain, "0")) {
			strcpy(g, b);
			break;
		}
		
		strcpy(a, b);
		strcpy(b, remain);
	}
	
	return;
}

void bigDivision(char* x, char* y) {
	//#define Q
	#ifdef Q
	printf("%s / %s\n", x, y);
	#endif
	
	sub[0] = 0;
	
	int cur, subL, cnt;
	int lenX = strlen(x);
	int lenQ = 0;
	int k, i;
	
	cur = subL = 0;
	while(1) {
		sub[subL++] = x[cur++];
		sub[subL] = 0;
		
		for(k = 0; k < subL; k++) {
			if(sub[k] != '0')
				break;
		}
		if(k >= subL)
			strcpy(sub, "0");
		else {
			for(i = 0; k < subL; i++, k++)
				sub[i] = sub[k];
			sub[i] = 0;
		}
		
		cnt = 0;
		
		// if sub >= y
		while(cmp(sub, y) != -1) {
			cnt++;
			bigMinus(sub, y);
		}
		
		#ifdef Q
		printf("%d\n", cnt);
		#endif
		
		quot[lenQ++] = cnt + 48;
		
		if(cur >= lenX)
			break;
		
		subL = strlen(sub);
	}
	
	
	#ifdef Q
	system("PAUSE");
	#endif
	
	strcpy(remain, sub);
	
	
	for(k = 0; remain[k]; k++) {
		if(remain[k] != '0')
			break;
	}
	if(k >= strlen(remain))
		strcpy(remain, "0");
	else {
		for(i = 0; k < strlen(remain); k++, i++)
			remain[i] = remain[k];
		remain[i] = 0;
	}
	
	quot[lenQ] = 0;
	
	for(k = 0; k < lenQ; k++) {
		if(quot[k] != '0')
			break;
	}
	if(k >= lenQ) {
		strcpy(quot, "0");
		return;
	}
	
	for(i = 0; k < lenQ; i++, k++)
		quot[i] = quot[k];
	quot[i] = 0;
	
	return;
}

// sub v.s. y: if sub >= y, return 1 or 0
int cmp(char* x, char* y) {
	int lenx = strlen(x);
	int leny = strlen(y);
	
	if(lenx < leny)
		return -1;
	if(lenx > leny)
		return 1;
	
	int k;
	
	for(k = 0; k < lenx; k++) {
		if(x[k] < y[k])
			return -1;
		if(x[k] > y[k])
			return 1;
	}
	
	return 0;
}

// sub - y
void bigMinus(char* x, char* y) {
	int k, j, len1 = strlen(x), len2 = strlen(y), ix, iy, i;
	int tmpi[MAXL + MAXL + MAXL];
	
	for(k = 0; k <= len1 + len2 + 14; k++)
		tmpi[k] = 0;
	
	i = 0;
	for(k = len1 - 1, j = len2 - 1; k >= 0 || j >= 0; k--, j--) {
		ix = (k < 0) ? 0 : (x[k] - 48);
		iy = (j < 0) ? 0 : (y[j] - 48);
		
		tmpi[i++] += ix - iy;
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
	if(k < 0) {
		strcpy(x, "0");
		return;
	}
	
	for(i = 0; k >= 0; k--, i++)
		x[i] = tmpi[k] + 48;
	x[i] = 0;
	
	return;
}
