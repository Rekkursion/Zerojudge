#include <stdio.h>
#define MAXN 10
#define MAXL 65
//#define DEBUG
int n;
int p[MAXN + 1], q[MAXN + 1];
int cost[MAXN + 1][MAXN + 1], cutIdx[MAXN + 1][MAXN + 1];
int resultIdx;
char result[MAXL + 1];

void printAnswer(int, int);
int main() {
	int kase = 0;
	
	while(~scanf("%d", &n) && n) {
		for(int k = 1; k <= n; ++k)
			scanf("%d %d", &p[k], &q[k]);
		
		for(int off = 0; off < n; ++off) {
			for(int k = n; k - off >= 1; --k) {
				if(off == 0)
					cost[k - off][k] = 0;
				else {
					int minCost = cost[k - off][k - off] + cost[k - off + 1][k] + (p[k - off] * q[k - off] * q[k]);
					int minCostIdx = k - off;
					for(int cut = k - 1; cut > k - off; --cut) {
						int tmpCost = cost[k - off][cut] + cost[cut + 1][k] + (p[k - off] * q[cut] * q[k]);
						if(tmpCost < minCost) {
							minCost = tmpCost;
							minCostIdx = cut;
						}
					}
					
					cost[k - off][k] = minCost;
					cutIdx[k - off][k] = minCostIdx;
				}
			}
		}
		
		#ifdef DEBUG
		for(int off = n - 1; off >= 0; --off) {
			for(int k = 1; k + off <= n; ++k) {
				printf("%d ", cost[k][k + off]);
			}
			puts("");
		}
		#endif
		
		printf("Case %d: ", ++kase);
		
		resultIdx = 0;
		printAnswer(1, n);
		result[resultIdx] = '\0';
		printf("%s\n", result);
	}
	
	return 0;
}


void printAnswer(int left, int right) {
	if(left == right) {
		result[resultIdx++] = 'A';
		if(left == 10)
			result[resultIdx++] = '1', result[resultIdx++] = '0';
		else
			result[resultIdx++] = left + 48;
		//printf("A%d", left);
		return;
	}
	
	if(left + 1 == right) {
		result[resultIdx++] = '(', result[resultIdx++] = 'A';
		result[resultIdx++] = left + 48;
		result[resultIdx++] = ' ', result[resultIdx++] = 'x', result[resultIdx++] = ' ';
		result[resultIdx++] = 'A';
		if(right == 10)
			result[resultIdx++] = '1', result[resultIdx++] = '0';
		else
			result[resultIdx++] = right + 48;
		result[resultIdx++] = ')';
		
		return;
	}
	
	result[resultIdx++] = '(';
	printAnswer(left, cutIdx[left][right]);
	result[resultIdx++] = ' ', result[resultIdx++] = 'x', result[resultIdx++] = ' ';
	printAnswer(cutIdx[left][right] + 1, right);
	result[resultIdx++] = ')';
	
	return;
}
