#pragma warning (disable:4996)

#include <stdio.h>
#include <stdlib.h>
#define MAXN 1000001
#define max(a, b) ((a) < (b) ? (b) : (a))
int snowflakes[MAXN];

typedef struct node {
	int data;
	int height;
	struct node* left;
	struct node* right;
}Node;
Node* avl = NULL;

Node* avlInsert(Node*, int);
Node* avlQuery(Node*, int);
Node* avlRemove(Node*, int);
Node* avlClear(Node*);
Node* findMin(Node*);
int getMax(Node*, Node*);
int getHeight(Node*);
void visitAvl(Node*);
Node* rightRotate(Node*);
Node* leftRotate(Node*);

static inline int readNonNegativeInt(int* const);
int main() {
	int kase;
	readNonNegativeInt(&kase);

	int n, l, r, maxRange;
	while (kase--) {
		readNonNegativeInt(&n);
		for (int k = 0; k < n; ++k)
			readNonNegativeInt(&snowflakes[k]);

		maxRange = !!n;
		l = r = 0;
		for (int k = 0; k < n; ++k) {
			// number exists
			if (avlQuery(avl, snowflakes[k])) {
				do {
					avl = avlRemove(avl, snowflakes[l]);
					++l;
				} while (avlQuery(avl, snowflakes[k]));
			}

			avl = avlInsert(avl, snowflakes[k]);
			++r;

			maxRange = max(maxRange, r - l);
			//visitAvl(avl); putchar('\n');
		}

		avl = avlClear(avl);
		printf("%d\n", maxRange);
	}

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

Node* avlQuery(Node* root, int value) {
	if (root == NULL)
		return NULL;

	Node* leftResult = NULL;
	Node* rightResult = NULL;

	if (root->data == value)
		return root;

	else if (root->data < value) {
		if (root->right == NULL)
			return NULL;
		return avlQuery(root->right, value);
	}

	else /* if (root->data > value) */ {
		if (root->left == NULL)
			return NULL;
		return avlQuery(root->left, value);
	}
}

Node* avlRemove(Node* root, int value) {
	if (root == NULL)
		return;

	// go to left
	if (value < root->data)
		root->left = avlRemove(root->left, value);

	// go to right
	else if (value > root->data)
		root->right = avlRemove(root->right, value);

	// exactly the value
	else {
		Node* minNode;
		if (root->left && root->right) {
			minNode = findMin(root->right);
			root->data = minNode->data;
			root->right = avlRemove(root->right, root->data);
		}
		else {
			minNode = root;
			if (root->left == NULL)
				root = root->right;
			else if (root->right == NULL)
				root = root->left;
			free(minNode);
		}
	}

	if (root == NULL)
		return root;

	root->height = getMax(root->left, root->right) + 1;
	int balance = getHeight(root->left) - getHeight(root->right);

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

Node* avlClear(Node* root) {
	if (root == NULL)
		return NULL;

	if (root->left)
		root->left = avlClear(root->left);
	if (root->right)
		root->right = avlClear(root->right);

	free(root);
	return NULL;
}

Node* findMin(Node* root) {
	if (root == NULL)
		return NULL;
	else if (root->left == NULL)
		return root;
	else
		return findMin(root->left);
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

int getHeight(Node* node) {
	return ((node == NULL) ? (-1) : node->height);
}

void visitAvl(Node* root) {
	if (root == NULL)
		return;

	if (root->left != NULL)
		visitAvl(root->left);

	//printf("%d %d %d\n", root->data, root->count, root->height);
	//printf("%d %d\n", root->data, root->count);
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

static inline int readNonNegativeInt(int* const integer) {
	static char ch;
	while ((ch = getchar()) < 48 || ch > 57);

	(*integer) = ch - 48;
	while ((ch = getchar()) >= 48 && ch <= 57)
		(*integer) = ((*integer) * 10) + (ch - 48);

	return 1;
}
