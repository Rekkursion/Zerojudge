#pragma warning (disable:4996)

#include <stdio.h>
#include <stdlib.h>
#define MAX_N 1001
#define MAX_E (MAX_N * MAX_N)

typedef struct enode {
	int src;
	int dst;
	int weight;
}EdgeNode;
EdgeNode edgeList[MAX_E];

int disjointSet[MAX_N];

int cmp(const void*, const void*);
inline int findSet(const int* const);
inline void unionSet(const int* const, const int* const);
int main() {
	int n, eNum;
	while (~scanf("%d", &n)) {
		for (int k = 0; k <= n; ++k)
			disjointSet[k] = k;

		eNum = ((n - 1) * n) >> 1;
		for (int k = 0; k < eNum; ++k)
			scanf("%d %d %d", &edgeList[k].src, &edgeList[k].dst, &edgeList[k].weight);
		qsort(edgeList, eNum, sizeof(EdgeNode), cmp);

		int totalW = 0;
		for (int k = 0; k < eNum; ++k) {
			if (findSet(&edgeList[k].src) != findSet(&edgeList[k].dst)) {
				unionSet(&edgeList[k].src, &edgeList[k].dst);
				totalW += edgeList[k].weight;
			}
		}

		printf("%d\n", totalW);
	}

	return 0;
}

int cmp(const void* a, const void* b) {
	EdgeNode* ea = (EdgeNode*)a;
	EdgeNode* eb = (EdgeNode*)b;
	return ea->weight - eb->weight;
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
