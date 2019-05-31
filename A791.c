#pragma warning (disable:4996)

#include <stdio.h>
#define MAX_PAGE_NUM 1024
#define MAX_CACHE_PAGE_NUM 16
#define INF 2147483647
int memoryList[MAX_PAGE_NUM];

inline int getLeastRecentlyUsedPageIdx();
int main() {
	int cacheNum = 0;
	int timeStamp = 1;
	int hit = 0;
	int pageIdx;

	while (~scanf("%d", &pageIdx)) {
		for (int k = 0; k < 20; ++k) {
			if (k)
				scanf("%d", &pageIdx);

			// cache hit
			if (memoryList[pageIdx]) {
				++hit;
				memoryList[pageIdx] = timeStamp;
			}

			// cache miss
			else {
				// still can use more pages as cache
				if (cacheNum < MAX_CACHE_PAGE_NUM) {
					++cacheNum;
					memoryList[pageIdx] = timeStamp;
				}

				// no more pages can be used, do LRU (least-recently-used)
				else {
					memoryList[getLeastRecentlyUsedPageIdx()] = 0;
					memoryList[pageIdx] = timeStamp;
				}
			}

			++timeStamp;
		}

		printf("cache hit rate: %.2lf%%\n", ((double)hit * 100.0) / (double)(timeStamp - 1));
	}

	return 0;
}

int getLeastRecentlyUsedPageIdx() {
	int minTimeStamp = INF;
	int minTimeStampPageIdx = -1;

	for (int k = 0; k < MAX_PAGE_NUM; ++k) {
		if (memoryList[k] > 0 && memoryList[k] < minTimeStamp) {
			minTimeStampPageIdx = k;
			minTimeStamp = memoryList[k];
		}
	}

	return minTimeStampPageIdx;
}
