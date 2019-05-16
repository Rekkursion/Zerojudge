#pragma warning (disable:4996)

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAX_NUMBER 1000
bool isInMemory[MAX_NUMBER + 1];
int currentMemoryUsage = 0;

typedef struct qnode {
	int data;
	struct qnode* next;
}Queue;
Queue* head = NULL;
Queue* tail = NULL;

void enqueue(int, const int*);
void dequeue();
int main() {
	int memSize, n, word, queryNum;
	scanf("%d %d", &memSize, &n);

	for (int k = 0; k <= MAX_NUMBER; ++k)
		isInMemory[k] = false;
	queryNum = 0;

	while (n--) {
		scanf("%d", &word);

		// if the word is not in the memory
		if (!isInMemory[word]) {
			++queryNum;
			if (memSize > 0) {
				isInMemory[word] = true;
				enqueue(word, &memSize);
			}
		}
	}

	printf("%d\n", queryNum);
	return 0;
}

void enqueue(int x, const int* memSizePtr) {
	Queue* newNode = (Queue*)malloc(sizeof(Queue));
	newNode->data = x;
	newNode->next = NULL;

	if (currentMemoryUsage < (*memSizePtr)) {
		if (head == NULL) {
			head = newNode;
			tail = newNode;
		}
		else {
			tail->next = newNode;
			tail = tail->next;
		}

		++currentMemoryUsage;
	}
	else /* if (currentMemoryUsage == (*memSizePtr)) */ {
		tail->next = newNode;
		tail = tail->next;
		dequeue();
	}

	return;
}

void dequeue() {
	if (head == NULL)
		return;

	Queue* qt = head;
	head = head->next;
	isInMemory[qt->data] = false;
	free(qt);

	return;
}
