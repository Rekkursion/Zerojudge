#pragma warning (disable:4996)

#include <stdio.h>
#include <stdlib.h>
#define MAXN 50

typedef struct lnode {
	int num;
	struct lnode* next;
}ListNode;
ListNode* head = NULL;
ListNode* tail = NULL;

int discardedCards[MAXN];

void buildList(int);
ListNode* newListNode(int);
int main() {
	int n, d;
	while (~scanf("%d", &n) && n) {
		buildList(n);

		d = 0;
		while (head != tail) {
			discardedCards[d++] = head->num;

			ListNode* t = head;
			head = head->next;
			free(t);

			t = newListNode(head->num);
			tail->next = t;
			tail = tail->next;

			t = head;
			head = head->next;
			free(t);
		}

		printf("Discarded cards: ");
		for (int k = 0; k < d; ++k)
			printf("%d%s", discardedCards[k], k == d - 1 ? "" : ", ");
		putchar('\n');
		printf("Remaining card: %d\n", head->num);
	}

	return 0;
}

void buildList(int n) {
	head = newListNode(1);
	tail = head;

	for (int k = 2; k <= n; ++k) {
		ListNode* newNode = newListNode(k);
		tail->next = newNode;
		tail = tail->next;
	}

	return;
}

ListNode* newListNode(int n) {
	ListNode* node = (ListNode*)malloc(sizeof(ListNode));
	node->num = n;
	node->next = NULL;

	return node;
}
