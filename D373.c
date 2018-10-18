#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#define MAXN 1000
#define MAXL 1001
#define NONE 90
#define SOURCE 91
#define DESTINATION 92
#define BLOCK 93
//#define QQ

int col, row;
int map[MAXN + 1][MAXN + 1];
bool inQue[MAXN + 1][MAXN + 1];

typedef struct point {
	int y, x;
}Point;

typedef struct qnode {
	Point pt;
	int step;
	struct qnode* next;
}Queue;
Queue* qhead = NULL;
Queue* qtail = NULL;

void getInput();
void setMap(int, Point, Point);
int bfs();
void queueInsert(int, int, int);
int main () {
	int res;
	
	getInput();
	res = bfs();
	
	if(res == -1)
		puts("no path");
	else
		printf("%d\n", res);
		
	#ifdef QQ
	system("PAUSE");
	#endif
	
	return 0;
}

void getInput() {
	Point pt1, pt2;
	char inp[MAXL];
	int k, j, len, num, cnt;
	
	scanf("%d %d", &col, &row);
	pt1.x = 0, pt1.y = 0;
	pt2.x = col - 1, pt2.y = row - 1;
	setMap(NONE, pt1, pt2);
	
	for(k = 0; k < row; k++) {
		for(j = 0; j < col; j++)
			inQue[k][j] = false;
	}
	
	scanf("%*s %d %d %d %d", &pt1.x, &pt1.y, &pt2.x, &pt2.y);
	setMap(SOURCE, pt1, pt2);
	
	scanf("%*s %d %d %d %d", &pt1.x, &pt1.y, &pt2.x, &pt2.y);
	setMap(DESTINATION, pt1, pt2);
	
	getchar();
	gets(inp);
	
	while(gets(inp)) {
		if(inp[0] == '.')
			break;
		
		strcat(inp, " ");
		len = strlen(inp);
		
		for(k = 0, num = cnt = 0; k < len; k++) {
			if(inp[k] == ' ') {
				switch(cnt) {
					case 0: pt1.x = num; break;
					case 1: pt1.y = num; break;
					case 2: pt2.x = num; break;
					case 3: pt2.y = num; break;
				}
				
				cnt++;
				num = 0;
			}
			
			else
				num = (num * 10) + (inp[k] - 48);
		}
		
		setMap(BLOCK, pt1, pt2);
	}
	
	#ifdef QQ
	for(k = 0; k < row; k++) {
		for(j = 0; j < col; j++)
			printf("%d ", map[k][j]);
		puts("");
	}
	#endif
	
	return;
}

void setMap(int type, Point pt1, Point pt2) {
	int x1 = (pt1.x < pt2.x) ? pt1.x : pt2.x;
	int x2 = (pt1.x < pt2.x) ? pt2.x : pt1.x;
	int y1 = (pt1.y < pt2.y) ? pt1.y : pt2.y;
	int y2 = (pt1.y < pt2.y) ? pt2.y : pt1.y;
	int k, j;
	
	for(k = y1; k <= y2; k++) {
		for(j = x1; j <= x2; j++)
			map[k][j] = type;
	}
	
	if(type == SOURCE) {
		for(k = y1; k <= y2; k++) {
			for(j = x1; j <= x2; j++) {
				
				if(k + 1 < row && map[k + 1][j] != SOURCE && inQue[k + 1][j] == false)
					queueInsert(k + 1, j, 0);
				if(j - 1 >= 0 && map[k][j - 1] != SOURCE && inQue[k][j - 1] == false)
					queueInsert(k, j - 1, 0);
				if(k - 1 >= 0 && map[k - 1][j] != SOURCE && inQue[k - 1][j] == false)
					queueInsert(k - 1, j, 0);
				if(j + 1 < col && map[k][j + 1] != SOURCE && inQue[k][j + 1] == false)
					queueInsert(k, j + 1, 0);
			}
		}
	}
	
	return;
}

int bfs() {
	Queue* p = qhead;
	Queue* qt = NULL;
	int k, j;
	
	while(p) {
		k = p->pt.y;
		j = p->pt.x;
		
		if(map[k][j] == DESTINATION)
			return p->step + 1;
		
		if(k + 1 < row && (map[k + 1][j] == NONE || map[k + 1][j] == DESTINATION) && inQue[k + 1][j] == false)
			queueInsert(k + 1, j, p->step + 1);
		if(j - 1 >= 0 && (map[k][j - 1] == NONE || map[k][j - 1] == DESTINATION) && inQue[k][j - 1] == false)
			queueInsert(k, j - 1, p->step + 1);
		if(k - 1 >= 0 && (map[k - 1][j] == NONE || map[k - 1][j] == DESTINATION) && inQue[k - 1][j] == false)
			queueInsert(k - 1, j, p->step + 1);
		if(j + 1 < col && (map[k][j + 1] == NONE || map[k][j + 1] == DESTINATION) && inQue[k][j + 1] == false)
			queueInsert(k, j + 1, p->step + 1);
		
		qt = p;
		p = p->next;
		free(qt);
	}
	
	return -1;
}

void queueInsert(int y, int x, int newStep) {
	Queue* newNode = (Queue*)malloc(sizeof(Queue));
	newNode->step = newStep;
	newNode->pt.y = y, newNode->pt.x = x;
	newNode->next = NULL;
	
	if(qhead == NULL) {
		qhead = newNode;
		qtail = newNode;
	}
	
	else {
		qtail->next = newNode;
		qtail = newNode;
	}
	
	inQue[y][x] = true;	
	return;
}
