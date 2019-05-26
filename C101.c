// 2018 01 12

#include <stdio.h>
#include <string.h>
#define MAXL 10001
#define MAXNODE 17001
#define NONE (-1)
char inp[MAXL];
int tree[MAXNODE];
int ans[MAXNODE];

int main () {
	int k, j, num, idx, notComplete, maxIdx;
	
	while(~scanf("%s", inp)) {
		notComplete = 0;
		maxIdx = 0;
		for(k = 0; k < MAXNODE; k++)
			tree[k] = NONE;
		
		while(1) {
			if(!strcmp("()", inp))
				break;
			
			num = 0;
			for(k = 0; inp[k]; k++) {
				if(inp[k] >= 48 && inp[k] <= 57)
					num = (num * 10) + (inp[k] - 48);
				if(inp[k] == ',')
					break;
			}
			
			idx = 1;
			for(k++; inp[k]; k++) {
				if(inp[k] == ')')
					break;
				
				if(inp[k] == 'L')
					idx = (idx << 1);
				if(inp[k] == 'R')
					idx = (idx << 1) + 1;
			}
			
			if(idx > maxIdx)
				maxIdx = idx;
			
			if(tree[idx] != NONE && !notComplete) {
				notComplete = 1;
			}
			else if(tree[idx] == NONE && !notComplete) {
				tree[idx] = num;
			}
			
			scanf("%s", inp);
		}
		
		if(notComplete) {
			printf("not complete\n");
			continue;
		}
		
		for(k = 1; k <= maxIdx; k++) {
			if(tree[k] != NONE) {
				j = k;
				
				while(j > 0) {
					j >>= 1;
					if(j == 0)
						break;
					
					if(tree[j] == NONE) {
						notComplete = 1;
						k = maxIdx + 1;
						break;
					}
				}
			}
		}
		
		if(notComplete) {
			printf("not complete\n");
			continue;
		}
		
		int ansIdx = 0;
		for(k = 1; k <= maxIdx; k++) {
			if(tree[k] != NONE)
				ans[ansIdx++] = tree[k];
		}
		for(int h = 0; h < ansIdx; ++h)
			printf("%d%s", ans[h], h == ansIdx - 1 ? "" : " ");
		printf("\n");
	}
	
	return 0;
}
