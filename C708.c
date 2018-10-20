#include <stdio.h>
typedef unsigned long long ull;

int main () {
	ull n, m, longitudinal, lateral, slash;
	
	while(~scanf("%llu %llu", &n, &m) && (n || m)) {
		if(n > m) {
			ull tmp = n;
			n = m;
			m = tmp;
		}
		
		if(n == 0 || m == 0)
			puts("0");
		
		else {
			longitudinal = (m * n) * (n - 1);
			lateral = (n * m) * (m - 1);
			slash = ((((((n - 2) * (n - 1) * ((n << 1) - 3)) / 6) + (((n - 1) * (n - 2)) >> 1)) << 1) + (n * (m - n + 1) * (n - 1))) << 1;
			
			printf("%llu\n", longitudinal + lateral + slash);
		}
	}
	
	return 0;
}
