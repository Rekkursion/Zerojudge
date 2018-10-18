#include <stdio.h>
#define MAXN 2018
#define MAX_NUM 1000000000000000000
unsigned long long seq[MAXN];

int dp();
int main () {
	int seqNum = dp(), k, total;
	unsigned long long n, m;
	scanf("%llu %llu", &n, &m);
	
	total = 0;
	for(k = 0; k < seqNum; k++) {
		if(seq[k] >= n && seq[k] <= m)
			total++;
	}
	
	printf("%d\n", total);
	
	return 0;
}

int dp() {
	seq[0] = 1;
	seq[1] = 2;
	seq[2] = 3;
	
	int k = 3;
	
	do {
		seq[k] = seq[k - 1] + seq[k - 2] + seq[k - 3];
		k++;
	}
	while(seq[k - 1] < MAX_NUM);
	
	return (k - 1);
}
