#pragma warning (disable:4996)

#include <stdio.h>
#include <stdlib.h>
#define MAXM 100000

typedef struct node {
	int distance;
	int quantity;
}TrashNode;
TrashNode trashList[MAXM];

static inline int readNonNegativeInt(int* const);
int cmp(const void*, const void*);
int main() {
	int kase;
	readNonNegativeInt(&kase);

	int m;
	while (kase--) {
		readNonNegativeInt(&m), readNonNegativeInt(&m);
		for (int k = 0; k < m; ++k)
			readNonNegativeInt(&trashList[k].distance);
		for (int k = 0; k < m; ++k)
			readNonNegativeInt(&trashList[k].quantity);

		if (m == 0) {
			puts("0");
			continue;
		}

		qsort(trashList, m, sizeof(TrashNode), cmp);

		long long disSum = 0ll;
		for (int k = 0; k < m; ++k) {
			if (k > 0 && trashList[k - 1].quantity == 1) {
				disSum += (long long)trashList[k - 1].distance << 1;
				--trashList[k].quantity;
			}

			if (trashList[k].quantity >= 2) {
				disSum += (long long)trashList[k].distance * (((long long)trashList[k].quantity >> 1) << 1);
				trashList[k].quantity &= 1;
			}
		}

		if (trashList[m - 1].quantity == 1)
			disSum += (long long)trashList[m - 1].distance << 1;

		printf("%lld\n", disSum);
	}

	return 0;
}

static inline int readNonNegativeInt(int* const integer) {
	static char ch;
	while ((ch = getchar()) < 48 || ch > 57);

	(*integer) = ch - 48;
	while ((ch = getchar()) >= 48 && ch <= 57)
		(*integer) = ((*integer) * 10) + (ch - 48);

	return 1;
}

int cmp(const void* a, const void* b) {
	TrashNode* ta = (TrashNode*)a;
	TrashNode* tb = (TrashNode*)b;

	return tb->distance - ta->distance;
}
