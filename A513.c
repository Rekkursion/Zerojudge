#pragma warning (disable:4996)

#include <stdio.h>
#define MAXN 40004
#define LOG2_MAXN 16

int maxHeap[MAXN * LOG2_MAXN];
int maxHeapSize;

static inline int readNonNegativeInt(int* const);
inline void heapInsert(const int* const);
inline void heapify();
inline int heapPop();
inline int isHeapEmpty();
int main() {
	int T, kase;
	readNonNegativeInt(&T);

	int n, m, num, cmd;
	for (int kase = 1; kase <= T; ++kase) {
		printf("Case %d:\n", kase);
		readNonNegativeInt(&n), readNonNegativeInt(&m);

		// initialize the max heap tree
		maxHeapSize = 1;
		for (int k = 0; k < n; ++k)
			readNonNegativeInt(&num),
			heapInsert(&num);

		// get commands
		while (m--) {
			readNonNegativeInt(&cmd);

			// heap pop
			if (cmd == 2)
				if (isHeapEmpty())
					puts("It\'s empty!");
				else
					printf("Max: %d\n", heapPop());

			// heap insert
			else
				readNonNegativeInt(&num),
				heapInsert(&num);
		}

		// output the remain elements
		if (isHeapEmpty())
			puts("It\'s empty!");
		else {
			while (!isHeapEmpty())
				printf("%d ", heapPop());
			putchar('\n');
		}
	}

	return 0;
}

static inline int readNonNegativeInt(int* const integer) {
	static char ch;
	while ((ch = getchar()) < 48 || ch > 57);

	if (ch < 48 || ch > 57)
		return 0;

	(*integer) = ch - 48;
	while ((ch = getchar()) >= 48 && ch <= 57)
		(*integer) = ((*integer) * 10) + (ch - 48);

	return 1;
}

void heapInsert(const int* const pData) {
	maxHeap[maxHeapSize++] = *pData;
	heapify();

	return;
}

void heapify() {
	if (maxHeapSize <= 1)
		return;

	int lastValue = maxHeap[maxHeapSize - 1];
	int nodeIdx = maxHeapSize - 1;

	while (nodeIdx > 1 && lastValue > maxHeap[nodeIdx >> 1])
		maxHeap[nodeIdx] = maxHeap[nodeIdx >> 1],
		nodeIdx >>= 1;
	maxHeap[nodeIdx] = lastValue;

	return;
}

int heapPop() {
	int ret = maxHeap[1];
	int lastValue = maxHeap[maxHeapSize - 1];
	int nodeIdx = 1;
	int childIdx;

	--maxHeapSize;
	while (nodeIdx <= maxHeapSize) {
		childIdx = (nodeIdx << 1);
		if (childIdx > maxHeapSize)
			break;

		if (childIdx < maxHeapSize && maxHeap[childIdx] < maxHeap[childIdx + 1])
			++childIdx;

		if (maxHeap[childIdx] <= lastValue)
			break;

		maxHeap[nodeIdx] = maxHeap[childIdx];
		nodeIdx = childIdx;
	}
	maxHeap[nodeIdx] = lastValue;

	return ret;
}

int isHeapEmpty() {
	return maxHeapSize == 1;
}
