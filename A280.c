#pragma warning (disable:4996)

#include <stdio.h>
#include <stdlib.h>
#define MAX_NODE_NUM 100

char answerSheet[2][12] = { "Impossib1e!", "Ok!" };

typedef struct lnode {
	int dst;
	struct lnode* next;
}ListNode;

typedef struct gnode {
	int visisted;
	ListNode* lhead;
	ListNode* ltail;
}GraphNode;
GraphNode gNodes[MAX_NODE_NUM + 1];

typedef ListNode QueueNode;
QueueNode* qhead = NULL;
QueueNode* qtail = NULL;

void initialize();
void insertEdge(int, int);
int bfs(int);
int main() {
	int n, k, u, v;

	while (~scanf("%d %d", &n, &k)) {
		initialize();
		for (int i = 0; i < k; ++i) {
			scanf("%d %d", &u, &v);
			insertEdge(u, v);
		}

		printf("%s\n", answerSheet[bfs(n)]);
	}

	return 0;
}

void initialize() {
	for (int k = 0; k <= MAX_NODE_NUM; ++k) {
		/*
		ListNode* p = gNodes[k].lhead;
		ListNode* q;

		while (p != NULL) {
			q = p;
			p = p->next;
			free(q);
		}
		*/

		gNodes[k].lhead = gNodes[k].ltail = NULL;
		gNodes[k].visisted = 0;
	}
	qhead = qtail = NULL;

	return;
}

void insertEdge(int u, int v) {
	ListNode* newListNode = (ListNode*)malloc(sizeof(ListNode));
	newListNode->dst = v;
	newListNode->next = NULL;

	if (gNodes[u].lhead == NULL) {
		gNodes[u].lhead = newListNode;
		gNodes[u].ltail = newListNode;
	}
	else {
		gNodes[u].ltail->next = newListNode;
		gNodes[u].ltail = newListNode;
	}

	return;
}

int bfs(int finalDst) {
	QueueNode* qHeadNode = (QueueNode*)malloc(sizeof(QueueNode));
	qHeadNode->dst = 0;
	qHeadNode->next = NULL;

	qhead = qHeadNode;
	qtail = qHeadNode;

	while (qhead != NULL) {
		if (qhead->dst == finalDst) {
			/*
			while (qhead != NULL) {
				QueueNode* qt = qhead;
				qhead = qhead->next;
				free(qt);
			}
			*/
			return 1;
		}

		ListNode* p = gNodes[qhead->dst].lhead;
		while (p != NULL) {
			if (!gNodes[p->dst].visisted) {
				gNodes[p->dst].visisted = 1;

				QueueNode* newQNode = (QueueNode*)malloc(sizeof(QueueNode));
				newQNode->dst = p->dst;
				newQNode->next = NULL;

				qtail->next = newQNode;
				qtail = newQNode;
			}
			p = p->next;
		}

		QueueNode* qt = qhead;
		qhead = qhead->next;
		free(qt);
	}

	return 0;
}
