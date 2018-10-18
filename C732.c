#include <stdio.h>
#include <stdlib.h>
#define MAXN 10000
int appetite[MAXN];

int cmp(const void*, const void*);
int main () {
	int n, k, max;
	scanf("%d", &n);
	
	for(k = 0; k < n; k++)
		scanf("%d", &appetite[k]);
	qsort(appetite, n, sizeof(int), cmp);
	
	max = appetite[0] + appetite[n - 1];
	for(k = 1; k < (n >> 1); k++) {
		if(appetite[k] + appetite[n - k - 1] > max)
			max = appetite[k] + appetite[n - k - 1];
	}
	
	printf("%d\n", max);
	
	return 0;
}

int cmp(const void* a, const void* b) {
	return (*((int *)a)) - (*((int *)b));
}
