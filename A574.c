#pragma warning (disable:4996)

// naive

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_N 200000
#define DIMENSION 10
#define MAX_L 50

typedef struct mrnode {
	int data[DIMENSION];
}MatrixRow;
MatrixRow matrix[MAX_N + 1];
MatrixRow L, U;

char inpStr[MAX_L], L_str[MAX_L], U_str[MAX_L];
int rowNum, total;

inline void getMatrixData();
inline void sortMatrixData();
int cmp(const void*, const void*);
int main() {
	getMatrixData();
	sortMatrixData();

	while (~scanf("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", &L.data[0], &L.data[1], &L.data[2], &L.data[3], &L.data[4], &L.data[5], &L.data[6], &L.data[7], &L.data[8], &L.data[9])) {
		scanf("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d", &U.data[0], &U.data[1], &U.data[2], &U.data[3], &U.data[4], &U.data[5], &U.data[6], &U.data[7], &U.data[8], &U.data[9]);
		scanf("%*d");

		if (rowNum == 0) {
			puts("0");
			continue;
		}

		total = 0;
		for (int r = 0; r < rowNum; ++r) {
			int c;
			for (c = 0; c < DIMENSION; ++c) {
				if (matrix[r].data[c] < L.data[c] || matrix[r].data[c] > U.data[c])
					break;
			}

			if (c == DIMENSION)
				++total;
		}

		printf("%d\n", total);
	}

	return 0;
}

void getMatrixData() {
	int rIdx = 0;
	while (~scanf("%d", &matrix[rIdx].data[0])) {
		if (matrix[rIdx].data[0] == -1)
			break;
		for (int c = 1; c < DIMENSION; ++c)
			scanf(",%d", &matrix[rIdx].data[c]);
		++rIdx;
	}
	rowNum = rIdx;

	return;
}

void sortMatrixData() {
	qsort(matrix, rowNum, sizeof(MatrixRow), cmp);
	return;
}

int cmp(const void* a, const void* b) {
	MatrixRow* mr_a = (MatrixRow*)a;
	MatrixRow* mr_b = (MatrixRow*)b;

	for (int k = 0; k < DIMENSION; ++k) {
		if (mr_a->data[k] != mr_b->data[k])
			return mr_a->data[k] - mr_b->data[k];
	}

	return 0;
}
