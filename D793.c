#include <stdio.h>
#define MAXN 1000
#define INF 100000001
int n, m;
const int begy = 0;
const int begx = 0;
int endy, endx;

typedef struct gnode {
	int F;
	int number;
}Graph;
Graph map[MAXN][MAXN];

typedef struct hnode {
	int F;
	int y, x;
}Heap;
Heap heap[MAXN * MAXN];
int heapLen;

void initialize();
void heapInsert(int, int);
void heapDelete();
int dijkstra();
void judgeCost(int, int, int, int);
int main () {
	int T;
	scanf("%d", &T);
	
	int k, j, resStep;
	while(T--) {
		scanf("%d %d", &n, &m);
		initialize();
		
		for(k = 0; k < n; k++) {
			for(j = 0; j < m; j++) {
				scanf("%d", &map[k][j].number);
			}
		}
		
		map[begy][begx].F = map[begy][begx].number;
		heapInsert(begy, begx);
		
		resStep = dijkstra();
		printf("%d\n", resStep);
	}
	
	return 0;
}

void initialize() {
	int k, j;
	
	endy = n - 1, endx = m - 1;
	heapLen = 0;
	
	for(k = 0; k < n; k++) {
		for(j = 0; j < m; j++) {
			map[k][j].F = INF;
		}
	}
	
	return;
}

void heapInsert(int _y, int _x) {
	heap[heapLen].y = _y; heap[heapLen].x = _x;
	heap[heapLen].F = map[_y][_x].F;
	heapLen++;
	
	#define D
	#ifdef DD
	int k, j;
	for(k = 0; k < heapLen; k++)
		printf("%d ", heap[k].F);
	puts("");
	#endif
	
	int now = heapLen - 1;
	int father = (now - 1) >> 1;
	Heap temp;
	
	while(now > 0) {
		if(heap[father].F <= heap[now].F)
			break;
		
		temp.y = heap[now].y, temp.x = heap[now].x, temp.F = heap[now].F;
		heap[now].y = heap[father].y, heap[now].x = heap[father].x, heap[now].F = heap[father].F;
		heap[father].y = temp.y, heap[father].x = temp.x, heap[father].F = temp.F;
		
		now = father;
		father = (now - 1) >> 1;
	}
	
	#ifdef DD
	for(k = 0; k < heapLen; k++)
		printf("%d ", heap[k].F);
	puts("");
	system("PAUSE");
	#endif
	
	return;
}

void heapDelete() {
	
	#define P
	#ifdef PP
	int k, j;
	for(k = 0; k < heapLen; k++)
		printf("%d ", heap[k].F);
	puts("");
	#endif
	
	int last = heapLen - 1;
	heap[0].y = heap[last].y, heap[0].x = heap[last].x, heap[0].F = heap[last].F;
	heapLen--;
	
	int now = 0;
	int leftIdx = (now << 1) + 1;
	int rightIdx = (now << 1) + 2;
	int smallerIdx;
	Heap temp;
	
	while(now < last) {
		if(leftIdx >= last && rightIdx >= last)
			break;
		else if(leftIdx >= last)
			smallerIdx = rightIdx;
		else if(rightIdx >= last)
			smallerIdx = leftIdx;
		else
			smallerIdx = (heap[leftIdx].F < heap[rightIdx].F) ? leftIdx : rightIdx;
		
		if(heap[smallerIdx].F >= heap[now].F)
			break;
		
		temp.y = heap[now].y, temp.x = heap[now].x, temp.F = heap[now].F;
		heap[now].y = heap[smallerIdx].y, heap[now].x = heap[smallerIdx].x, heap[now].F = heap[smallerIdx].F;
		heap[smallerIdx].y = temp.y, heap[smallerIdx].x = temp.x, heap[smallerIdx].F = temp.F;
		
		now = smallerIdx;
		leftIdx = (now << 1) + 1;
		rightIdx = (now << 1) + 2;
	}
	
	#ifdef PP
	for(k = 0; k < heapLen; k++)
		printf("%d ", heap[k].F);
	puts("");
	system("PAUSE");
	#endif
	
	return;
}

int dijkstra() {
	int nowy = begy, nowx = begx;
	
	while(1) {
		
		#define Q
		#ifdef QQ
		{
			int k, j;
			for(k = 0; k < n; k++) {
				for(j = 0; j < m; j++) {
					if(map[k][j].F == INF)
						printf("XX ");
					else
						printf("%02d ", map[k][j].F);
				}
				puts("");
			}
			for(k = 0; k < heapLen; k++)
				printf("%d ", heap[k].F);
			puts("\n");
			system("PAUSE");
		}
		#endif
		
		judgeCost(nowy, nowx, nowy - 1, nowx);
		judgeCost(nowy, nowx, nowy, nowx + 1);
		judgeCost(nowy, nowx, nowy + 1, nowx);
		judgeCost(nowy, nowx, nowy, nowx - 1);
		
		if(nowy == endy && nowx == endx)
			break;
		
		if(heapLen <= 0)
			break;
		
		nowy = heap[0].y, nowx = heap[0].x;
		heapDelete();
	}
	
	return map[endy][endx].F;
}

void judgeCost(int nowy, int nowx, int ny, int nx) {
	if(ny < 0 || ny >= n || nx < 0 || nx >= m)
		return;
	
	if(map[nowy][nowx].F + map[ny][nx].number < map[ny][nx].F) {
		map[ny][nx].F = map[nowy][nowx].F + map[ny][nx].number;
		
		#define X
		#ifdef XX
		printf("(%02d, %02d): %02d\n", ny, nx, map[ny][nx].F);
		#endif
		
		heapInsert(ny, nx);
	}
	
	return;
}
