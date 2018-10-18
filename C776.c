#include <stdio.h>

int main () {
	int n, m, firstRow, restRow;
	scanf("%d %d", &n, &m);
	
	firstRow = 6 + ((m - 1) * 4);
	restRow = 5 + ((m - 1) * 3);
	
	printf("%d\n", firstRow + (restRow * (n - 1)));
	
	return 0;
}
