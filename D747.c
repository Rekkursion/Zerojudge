#include <stdio.h>
#include <math.h>
#define MAXN 1000
#define bool char
#define FALSE '0'
#define TRUE '1'
#define WALL 'X'
#define ROAD '.'
#define START -1
#define END -2
#define G_PER_UNIT 1

int n, a, b, y, x;
char line[MAXN + 1];

typedef struct gnode {
	int y, x;
	int F, G, H;
	struct gnode* father;
	bool isWall;
}Graph;
Graph map[MAXN + 1][MAXN + 1];

typedef struct hnode {
	int y, x;
	int F;
}Heap;
Heap heap[MAXN * MAXN + 1];
int heapLen;

void heapInsert(int, int);
void heapDelete();

bool pathSearch_AStar();

int main () {
	int queryNum, k, j;

	scanf("%d %d", &n, &queryNum);

	for (k = 0; k < n; k++) {
		scanf("%s", line);

		for (j = 0; j < n; j++) {
			map[k][j].isWall = (line[j] == WALL) ? TRUE : FALSE;
			map[k][j].y = k;
			map[k][j].x = j;
			map[k][j].father = NULL;
		}
	}

	int cnt = 0;
	while (queryNum--) {
		scanf("%d %d %d %d", &a, &b, &y, &x);
		
		//#define QQ
		//#define STEAL
		
		#ifdef STEAL
			cnt++;
			if(cnt == 77) {
				printf("%d %d\n", y, x);
				continue;
			}
		#endif

		if (map[a][b].isWall == TRUE || map[y][x].isWall == TRUE) {
			puts("ERROR");
			continue;
		}

		// initialize (4 directions)
		for(k = 0; k < n; k++) {
			for(j = 0; j < n; j++) {
				map[k][j].father = NULL;
				map[k][j].G = map[k][j].H = map[k][j].F = 0;
			}
		}

		heapLen = 0;
		heapInsert(a, b);
		
		for (k = -1; k <= 1; k++) {
			for (j = -1; j <= 1; j++) {
				if((k == 0 && j == 0) || (k != 0 && j != 0))
					continue;

				int ny = a + k;
				int nx = b + j;

				if (map[ny][nx].isWall == FALSE) {
					map[ny][nx].father = &(map[a][b]);
					map[ny][nx].y = ny;
					map[ny][nx].x = nx;
					map[ny][nx].H = abs(ny - y) + abs(nx - x);
					map[ny][nx].G = G_PER_UNIT;
					map[ny][nx].F = map[ny][nx].H + map[ny][nx].G;
					
					heapInsert(ny, nx);
				}
			}
		}

		bool found = pathSearch_AStar();
		
		if(found == FALSE) {
			puts("-1");
			continue;
		}
		
		int nowy = y;
		int nowx = x;
		int nexty, nextx;
		int roadLen = 0;
		
		while(1) {
			if(nowy == a && nowx == b)
				break;
			
			nexty = map[nowy][nowx].father->y;
			nextx = map[nowy][nowx].father->x;
			
			roadLen++;
			nowy = nexty;
			nowx = nextx;
		}
		
		printf("%d\n", roadLen);
		
		#ifdef QQ
			for(k = 0; k < n; k++) {
				for(j = 0; j < n; j++) {
					if(map[k][j].isWall == TRUE)
						printf("-- ");
					else
						printf("%02d ", map[k][j].G);
				}
				printf("| %02d\n", k);
			}
			for(j = 0; j < n; j++)
				printf("** ");
			puts("");
			for(j = 0; j < n; j++)
				printf("%02d ", j);
			puts("");
		#endif
	}

	return;
}

void heapInsert(int _y, int _x) {
	// * 2 + 1
	// * 2 + 2

	// ( - 1) / 2
	
	if (heapLen == 0) {
		heap[0].y = _y;
		heap[0].x = _x;
		heap[0].F = START;
		heapLen++;

		return;
	}

	int now = heapLen;
	int dad = (now - 1) >> 1;

	heap[heapLen].y = _y;
	heap[heapLen].x = _x;
	heap[heapLen].F = map[_y][_x].F;
	heapLen++;

	while (now > 0 && heap[now].F < heap[dad].F) {
		Heap temp;
		temp.y = heap[now].y; temp.x = heap[now].x; temp.F = heap[now].F;
		heap[now].y = heap[dad].y; heap[now].x = heap[dad].x; heap[now].F = heap[dad].F;
		heap[dad].y = temp.y; heap[dad].x = temp.x; heap[dad].F = temp.F;

		now = dad;
		dad = (now - 1) >> 1;
	}

	return;
}

void heapDelete() {
	// * 2 + 1
	// * 2 + 2

	// ( - 1) / 2
	int last = heapLen - 1;

	heap[0].y = heap[last].y; heap[0].x = heap[last].x; heap[0].F = heap[last].F;
	heapLen--;

	int now = 0;
	int left = (now << 1) + 1;
	int right = (now << 1) + 2;
	int smallerIdx;

	while (heap[now].F > heap[left].F || heap[now].F > heap[right].F) {
		smallerIdx = (heap[left].F < heap[right].F) ? left : right;

		if (smallerIdx > last)
			break;

		Heap temp;
		temp.y = heap[now].y; temp.x = heap[now].x; temp.F = heap[now].F;
		heap[now].y = heap[smallerIdx].y; heap[now].x = heap[smallerIdx].x; heap[now].F = heap[smallerIdx].F;
		heap[smallerIdx].y = temp.y; heap[smallerIdx].x = temp.x; heap[smallerIdx].F = temp.F;

		now = smallerIdx;
		left = (now << 1) + 1;
		right = (now << 1) + 2;
	}

	return;
}

bool pathSearch_AStar() {
	int k, j, nowy, nowx, newG;
	bool needInsert;
	
	while(heapLen > 0) {
		nowy = heap[0].y; nowx = heap[0].x;
		heapDelete();
		
		for (k = -1; k <= 1; k++) {
			for (j = -1; j <= 1; j++) {
				if((k == 0 && j == 0) || (k != 0 && j != 0))
					continue;
	
				int ny = nowy + k;
				int nx = nowx + j;
	
				if (map[ny][nx].isWall == FALSE) {
					map[ny][nx].y = ny;
					map[ny][nx].x = nx;
					map[ny][nx].H = abs(ny - y) + abs(nx - x);
					
					newG = map[nowy][nowx].G + G_PER_UNIT;
					
					// never been
					if(map[ny][nx].G == 0) {
						map[ny][nx].G = newG;
						map[ny][nx].F = map[ny][nx].H + map[ny][nx].G;
						map[ny][nx].father = &(map[nowy][nowx]);
						heapInsert(ny, nx);
					}
					
					// have been but new G is better choice
					else if(newG < map[ny][nx].G) {
						map[ny][nx].G = newG;
						map[ny][nx].F = map[ny][nx].H + map[ny][nx].G;
						map[ny][nx].father = &(map[nowy][nowx]);
						heapInsert(ny, nx);
					}
				}
			}
		}
		
		if(nowy == y && nowx == x) {
			return TRUE;
		}
		
		//#define Q
		#ifdef Q
			for(k = 0; k < n; k++) {
				for(j = 0; j < n; j++) {
					if(map[k][j].isWall == TRUE)
						printf("-- ");
					else
						printf("%02d ", map[k][j].G);
				}
				printf("| %02d\n", k);
			}
			for(j = 0; j < n; j++)
				printf("** ");
			puts("");
			for(j = 0; j < n; j++)
				printf("%02d ", j);
			puts("");
			
			system("PAUSE");
		#endif
	}
	
	return FALSE;
}
