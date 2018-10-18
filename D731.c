#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define MAXN (((999999 + 1) << 1) + 1)
#define BLUE 1
#define RED 0
//#define QQ
int blue[MAXN], red[MAXN];
int blueNum, redNum;

int cmp(const void*, const void*);
int main () {
	int p;
	scanf("%d", &p);
	
	#ifdef QQ
	int cnt = 0;
	#endif
	int n, k, j, area, now, tall, nowMax, lastNow;
	while(p--) {
		
		#ifdef QQ
		cnt++;
		#endif
		
		scanf("%d", &n);
		
		if(n == 0) {
			puts("0");
			continue;
		}
		
		blueNum = redNum = 0;
		for(k = 0; k < n; k++) {
			scanf("%d", &area);
			
			if(area < 0)
				red[redNum++] = -area;
			else
				blue[blueNum++] = area;
		}
		
		if(redNum == 0 || blueNum == 0) {
			puts("1");
			continue;
		}
		
		qsort(red, redNum, sizeof(int), cmp);
		qsort(blue, blueNum, sizeof(int), cmp);
		
		#ifdef QQ
		if(cnt == 4) {
			
		//for(k = 0; k < redNum; k++)
			//printf("%d|", red[k]);
		for(k = 0; k < blueNum; k++)
			printf("%d|", blue[k]);
		puts("");
		}
		#endif
		
		now = (blue[0] < red[0]) ? RED : BLUE;
		nowMax = (blue[0] < red[0]) ? blue[0] : red[0];
		k = (blue[0] < red[0]) ? 1 : 0;
		j = (blue[0] < red[0]) ? 0 : 1;
		
		tall = 1;
		while(1) {
			lastNow = now;
			
			if(now == BLUE) {
				while(k < blueNum) {
					
					if(blue[k] > nowMax) {
						tall++;
						nowMax = blue[k];
						now = !now;
						
						break;
					}
					
					k++;
				}
			}
			
			else if(now == RED) {
				while(j < redNum) {
					
					if(red[j] > nowMax) {
						tall++;
						nowMax = red[j];
						now = !now;
						
						break;
					}
					
					j++;
				}
			}
			
			if(lastNow == now)
				break;
		}
		
		printf("%d\n", tall);
	}
	
	return 0;
}

int cmp(const void* a, const void* b) {
	return (*((int *)a)) - (*((int *)b));
}
