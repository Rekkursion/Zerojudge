#include <stdio.h>
#include <string.h>
#define MAXL 30
#define MAXN 1000
#define MAXB 245
#define CMD_NUM 7
//#define QQ
const char* cmdList[] = {"(>OwO)>u~(/OwO)/nya~",
						 "(>OwO)>u~!(/OwO)/nya~!",
						 "(>OwO)>u~!!(/OwO)/nya~!!",
						 "(>OwO)>u~!!!(/OwO)/nya~!!!",
						 "CHAOS CHAOS!",
						 "I WANNA CHAOS!",
						 "Let\'s\\(OwO)/nya~"};

typedef struct node {
	int chaos;
	int cmd;
}nyaruko;
nyaruko nya[MAXN];
int nyaNum;

int chaosStk[MAXN];
int top;

int brain[MAXB];
int ptr;

int main () {
	char c, inp[MAXL];
	int len, k, chaosChaos;
	
	len = nyaNum = top = 0;
	while((c = getchar()) != EOF) {
		#ifdef QQ
		if(c == '_')
			break;
		#endif
		
		if(c == ' ' || c == '\n') {
			if(len == 0)
				continue;
			
			inp[len] = 0;
			
			for(k = 0; k < CMD_NUM; k++) {
				if(!strcmp(inp, cmdList[k]))
					break;
			}
			
			if(k >= CMD_NUM)
				inp[len++] = ' ';
			
			else {
				nya[nyaNum].cmd = k;
				nya[nyaNum].chaos = -1;
				
				if(!strcmp(inp, "CHAOS CHAOS!")) {
					chaosStk[top++] = nyaNum;
				}
				
				else if(!strcmp(inp, "I WANNA CHAOS!")) {
					top--;
					
					nya[chaosStk[top]].chaos = nyaNum;
					nya[nyaNum].chaos = chaosStk[top];
				}
				
				len = 0;
				nyaNum++;
			}
		}
		
		else
			inp[len++] = c;
	}
	
	#ifdef QQ
	for(k = 0; k < nyaNum; k++) {
		printf("[%d]: No(%d) = |%s| (chaos=%d)\n", k, nya[k].cmd, cmdList[nya[k].cmd], nya[k].chaos);
	}
	#endif
	
	ptr = 0;
	for(k = 0; k < MAXB; k++)
		brain[k] = 0;
	
	for(k = 0; k < nyaNum; k++) {
		
		switch(nya[k].cmd) {
			case 0: ptr++;		  break;
			case 1: brain[ptr]++; break;
			case 2: ptr--;		  break;
			case 3: brain[ptr]--; break;
			case 4:
				if(brain[ptr] == 0)
					k = nya[k].chaos;
				break;
			case 5:
				if(brain[ptr] != 0)
					k = nya[k].chaos;
				break;
			case 6: printf("%c", brain[ptr]); break;
		}
	}
	//puts("");
	
	return 0;
}
