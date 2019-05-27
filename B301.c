#pragma warning (disable:4996)

#include <stdio.h>
#include <stdlib.h>
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) < (b) ? (b) : (a))
#define MAXN 10000

typedef struct enode {
	int u;
	int v;
}EdgeNode;
EdgeNode edges[MAXN + 1];

typedef struct lnode {
	int dst;
	struct lnode* next;
}ListNode;
ListNode* qhead;
ListNode* qtail;

typedef struct gnode {
	struct lnode* lhead;
	struct lnode* ltail;
}GraphNode;
GraphNode graph[MAXN + 1];

int isRepresentative[MAXN + 1];
int set[MAXN + 1];
int visited[MAXN + 1];

static inline int readNonNegativeInt(int* const);
inline void initialize(const int* const);
inline void insertEdge(const int* const, const int* const);
inline int findSet(const int* const);
inline void unionSet(const int* const, const int* const);
inline int hasPath(const int* const, const int* const, const int* const, const int* const);
int cmp(const void*, const void*);
int main() {
	int n, q, u, v, a, b;
	int splittedSet, uSet, vSet;

	readNonNegativeInt(&n);
	readNonNegativeInt(&q);
	initialize(&n);

	for (int k = 0; k < n; ++k) {
		readNonNegativeInt(&u);
		readNonNegativeInt(&v);
		edges[k].u = min(u, v);
		edges[k].v = max(u, v);
	}

	qsort(edges, n, sizeof(EdgeNode), cmp);
	for (int k = 0; k < n; ++k) {
		if (edges[k].u == 0)
			isRepresentative[edges[k].v] = 1;
		else
			unionSet(&edges[k].u, &edges[k].v);

		insertEdge(&edges[k].u, &edges[k].v);
		insertEdge(&edges[k].v, &edges[k].u);
	}

	while (q--) {
		readNonNegativeInt(&u);
		readNonNegativeInt(&v);
		readNonNegativeInt(&a);
		readNonNegativeInt(&b);

		splittedSet = a == 0 ? findSet(&b) : findSet(&a);
		uSet = findSet(&u);
		vSet = findSet(&v);

		if (a == 0 || b == 0) {
			if (uSet != splittedSet && vSet != splittedSet)
				puts("STOP");
			else if (uSet == splittedSet && vSet == splittedSet)
				puts("STOP");
			else
				puts("GO");
		} else {
			if (uSet != splittedSet && vSet != splittedSet)
				puts("STOP");
			else {
				int canReach_u = uSet == 0 ? 1 : hasPath(&uSet, &u, &a, &b);
				int canReach_v = vSet == 0 ? 1 : hasPath(&vSet, &v, &a, &b);
				puts((canReach_u ^ canReach_v) ? "GO" : "STOP");
			}
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

void initialize(const int* const n) {
	for (int k = 0; k <= *n; ++k)
		isRepresentative[k] = 0,
		visited[k] = 0,
		set[k] = k,
		graph[k].lhead = graph[k].ltail = NULL;

	return;
}

void insertEdge(const int* const u, const int* const v) {
	ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
	newNode->dst = *v;
	newNode->next = NULL;

	if (graph[*u].lhead == NULL)
		graph[*u].lhead = newNode,
		graph[*u].ltail = newNode;
	else
		graph[*u].ltail->next = newNode,
		graph[*u].ltail = graph[*u].ltail->next;

	return;
}

int findSet(const int* const v) {
	if (set[*v] == *v)
		return *v;

	set[*v] = findSet(&set[*v]);
	return set[*v];
}

void unionSet(const int* const u, const int* const v) {
	int u_dad = findSet(u);
	int v_dad = findSet(v);

	if (u_dad == v_dad)
		return;

	if (isRepresentative[u_dad])
		set[v_dad] = u_dad;
	else if (isRepresentative[v_dad])
		set[u_dad] = v_dad;
	else {
		if (u_dad < v_dad)
			set[v_dad] = u_dad;
		else
			set[u_dad] = v_dad;
	}

	return;
}

int hasPath(const int* const source, const int* const destination, const int* const a, const int* const b) {
	int maxVisited = *source; 
	int minVisited = *source;
	int canReach = -1;

	ListNode* queHead = (ListNode*)malloc(sizeof(ListNode));
	queHead->dst = *source;
	queHead->next = NULL;

	qhead = queHead;
	qtail = queHead;
	visited[0] = visited[*source] = 1;

	while (qhead != NULL) {
		if (qhead->dst == *destination) {
			canReach = 1;
			break;
		}

		ListNode* p = graph[qhead->dst].lhead;
		while (p != NULL) {
			if (!visited[p->dst] && !((qhead->dst == *a && p->dst == *b) || (qhead->dst == *b && p->dst == *a))) {
				ListNode* newNode = (ListNode*)malloc(sizeof(ListNode));
				newNode->dst = p->dst;
				newNode->next = NULL;

				qtail->next = newNode;
				qtail = qtail->next;

				visited[p->dst] = 1;
				maxVisited = max(maxVisited, p->dst);
				minVisited = min(minVisited, p->dst);
			}
			p = p->next;
		}

		ListNode* qt = qhead;
		qhead = qhead->next;
		free(qt);
	}

	for (int k = minVisited; k <= maxVisited; ++k)
		visited[k] = 0;

	return canReach;
}

int cmp(const void* a, const void* b) {
	EdgeNode* ea = (EdgeNode*)a;
	EdgeNode* eb = (EdgeNode*)b;

	if (ea->u != eb->u)
		return ea->u - eb->u;
	return ea->v - eb->v;
}
