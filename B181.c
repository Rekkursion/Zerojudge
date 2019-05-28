#pragma warning (disable:4996)

#include <stdio.h>
#include <stdlib.h>
#define MAX_N 17
#define MAX_E 107

typedef struct enode {
	int src;
	int dst;
	int weight;
}EdgeNode;
EdgeNode edgeList[MAX_E];
EdgeNode mstList[MAX_E];

int disjointSet[MAX_N];

int cmp_byWeight(const void*, const void*);
int cmp_byNumberOrder(const void*, const void*);
inline int findSet(const int* const);
inline void unionSet(const int* const, const int* const);
int main() {
	int n, m;
	while (~scanf("%d %d", &n, &m)) {
		for (int k = 0; k <= n; ++k)
			disjointSet[k] = k;

		char srcStr[4], dstStr[4];
		int w, src, dst;
		for (int k = 0; k < m; ++k) {
			scanf("%s %s %d", srcStr, dstStr, &w);
			sscanf(srcStr, "%*c%d", &src);
			sscanf(dstStr, "%*c%d", &dst);

			edgeList[k].src = src;
			edgeList[k].dst = dst;
			edgeList[k].weight = w;
		}
		qsort(edgeList, m, sizeof(EdgeNode), cmp_byWeight);

		int totalWeight = 0;
		int mstNum = 0;
		for (int k = 0; k < m; ++k) {
			if (findSet(&edgeList[k].src) != findSet(&edgeList[k].dst)) {
				unionSet(&edgeList[k].src, &edgeList[k].dst);

				mstList[mstNum].src = edgeList[k].src;
				mstList[mstNum].dst = edgeList[k].dst;
				//mstList[mstNum].weight = edgeList[k].weight;
				++mstNum;
				totalWeight += edgeList[k].weight;
			}
		}
		qsort(mstList, mstNum, sizeof(EdgeNode), cmp_byNumberOrder);

		for (int k = 0; k < mstNum; ++k)
			printf("(W%d W%d)%s", mstList[k].src, mstList[k].dst, k == mstNum - 1 ? "" : " ");
		printf("\n%d\n", totalWeight);
	}

	return 0;
}

int cmp_byWeight(const void* a, const void* b) {
	EdgeNode* ea = (EdgeNode*)a;
	EdgeNode* eb = (EdgeNode*)b;
	return ea->weight - eb->weight;
}

int cmp_byNumberOrder(const void* a, const void* b) {
	EdgeNode* ea = (EdgeNode*)a;
	EdgeNode* eb = (EdgeNode*)b;

	if (ea->src != eb->src)
		return ea->src - eb->src;
	return ea->dst - eb->dst;
}

int findSet(const int* const v) {
	if (disjointSet[*v] == *v)
		return *v;

	disjointSet[*v] = findSet(&disjointSet[*v]);
	return disjointSet[*v];
}

void unionSet(const int* const u, const int* const v) {
	int u_dad = findSet(u);
	int v_dad = findSet(v);

	if (u_dad == v_dad)
		return;

	disjointSet[u_dad] = v_dad;
	return;
}
