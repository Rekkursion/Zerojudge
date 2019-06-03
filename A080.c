#pragma warning (disable:4996)

#include <stdio.h>
#include <stdlib.h>
#define MAXL 63
char str[MAXL + 1];

typedef struct tnode {
	struct tnode* children[26];
}TrieNode;
TrieNode* root = NULL;

inline TrieNode* newTrieNode();
inline int insertTrie(TrieNode*, char*);
int main() {
	root = newTrieNode();
	int nodeNum = 1;

	while (~scanf("%s", &str))
		nodeNum += insertTrie(root, str);
	printf("%d\n", nodeNum);

	return 0;
}

TrieNode* newTrieNode() {
	TrieNode* newNode = (TrieNode*)malloc(sizeof(TrieNode));
	for (int k = 0; k < 26; ++k)
		newNode->children[k] = NULL;
	return newNode;
}

int insertTrie(TrieNode * node, char* str) {
	TrieNode* p = node;
	int trieIdx;
	int numOfNewNode = 0;

	for (int k = 0; str[k]; ++k) {
		trieIdx = str[k] - 65;

		if (p->children[trieIdx] == NULL)
			++numOfNewNode,
			p->children[trieIdx] = newTrieNode();

		p = p->children[trieIdx];
	}

	return numOfNewNode;
}
