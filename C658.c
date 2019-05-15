#pragma warning (disable:4996)

#include <stdio.h>
#include <stdlib.h>
typedef unsigned long long ull;

void getAllPerfectSquareNumber();
ull calcHashCode(ull);

typedef struct lnode {
	ull data;
	struct lnode* next;
}ListNode;

typedef struct node {
	struct lnode* head;
	struct lnode* tail;
	ull hashCode;
	int height;
	struct node* left;
	struct node* right;
}Node;
struct node* avl = NULL;

void listInsert(struct node*, ull);
void visitList(struct lnode*);

struct node* avlInsert(struct node*, ull, ull);
struct node* avlQuery(struct node*, ull);
int getMax(struct node*, struct node*);
int getHeight(struct node*);
void visitAvl(struct node*);
struct node* rightRotate(struct node*);
struct node* leftRotate(struct node*);

int main() {
	getAllPerfectSquareNumber();

	ull inp, hashCode;
	struct node* res;
	while (~scanf("%llu", &inp)) {
		hashCode = calcHashCode(inp);
		if (hashCode == 0ull)
			puts("0");
		else {
			res = avlQuery(avl, hashCode);
			if (res == NULL)
				puts("0");
			else
				visitList(res->head);
		}
	}

	return 0;
}

// ======================================================================

void getAllPerfectSquareNumber() {
	const ull MAX_NUM = 9999999999ull;

	for (ull k = 1ull; k * k <= MAX_NUM; ++k) {
		ull hashCode = calcHashCode(k * k);
		if (hashCode != 0ull)
			avl = avlInsert(avl, k * k, hashCode);
	}

	return;
}

ull calcHashCode(ull num) {
	int digitCnt[10] = { 0 };

	while (num > 0ull) {
		++digitCnt[(int)(num % 10ull)];
		num /= 10ull;
	}

	if (digitCnt[0] > 0)
		return 0ull;

	ull hashCode = 0ull;
	for (int k = 1; k < 10; ++k)
		hashCode = (hashCode * 10ull) + digitCnt[k];

	return hashCode;
}

// ======================================================================

void listInsert(struct node* root, ull pData) {
	struct lnode* newListNode = NULL;
	newListNode = (struct lnode*)malloc(sizeof(struct lnode));
	newListNode->data = pData;
	newListNode->next = NULL;

	if (root->head == NULL) {
		root->head = newListNode;
		root->tail = newListNode;
	}
	else {
		root->tail->next = newListNode;
		root->tail = root->tail->next;
	}

	return;
}

void visitList(struct lnode* head) {
	struct lnode* p = head;

	while (p != NULL) {
		printf("%llu ", p->data);
		p = p->next;
	}
	puts("");

	return;
}

// ======================================================================

struct node* avlInsert(struct node* root, ull pNumber, ull pHashCode) {

	struct node* newNode = NULL;
	int balance;

	if (root == NULL) {
		newNode = (struct node*)malloc(sizeof(struct node));

		newNode->hashCode = pHashCode;
		newNode->height = 0;
		newNode->left = newNode->right = NULL;
		newNode->head = newNode->tail = NULL;
		listInsert(newNode, pNumber);

		return newNode;
	}

	// go to left child
	if (pHashCode < root->hashCode)
		root->left = avlInsert(root->left, pNumber, pHashCode);

	// go to right child
	else if (pHashCode > root->hashCode)
		root->right = avlInsert(root->right, pNumber, pHashCode);

	// found the number
	else {
		listInsert(root, pNumber);
		return root;
	}


	root->height = getMax(root->left, root->right) + 1;
	balance = getHeight(root->left) - getHeight(root->right);

	// left
	if (balance > 1) {

		// left-left
		if (getHeight(root->left->left) >= getHeight(root->left->right))
			root = rightRotate(root);

		// left-right
		else {
			root->left = leftRotate(root->left);
			root = rightRotate(root);
		}
	}

	// right
	if (balance < -1) {

		// right-right
		if (getHeight(root->right->right) >= getHeight(root->right->left))
			root = leftRotate(root);

		// right-left
		else {
			root->right = rightRotate(root->right);
			root = leftRotate(root);
		}
	}

	return root;
}

struct node* avlQuery(struct node* root, ull pHashCode) {
	struct node* leftRes = NULL;
	struct node* rightRes = NULL;

	// exactly the hash code
	if (root->hashCode == pHashCode)
		return root;
	// to left
	else if (pHashCode < root->hashCode) {
		if (root->left == NULL)
			return NULL;
		return avlQuery(root->left, pHashCode);
	}
	// to right
	else /* if (pHashCode > root->hashCode) */ {
		if (root->right == NULL)
			return NULL;
		return avlQuery(root->right, pHashCode);
	}
}

int getMax(struct node* a, struct node* b) {
	if (a == NULL && b == NULL)
		return (-1);

	else if (a == NULL)
		return b->height;

	else if (b == NULL)
		return a->height;

	else
		return ((a->height > b->height) ? a->height : b->height);
}

int getHeight(struct node* nod) {
	return ((nod == NULL) ? (-1) : nod->height);
}

void visitAvl(struct node* root) {
	if (root->left != NULL)
		visitAvl(root->left);

	// do something

	if (root->right != NULL)
		visitAvl(root->right);

	return;
}

struct node* rightRotate(struct node* root) {

	struct node* newRoot = root->left;
	root->left = newRoot->right;
	newRoot->right = root;

	root->height = getMax(root->left, root->right) + 1;
	newRoot->height = getMax(newRoot->left, newRoot->right) + 1;

	return newRoot;
}

struct node* leftRotate(struct node* root) {

	struct node* newRoot = root->right;
	root->right = newRoot->left;
	newRoot->left = root;

	root->height = getMax(root->left, root->right) + 1;
	newRoot->height = getMax(newRoot->left, newRoot->right) + 1;

	return newRoot;
}
