#pragma warning (disable:4996)

#include <stdio.h>
#define MAXN 10000

int minHeap[MAXN * 3];
int minHeapSize;

inline void heapInsert(int);
inline void heapify();
inline int heapPop();
inline int heapTop();
inline int isHeapEmpty();
int main() {
	int n, k, inp;
	while (~scanf("%d %d", &n, &k)) {

		minHeapSize = 1;
		for (int i = 0; i < n; ++i) {
			scanf("%d", &inp);
			heapInsert(inp);
		}

		// make the most negative into positive
		while (!isHeapEmpty() && heapTop() < 0 && k > 0) {
			--k;
			heapInsert(-(heapPop()));
		}

		// still need to change the cards
		if ((k & 1) && heapTop() > 0)
			heapInsert(-(heapPop()));

		// sum up all the numbers of cards
		int total = 0;
		while (!isHeapEmpty())
			total += heapPop();

		printf("%d\n", total);
	}

	return 0;
}

void heapInsert(int pData) {
	minHeap[minHeapSize++] = pData;
	heapify();

	return;
}

void heapify() {
	if (minHeapSize <= 1)
		return;

	int lastValue = minHeap[minHeapSize - 1];
	int nodeIdx = minHeapSize - 1;

	while (nodeIdx > 1 && lastValue < minHeap[nodeIdx >> 1])
		minHeap[nodeIdx] = minHeap[nodeIdx >> 1],
		nodeIdx >>= 1;
	minHeap[nodeIdx] = lastValue;

	return;
}

int heapPop() {
	int ret = minHeap[1];
	int lastValue = minHeap[minHeapSize - 1];
	int nodeIdx = 1;
	int childIdx;

	--minHeapSize;
	while (nodeIdx <= minHeapSize) {
		childIdx = (nodeIdx << 1);
		if (childIdx > minHeapSize)
			break;

		if (childIdx < minHeapSize && minHeap[childIdx] > minHeap[childIdx + 1])
			++childIdx;

		if (minHeap[childIdx] >= lastValue)
			break;

		minHeap[nodeIdx] = minHeap[childIdx];
		nodeIdx = childIdx;
	}
	minHeap[nodeIdx] = lastValue;

	return ret;
}

int heapTop() {
	return minHeap[1];
}

int isHeapEmpty() {
	return minHeapSize == 1;
}
