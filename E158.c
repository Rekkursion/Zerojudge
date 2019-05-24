#pragma warning (disable:4996)

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAX_NUMBER 50000
#define lowbit(x) ((x) & (-(x)))

typedef struct node {
	int startTime, finishTime;
	int chooseNum;
}Interval;

Interval* intervals;
int bit[MAX_NUMBER + 1];
bool hasBeenChosen[MAX_NUMBER + 1];

static inline void readNonNegativeInt(int* const);
int cmp(const void*, const void*);
int bitQuery(int);
void bitInsert(const int* const);
int main() {
	int n, totalSize;

	readNonNegativeInt(&n);
	intervals = (Interval*)malloc(sizeof(Interval) * n);

	for (int k = 0; k < n; ++k)
		readNonNegativeInt(&intervals[k].startTime),
		readNonNegativeInt(&intervals[k].finishTime),
		readNonNegativeInt(&intervals[k].chooseNum);

	qsort(intervals, n, sizeof(Interval), cmp);

	totalSize = 0;
	for (int k = 0; k < n; ++k) {
		int remainNum = intervals[k].chooseNum - (bitQuery(intervals[k].finishTime) - bitQuery(intervals[k].startTime - 1));

		if (remainNum > 0) {
			totalSize += remainNum;

			for (int i = intervals[k].finishTime; remainNum > 0; --i) {
				if (!hasBeenChosen[i]) {
					hasBeenChosen[i] = true;
					--remainNum;
					bitInsert(&i);
				}
			}
		}
	}

	printf("%d\n", totalSize);
	return 0;
}

static inline void readNonNegativeInt(int* const integer) {
	static char ch;
	while ((ch = getchar()) < 48 || ch > 57);

	if (ch < 48 || ch > 57)
		return;

	(*integer) = ch - 48;
	while ((ch = getchar()) >= 48 && ch <= 57)
		(*integer) = ((*integer) * 10) + (ch - 48);

	return;
}

int cmp(const void* a, const void* b) {
	Interval* interval_a = (Interval*)a;
	Interval* interval_b = (Interval*)b;

	if (interval_a->finishTime != interval_b->finishTime)
		return interval_a->finishTime - interval_b->finishTime;
	return interval_a->startTime - interval_b->startTime;
}

int bitQuery(int index) {
	int sum = 0;
	for (int k = index; k > 0; k -= lowbit(k))
		sum += bit[k];
	return sum;
}

void bitInsert(const int* const INDEX) {
	for (int k = *INDEX; k <= MAX_NUMBER; k += lowbit(k))
		++bit[k];
	return;
}
