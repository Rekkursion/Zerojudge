#pragma warning (disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_NUM 2147483648ull
typedef unsigned long long ull;
ull minDifference;

typedef struct node {
	int data;
	int height;
	struct node* left;
	struct node* right;
}Node;
Node* avl = NULL;

inline Node* avlInsert(Node*, int);
inline Node* avlQuery(Node*, int);
inline int getMax(Node*, Node*);
inline int getHeight(Node*);
inline void visitAvl(Node*);
inline Node* rightRotate(Node*);
inline Node* leftRotate(Node*);

int main() {
	int n, number, sum = 0, nCounter = 0;

	scanf("%d", &n);
	while (nCounter < n) {
		scanf("%d", &number);

		if (avl == NULL)
			sum += number;
		else {
			minDifference = MAX_NUM;
			avlQuery(avl, number);
			sum += (int)minDifference;
		}

		avl = avlInsert(avl, number);
		++nCounter;
	}

	printf("%d\n", sum);
	return 0;
}

Node* avlInsert(Node* root, int number) {
	Node* newNode = NULL;
	int balance;

	if (root == NULL) {
		newNode = (Node*)malloc(sizeof(Node));

		newNode->data = number;
		newNode->height = 0;
		newNode->left = newNode->right = NULL;

		return newNode;
	}

	// go to left child
	if (number < root->data)
		root->left = avlInsert(root->left, number);

	// go to right child
	else if (number > root->data)
		root->right = avlInsert(root->right, number);

	// found the data
	else
		return root;


	root->height = getMax(root->left, root->right) + 1;
	balance = getHeight(root->left) - getHeight(root->right);

	//if(balance > 1 || balance < -1)
	//	printf("root: %d h:%d b:%d\n", root->data, root->height, balance);

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

Node* avlQuery(Node* root, int pNumber) {
	Node* leftRes = NULL;
	Node* rightRes = NULL;

	// update the minima of absolute difference
	if ((ull)abs(root->data - pNumber) < minDifference)
		minDifference = (ull)abs(root->data - pNumber);

	// exactly the hash code
	if (root->data == pNumber)
		return root;

	// to left
	else if (pNumber < root->data) {
		if (root->left == NULL)
			return NULL;
		return avlQuery(root->left, pNumber);
	}

	// to right
	else /* if (pNumber > root->data) */ {
		if (root->right == NULL)
			return NULL;
		return avlQuery(root->right, pNumber);
	}
}

int getMax(Node* a, Node* b) {
	if (a == NULL && b == NULL)
		return (-1);

	else if (a == NULL)
		return b->height;

	else if (b == NULL)
		return a->height;

	else
		return ((a->height > b->height) ? a->height : b->height);
}

int getHeight(Node* nod) {
	return ((nod == NULL) ? (-1) : nod->height);
}

void visitAvl(Node* root) {
	if (root->left != NULL)
		visitAvl(root->left);

	printf("%d\n", root->data);

	if (root->right != NULL)
		visitAvl(root->right);

	return;
}

Node* rightRotate(Node* root) {
	Node* newRoot = root->left;
	root->left = newRoot->right;
	newRoot->right = root;

	root->height = getMax(root->left, root->right) + 1;
	newRoot->height = getMax(newRoot->left, newRoot->right) + 1;

	return newRoot;
}

Node* leftRotate(Node* root) {
	Node* newRoot = root->right;
	root->right = newRoot->left;
	newRoot->left = root;

	root->height = getMax(root->left, root->right) + 1;
	newRoot->height = getMax(newRoot->left, newRoot->right) + 1;

	return newRoot;
}
