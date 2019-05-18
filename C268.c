#pragma warning (disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 45
#define MAXL 5000001
int side[MAXN];
char qiu[MAXL];

void getInput();
int cmp(const void*, const void*);
int main() {
	int kase;
	scanf("%d", &kase);

	while (kase--) {
		int n, k;
		scanf("%d", &n);

		if (n > MAXN) {
			getchar();
			//while (getchar() >= 32);
			do {
				fgets(qiu, MAXL, stdin);
			} while (qiu[strlen(qiu) - 1] >= 32);

			puts("YES");
		}
		else {
			getchar(); getInput();
			qsort(side, n, sizeof(int), cmp);

			for (k = 2; k < n; k++) {
				if (side[k - 2] + side[k - 1] > side[k]) {
					puts("YES");
					break;
				}
			}
			if (k >= n)
				puts("NO");
		}
	}

	return 0;
}

void getInput() {
	int idx = 0;
	while (1) {
		int num = 0;
		char c;

		while ((c = getchar()) > 32)
			num = (num * 10) + (c - 48);
		side[idx++] = num;

		if (c != ' ') break;
	}

	return;
}

int cmp(const void* a, const void* b) {
	return (*((int*)a)) - (*((int*)b));
}
