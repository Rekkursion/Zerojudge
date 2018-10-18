#include <stdio.h>
#define MAXN 8
#define MAXM 8
int n, m, maxNum;
int zu[MAXN][MAXM];

void dfs(int, int, int);
int main () {
	scanf("%d %d", &n, &m);
	
	int k, j;
	for(k = 0; k < n; k++) {
		for(j = 0; j < m; j++)
			zu[k][j] = 1;
	}
	zu[0][0] = 0;
	
	maxNum = 0;
	dfs(0, 0, 0);
	
	printf("%d\n", maxNum);
	
	return 0;
}

void dfs(int curRow, int curCol, int curNum) {
	int k, foundZu;
	
	for(k = curRow, foundZu = 0; k >= 0; k--) {
		if(zu[k][curCol] == 1) {
			
			if (foundZu == 1) {
				zu[k][curCol] = 0;
				dfs(k, curCol, curNum + 1);
				zu[k][curCol] = 1;
			}
			foundZu++;
		}
	}
	
	for(k = curRow, foundZu = 0; k < n; k++) {
		if(zu[k][curCol] == 1) {
			
			if (foundZu == 1) {
				zu[k][curCol] = 0;
				dfs(k, curCol, curNum + 1);
				zu[k][curCol] = 1;
			}
			foundZu++;
		}
	}
	
	for(k = curCol, foundZu = 0; k >= 0; k--) {
		if(zu[curRow][k] == 1) {
			
			if (foundZu == 1) {
				zu[curRow][k] = 0;
				dfs(curRow, k, curNum + 1);
				zu[curRow][k] = 1;
			}
			foundZu++;
		}
	}
	
	for(k = curCol, foundZu = 0; k < m; k++) {
		if(zu[curRow][k] == 1) {
			
			if (foundZu == 1) {
				zu[curRow][k] = 0;
				dfs(curRow, k, curNum + 1);
				zu[curRow][k] = 1;
			}
			foundZu++;
		}
	}
	
	if(curNum > maxNum)
		maxNum = curNum;
		
	return;
}
