#pragma warning (disable:4996)

#include <stdio.h>
#include <string.h>
#define MAXL 200002
char products[MAXL];
char stack[MAXL];
char contents[MAXL];

int parenthesesMatch(char, char);
int main() {
	int n, productsLen, stkTop, contentsIdx, hasContent, broken;

	while (~scanf("%d", &n) && n) {
		while (n--) {
			scanf("%s", products);

			productsLen = strlen(products);
			stkTop = 0;
			broken = 0;
			contentsIdx = 0;

			for (int k = 0; k < productsLen; ++k) {
				// opened parenthesis
				if (products[k] == '(' || products[k] == '[' || products[k] == '{') {
					hasContent = stkTop;
					stack[stkTop++] = products[k];

					if (hasContent)
						contents[contentsIdx++] = products[k];
				}

				// close parenthesis
				else if (products[k] == ')' || products[k] == ']' || products[k] == '}') {
					// stack is empty
					if (stkTop == 0) {
						broken = 1;
						break;
					}
					
					// parentheses are not matched
					if (!parenthesesMatch(stack[--stkTop], products[k])) {
						broken = 1;
						break;
					}

					// the outest parentheses
					if (stkTop == 0) {
						if (!hasContent) {
							broken = 1;
							break;
						}
					}
					else
						contents[contentsIdx++] = products[k];
				}

				// invalid character
				else {
					broken = 1;
					break;
				}
			}

			// stack emptiness check
			if (stkTop > 0)
				broken = 1;

			if (broken)
				puts("Product Broken!!");
			else
				contents[contentsIdx] = '\0', puts(contents);
		}
	}

	return 0;
}

int parenthesesMatch(char opened, char close) {
	return (opened == '(' && close == ')') ||
		(opened == '[' && close == ']') ||
		(opened == '{' && close == '}');
}
