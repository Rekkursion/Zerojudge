#pragma warning (disable:4996)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXL 30
#define CHAR_NUM 63 // a-z, A-Z, 0-9, white-space

int total;

typedef struct tnode {
	int count;
	struct tnode* children[CHAR_NUM];
}TrieNode;
TrieNode* root;

inline TrieNode* newTrieNode();
inline void insertTrie(TrieNode*, char*);
void visitTrie(TrieNode*, char*, int);
void clearTrie(TrieNode*);
inline int isWhiteLine(char*);
inline int getCharIndex(char);
inline char getCharByIndex(int);
int main() {
	char inpName[MAXL + 1], res[MAXL + 1];
	int kase;

	scanf("%d", &kase), getchar(), gets(inpName);
	while (kase--) {
		root = newTrieNode();
		total = 0;

		while (gets(inpName) && !isWhiteLine(inpName)) {
			++total;
			insertTrie(root, inpName);
		}

		visitTrie(root, res, 0);
		//clearTrie(root);
		root = NULL;

		putchar('\n');
	}

	return 0;
}

TrieNode* newTrieNode() {
	TrieNode* newNode = (TrieNode*)malloc(sizeof(TrieNode));
	newNode->count = 0;
	for (int k = 0; k < CHAR_NUM; ++k)
		newNode->children[k] = NULL;
	return newNode;
}

void insertTrie(TrieNode * node, char* str) {
	TrieNode* p = node;

	for (int k = 0; str[k]; ++k) {
		int chrIdx = getCharIndex(str[k]);

		if (p->children[chrIdx] == NULL)
			p->children[chrIdx] = newTrieNode();
		p = p->children[chrIdx];
	}
	++(p->count);

	return;
}

void visitTrie(TrieNode * node, char* str, int strIdx) {
	if (node == NULL)
		return;

	for (int k = 0; k < CHAR_NUM; ++k) {
		if (node->children[k] != NULL) {
			str[strIdx++] = getCharByIndex(k);
			visitTrie(node->children[k], str, strIdx);
			--strIdx;
		}
	}

	if (node->count) {
		str[strIdx] = '\0';
		printf("%s %.4lf\n", str, (double)(node->count) * 100.0 / (double)total);
	}

	return;
}

void clearTrie(TrieNode * node) {
	if (node == NULL)
		return;

	for (int i = 0; i < CHAR_NUM; ++i) {
		if (node->children[i] != NULL)
			clearTrie(node->children[i]);
	}
	free(node);
	node = NULL;

	return;
}

int isWhiteLine(char* str) {
	for (int k = 0; str[k]; ++k) {
		if (str[k] != ' ')
			return 0;
	}
	return 1;
}

int getCharIndex(char ch) {
	// white-space => 62
	if (ch == ' ')
		return 62;

	// '0'-'9' => 0-9
	if (ch >= 48 && ch <= 57)
		return ch - 48;

	// 'A'-'Z' => 10-35
	if (ch >= 65 && ch <= 90)
		return ch - 55;

	// 'a'-'z' => 36-61
	if (ch >= 97 && ch <= 122)
		return ch - 61;

	return -1;
}

char getCharByIndex(int idx) {
	// 62 => white-space
	if (idx == 62)
		return ' ';

	// 0-9 => '0'-'9'
	if (idx >= 0 && idx <= 9)
		return idx + 48;

	// 10-35 => 'A'-'Z'
	if (idx >= 10 && idx <= 35)
		return idx + 55;

	// 36-61 => 'a'-'z'
	if (idx >= 36 && idx <= 61)
		return idx + 61;

	return 200002;
}
