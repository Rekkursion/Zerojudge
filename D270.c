#include <stdio.h>
#include <stdbool.h>
#define MAXN 1024
#define SIDE 3
bool used[MAXN];
char map[SIDE + 1][SIDE + 1], buf[SIDE + 1][SIDE + 1];

int main () {
	int t;
	scanf("%d", &t);
	
	int k, j, num, cif, ans;
	while(t--) {
		scanf("%s %s %s", map[0], map[1], map[2]);
		
		for(k = 0; k < MAXN; k++)
			used[k] = false;
		used[0] = true;
		
		ans = -1;
		while(1) {
			
			//#define QQ
			#ifdef QQ
			puts("------------");
			for(k = 0; k < SIDE; k++) {
				printf("|");
				for(j = 0; j < SIDE; j++)
					printf("%c", map[k][j]);
				puts("|");
			}
			puts("------------");
			#endif
			
			num = 0; cif = 1;
			for(k = 0; k < SIDE; k++) {
				for(j = 0; j < SIDE; j++) {
					num += cif * (map[k][j] - 48);
					cif <<= 1;
				}
			}
			
			if(used[num])
				break;
			else {
				used[num] = true;
				ans++;
			}
			
			for(k = 0; k < SIDE; k++) {
				for(j = 0; j < SIDE; j++) {
					num = 0;
					
					if(k > 0)
						num += map[k - 1][j] - 48;
					if(j > 0)
						num += map[k][j - 1] - 48;
					if(k < SIDE - 1)
						num += map[k + 1][j] - 48;
					if(j < SIDE - 1)
						num += map[k][j + 1] - 48;
					
					buf[k][j] = (num & 1) + 48;
				}
			}
			
			for(k = 0; k < SIDE; k++) {
				for(j = 0; j < SIDE; j++)
					map[k][j] = buf[k][j];
			}
		}
		
		printf("%d\n", ans);
	}
	
	return 0;
}
