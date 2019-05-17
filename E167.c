#pragma warning (disable:4996)

#include <stdio.h>
#define MAXN 100
#define abs(x) ((x) < 0 ? (-(x)) : (x))
int map[MAXN][MAXN];
int visited[MAXN][MAXN];

int searchPeople(int*, int*, const int, const int);
int main() {
	int n, m, x, y;
	while (~scanf("%d %d", &n, &m) && (n || m)) {
		for (int r = 0; r < n; ++r) {
			for (int c = 0; c < m; ++c) {
				visited[r][c] = 0;
				scanf("%d", &map[r][c]);
			}
		}
		scanf("%d %d", &y, &x);

		if (map[y][x] != 1)
			searchPeople(&y, &x, n, m);
		visited[y][x] = 1;

		while (searchPeople(&y, &x, n, m))
			visited[y][x] = 1;

		printf("%d %d\n", y, x);
	}

	return 0;
}

int searchPeople(int* yPtr, int* xPtr, const int N, const int M) {
	// 8-rounded
	for (int k = -1; k <= 1; ++k) {
		for (int j = -1; j <= 1; ++j) {
			if ((*yPtr) + k < 0 || (*yPtr) + k >= N || (*xPtr) + j < 0 || (*xPtr) + j >= M)
				continue;
			if (k == 0 && j == 0)
				continue;
			if (map[(*yPtr) + k][(*xPtr) + j] && !visited[(*yPtr) + k][(*xPtr) + j]) {
				(*yPtr) = (*yPtr) + k;
				(*xPtr) = (*xPtr) + j;
				return 1;
			}
		}
	}

	// 16-rounded
	for (int k = -2; k <= 2; ++k) {
		for (int j = -2; j <= 2; ++j) {
			if ((*yPtr) + k < 0 || (*yPtr) + k >= N || (*xPtr) + j < 0 || (*xPtr) + j >= M)
				continue;
			if (abs(k) < 2 && abs(j) < 2)
				continue;
			if (map[(*yPtr) + k][(*xPtr) + j] && !visited[(*yPtr) + k][(*xPtr) + j]) {
				(*yPtr) = (*yPtr) + k;
				(*xPtr) = (*xPtr) + j;
				return 1;
			}
		}
	}

	return 0;
}
