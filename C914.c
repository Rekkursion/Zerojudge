#include <stdio.h>
#define MAXN 31
typedef unsigned long long ull;
ull tail_v[MAXN], tail_h[MAXN], tail_dots[MAXN], tail_up[MAXN], tail_down[MAXN];
ull total[MAXN];

int main () {
	tail_v[1] = tail_dots[1] = 1;
	tail_h[1] = tail_up[1] = tail_down[1] = 0;
	total[1] = 2;
	
	int k, n;
	for(k = 2; k < MAXN; k++) {
		tail_v[k] = tail_dots[k] = total[k - 1];
		tail_h[k] = tail_dots[k - 1];
		tail_up[k] = tail_down[k - 1] + tail_dots[k - 1];
		tail_down[k] = tail_up[k - 1] + tail_dots[k - 1];
		
		total[k] = tail_v[k] + tail_h[k] + tail_up[k] + tail_down[k] + tail_dots[k];
	}
	
	scanf("%d", &k);
	
	while(k--) {
		scanf("%d", &n);
		printf("%llu\n", total[n]);
	}
	
	return 0;
}
