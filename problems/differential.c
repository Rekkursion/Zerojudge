#pragma warning (disable:4996)

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define MAXL 100001
#define MAX_ELE_COUNT 10001
#define MAX_ELE_LEN 10001
#define islowercasechar(c) ((c) >= 97 && (c) <= 122)
#define isuppercasechar(c) ((c) >= 65 && (c) <= 90)
#define isalphabetchar(c) (islowercasechar(c) || isuppercasechar(c))
#define isnumberchar(c) ((c) >= 48 && (c) <= 57)
#define isechar(c) ((c) == 'e')
#define isxyzchar(c) ((c) == 'x' || (c) == 'y' || (c) == 'z')
#define issctchar(c) ((c) == 's' || (c) == 'c' || (c) == 't')

typedef struct bstnode {
	struct bstnoode* left;
	struct bstnoode* right;
	char key[MAX_ELE_LEN];
	char value[MAX_ELE_LEN];
}BSTNode;
BSTNode* root;

int eqLen, postfixIdx, stkTop;
char equation[MAXL], variableWhichIsGoingToBeWeifened[2], weifenedEquation[MAXL];
char postfix[MAX_ELE_COUNT][MAX_ELE_LEN];
char stack[MAX_ELE_COUNT][MAX_ELE_LEN];
int opPriorities[255];

void solve();

void initOpPriorities();
void removeSpacesAndAddOmittedMultiplySignsAndGetLengthOfEquation();
void assureTheCorrectnessOfAssociativitiesOfCifangOperations();
void toPostfix();
void differential();
bool hasVarWhichIsGoingToBeWeifenedIn(char*);

BSTNode* newBSTNode(char*, char*);
void addBSTNode(char*, char*);
BSTNode* getBSTNode(char*);

int main() {
	scanf("%s %s", equation, variableWhichIsGoingToBeWeifened);
	solve();

	return 0;
}

void solve() {
	root = NULL;

	removeSpacesAndAddOmittedMultiplySignsAndGetLengthOfEquation();
	assureTheCorrectnessOfAssociativitiesOfCifangOperations();
	initOpPriorities();
	toPostfix();

	differential();

	printf("%s\n", weifenedEquation);

	return;
}

void initOpPriorities() {
	opPriorities['\"'] = 6; // unary operator: positive
	opPriorities['\''] = 6; // unary operator: negative
	opPriorities['^'] = 5; // zhishu
	opPriorities['*'] = 2;
	opPriorities['/'] = 2;
	opPriorities['+'] = 1;
	opPriorities['-'] = 1;
	opPriorities['('] = -1;
	opPriorities[')'] = -1;

	return;
}

void removeSpacesAndAddOmittedMultiplySignsAndGetLengthOfEquation() {
	eqLen = strlen(equation);

	// remove spaces
	int j = 0;
	for (int k = 0; k < eqLen; ++k, ++j) {
		if (equation[k] == ' ')
			--j;
		else
			equation[j] = equation[k];
	}

	equation[j] = 0;
	eqLen = j;

	// add the omitted multiply-signs, e.g. xysin(8)cos((5)(1.2)) -> x*y*sin(8)*cos((5)*(1.2))
	char tmp[MAXL];
	j = 0;
	for (int i = 0; i < eqLen; ++i) {
		tmp[j++] = equation[i];

		// 括弧 數字 變數 函數 運算符 自然指數
		if (i + 1 < eqLen) {
			char nextch = equation[i + 1];

			// ')' * ['(' or number or variable or function or 'e']
			if (equation[i] == ')' && (nextch == '(' || isnumberchar(nextch) || nextch == '.' || isxyzchar(nextch) || issctchar(nextch) || nextch == 'l' || isechar(nextch)))
				tmp[j++] = '*';
			// number * ['(' or variable or function or 'e']
			if ((isnumberchar(equation[i]) || equation[i] == '.') && (nextch == '(' || isxyzchar(nextch) || issctchar(nextch) || nextch == 'l' || isechar(nextch)))
				tmp[j++] = '*';
			// variable * ['(' or number or variable or function or 'e']
			if (isxyzchar(equation[i]) && (nextch == '(' || isnumberchar(nextch) || nextch == '.' || isxyzchar(nextch) || issctchar(nextch) || nextch == 'l' || isechar(nextch)))
				tmp[j++] = '*';
			// 'e' * ['(' or number or variable or function or 'e']
			if (isechar(equation[i]) && (nextch == '(' || isnumberchar(nextch) || nextch == '.' || isxyzchar(nextch) || issctchar(nextch) || nextch == 'l' || isechar(nextch))) {
				// exclude the case of 'sec'
				if (i > 0 && equation[i - 1] == 's')
					continue;
				tmp[j++] = '*';
			}
		}
	}
	tmp[j] = 0;

	strcpy(equation, tmp);
	eqLen = j;

	return;
}

void assureTheCorrectnessOfAssociativitiesOfCifangOperations() {
	char lhs[MAXL], rhs[MAXL], llhs[MAXL], rrhs[MAXL];
	int parDepth = 0, i, j;

	// numbers, operators, functions, variables, parentheses
	for (int k = eqLen - 1; k >= 0; --k) {
		if (equation[k] == '^') {

			// get the left-side element
			parDepth = 0;
			for (i = k - 1; i >= 0; --i) {

				// right parenthesis (including function)
				if (equation[k - 1] == ')') {
					if (equation[i] == ')')
						++parDepth;
					else if (equation[i] == '(') {
						--parDepth;
						if (parDepth == 0) {
							// function: ln (natural log)
							if (i > 1 && equation[i - 1] == 'n' && equation[i - 2] == 'l')
								i -= 2;
							// function: trigonometrics
							else if (i > 0 && (equation[i - 1] == 'n' || equation[i - 1] == 's' || equation[i - 1] == 't' || equation[i - 1] == 'c'))
								i -= 3;
							break;
						}
					}
				}

				// number
				else if (isnumberchar(equation[k - 1]) || equation[k - 1] == '.') {
					// deal with scientific notation with sign, e.g. 3.4E+3, 1.32E-9
					if (equation[i] == '+' || equation[i] == '-') {
						if (i > 0 && equation[i - 1] == 'E')
							--i;
						else {
							++i;
							break;
						}
					}
					// general situation
					else if (!isnumberchar(equation[i]) && equation[i] != '.' && equation[i] != 'E') {
						++i;
						break;
					}
				}

				// variable or 'e'
				else if (isxyzchar(equation[k - 1]) || isechar(equation[k - 1]))
					break;
			}
			if (i < 0)
				i = 0;
			strncpy(lhs, equation + i, k - i);
			strncpy(llhs, equation, i);
			lhs[k - i] = 0;
			llhs[i] = 0;

			// get the right-side element
			parDepth = 0;
			int checkIdx = equation[k + 1] == '+' || equation[k + 1] == '-' ? k + 2 : k + 1;
			for (j = checkIdx; j < eqLen; ++j) {

				// left parenthesis or function
				if (equation[checkIdx] == '(' || issctchar(equation[checkIdx]) || equation[checkIdx] == 'l') {
					if (equation[j] == '(')
						++parDepth;
					else if (equation[j] == ')') {
						--parDepth;
						if (parDepth == 0)
							break;
					}
				}

				// number
				else if (isnumberchar(equation[checkIdx]) || equation[checkIdx] == '.' || equation[checkIdx] == 'E') {
					if (!isnumberchar(equation[j]) && equation[j] != '.' && equation[j] != 'E') {
						if ((equation[j] == '+' || equation[j] == '-') && j > 0 && equation[j - 1] == 'E');
						else {
							--j;
							break;
						}
					}
				}

				// variable or 'e'
				else if (isxyzchar(equation[checkIdx]) || isechar(equation[checkIdx]))
					break;
			}
			if (j >= eqLen)
				j = eqLen - 1;
			strncpy(rhs, equation + k + 1, j - k);
			strcpy(rrhs, equation + j + 1);
			rhs[j - k] = 0;

			// combine among lhs, '^', and rhs. build a new equation
			strcpy(equation, llhs);
			strcat(equation, "(");
			strcat(equation, lhs);
			strcat(equation, "^");
			strcat(equation, rhs);
			strcat(equation, ")");
			strcat(equation, rrhs);

			eqLen = strlen(equation);
			++k;
		}
	}

	return;
}

void toPostfix() {
	postfixIdx = stkTop = 0;

	for (int k = 0; k < eqLen; ++k) {
		char ch = equation[k];

		// number
		if (isnumberchar(ch) || ch == '.') {
			int j = k;
			while (j < eqLen && (isnumberchar(equation[j]) || equation[j] == '.' || equation[j] == 'E')) {
				if (equation[j] == 'E' && (equation[j + 1] == '+' || equation[j + 1] == '-'))
					++j;
				++j;
			}
			strncpy(postfix[postfixIdx++], equation + k, j - k);
			k = j - 1;
		}

		// left parenthesis
		else if (ch == '(')
			strcpy(stack[stkTop++], "(");

		// right parenthesis
		else if (ch == ')') {
			while (stkTop > 0 && stack[stkTop - 1][0] != '#' && strcmp(stack[stkTop - 1], "(") != 0)
				strcpy(postfix[postfixIdx++], stack[--stkTop]);

			// it was a function
			if (stkTop > 0 && stack[stkTop - 1][0] == '#')
				strcpy(postfix[postfixIdx++], stack[--stkTop]);
			// it was just a left parenthesis
			else
				--stkTop;
		}

		// operator
		else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^') {
			// a '+' or a '-' is a unary operator if the character before it is an operator or an opened parenthesis or a ','
			// or it's the first character in the expression
			if ((ch == '+' || ch == '-') && (k == 0 || equation[k - 1] == '(' || equation[k - 1] == '+' || equation[k - 1] == '-' || equation[k - 1] == '*' || equation[k - 1] == '/' || equation[k - 1] == '^' || equation[k - 1] == ','))
				ch = ch == '+' ? '\"' : '\''; // " -> positive, ' -> negative

			while (stkTop > 0 && stack[stkTop - 1][0] != '#' && opPriorities[stack[stkTop - 1][0]] >= opPriorities[ch]) {
				if (opPriorities[stack[stkTop - 1][0]] == 6 && opPriorities[ch] == 6)
					break;
				strcpy(postfix[postfixIdx++], stack[--stkTop]);
			}

			switch (ch) {
				case '+':  strcpy(stack[stkTop++], "+"); break;
				case '-':  strcpy(stack[stkTop++], "-"); break;
				case '/':  strcpy(stack[stkTop++], "/"); break;
				case '*':  strcpy(stack[stkTop++], "*"); break;
				case '^':  strcpy(stack[stkTop++], "^"); break; // zhishu
				case '\"': strcpy(stack[stkTop++], "\""); break; // positive sign
				case '\'': strcpy(stack[stkTop++], "\'"); break; // negative sign
			}
		}

		// variable
		else if (ch == 'x' || ch == 'y' || ch == 'z') {
			switch (ch) {
				case 'x': strcpy(postfix[postfixIdx++], "x"); break;
				case 'y': strcpy(postfix[postfixIdx++], "y"); break;
				case 'z': strcpy(postfix[postfixIdx++], "z"); break;
			}
		}

		// 'e'
		else if (isechar(ch)) {
			strcpy(postfix[postfixIdx++], "e");
		}

		// trigonometric function (sin/cos/tan/cot/sec/csc)
		else if (ch == 's' || ch == 'c' || ch == 't') {
			strcpy(stack[stkTop], "#");

			switch (ch) {
				// sin/sec
				case 's': strcat(stack[stkTop++], equation[k + 1] == 'i' ? "sin" : "sec");
					break;
					// cos/cot/csc
				case 'c':
					switch (equation[k + 2]) {
						case 's': strcat(stack[stkTop++], "cos"); break;
						case 't': strcat(stack[stkTop++], "cot"); break;
						case 'c': strcat(stack[stkTop++], "csc"); break;
					}
					break;
					// tan
				case 't': strcat(stack[stkTop++], "tan");
					break;
			}

			k += 3;
		}

		// ln (natural log)
		else if (ch == 'l') {
			strcpy(stack[stkTop++], "#ln");
			k += 2;
		}
	}

	// if operator-stack still has some operators
	while (stkTop > 0)
		strcpy(postfix[postfixIdx++], stack[--stkTop]);

	return;
}

void differential() {
	stkTop = 0;

	for (int k = 0; k < postfixIdx; ++k) {
		// number
		if (isnumberchar(postfix[k][0]) || postfix[k][0] == '.') {
			strcpy(stack[stkTop++], postfix[k]);
			addBSTNode(postfix[k], "0");
		}

		// variable
		else if (isxyzchar(postfix[k][0])) {
			strcpy(stack[stkTop++], postfix[k]);
			addBSTNode(postfix[k], strcmp(postfix[k], variableWhichIsGoingToBeWeifened) == 0 ? "1" : "0");
		}

		// 'e'
		else if (isechar(postfix[k][0])) {
			strcpy(stack[stkTop++], postfix[k]);
			addBSTNode(postfix[k], "0");
		}

		// function
		else if (postfix[k][0] == '#') {
			char funArg[MAX_ELE_LEN];
			strcpy(funArg, stack[--stkTop]);

			char pushee[MAX_ELE_LEN];
			char weifened[MAX_ELE_LEN];

			// sin
			if (strcmp(postfix[k], "#sin") == 0) {
				strcpy(pushee, "sin("), strcat(pushee, funArg), strcat(pushee, ")");
				strcpy(weifened, "(cos("), strcat(weifened, funArg), strcat(weifened, ")*("), strcat(weifened, getBSTNode(funArg)->value), strcat(weifened, "))");
			}

			// cos
			else if (strcmp(postfix[k], "#cos") == 0) {
				strcpy(pushee, "cos("), strcat(pushee, funArg), strcat(pushee, ")");
				strcpy(weifened, "(-sin("), strcat(weifened, funArg), strcat(weifened, ")*("), strcat(weifened, getBSTNode(funArg)->value), strcat(weifened, "))");
			}

			// tan
			else if (strcmp(postfix[k], "#tan") == 0) {
				strcpy(pushee, "tan("), strcat(pushee, funArg), strcat(pushee, ")");
				strcpy(weifened, "(sec("), strcat(weifened, funArg), strcat(weifened, ")^2*("), strcat(weifened, getBSTNode(funArg)->value), strcat(weifened, "))");
			}

			// cot
			else if (strcmp(postfix[k], "#cot") == 0) {
				strcpy(pushee, "cot("), strcat(pushee, funArg), strcat(pushee, ")");
				strcpy(weifened, "(-csc("), strcat(weifened, funArg), strcat(weifened, ")^2*("), strcat(weifened, getBSTNode(funArg)->value), strcat(weifened, "))");
			}

			// sec
			else if (strcmp(postfix[k], "#sec") == 0) {
				strcpy(pushee, "sec("), strcat(pushee, funArg), strcat(pushee, ")");
				strcpy(weifened, "(sec("), strcat(weifened, funArg), strcat(weifened, ")*tan("), strcat(weifened, funArg), strcat(weifened, ")*("), strcat(weifened, getBSTNode(funArg)->value), strcat(weifened, "))");
			}

			// csc
			else if (strcmp(postfix[k], "#csc") == 0) {
				strcpy(pushee, "csc("), strcat(pushee, funArg), strcat(pushee, ")");
				strcpy(weifened, "(-csc("), strcat(weifened, funArg), strcat(weifened, ")*cot("), strcat(weifened, funArg), strcat(weifened, ")*("), strcat(weifened, getBSTNode(funArg)->value), strcat(weifened, "))");
			}

			// ln (natural log)
			else if (strcmp(postfix[k], "#ln") == 0) {
				strcpy(pushee, "ln("), strcat(pushee, funArg), strcat(pushee, ")");
				strcpy(weifened, "(("), strcat(weifened, getBSTNode(funArg)->value), strcat(weifened, ")/("), strcat(weifened, funArg), strcat(weifened, "))");
			}

			strcpy(stack[stkTop++], pushee);
			addBSTNode(pushee, weifened);
		}

		// binary operator
		else if (postfix[k][0] == '+' || postfix[k][0] == '-' || postfix[k][0] == '*' || postfix[k][0] == '/' || postfix[k][0] == '^') {
			char b[MAX_ELE_LEN], a[MAX_ELE_LEN];
			char pushee[MAX_ELE_LEN], weifened[MAX_ELE_LEN];

			strcpy(b, stack[--stkTop]);
			strcpy(a, stack[--stkTop]);

			switch (postfix[k][0]) {
				case '+':
					strcpy(pushee, "("), strcat(pushee, a), strcat(pushee, "+"), strcat(pushee, b), strcat(pushee, ")");
					strcpy(weifened, "("), strcat(weifened, getBSTNode(a)->value), strcat(weifened, "+"), strcat(weifened, getBSTNode(b)->value), strcat(weifened, ")");
					break;

				case '-':
					strcpy(pushee, "("), strcat(pushee, a), strcat(pushee, "-"), strcat(pushee, b), strcat(pushee, ")");
					strcpy(weifened, "("), strcat(weifened, getBSTNode(a)->value), strcat(weifened, "-"), strcat(weifened, getBSTNode(b)->value), strcat(weifened, ")");
					break;

				case '*':
					strcpy(pushee, "(("), strcat(pushee, a), strcat(pushee, ")*("), strcat(pushee, b), strcat(pushee, "))");
					strcpy(weifened, "(("), strcat(weifened, getBSTNode(a)->value), strcat(weifened, ")*("), strcat(weifened, b), strcat(weifened, ")+("), strcat(weifened, a), strcat(weifened, ")*("), strcat(weifened, getBSTNode(b)->value), strcat(weifened, "))");
					break;

				case '/':
					strcpy(pushee, "(("), strcat(pushee, a), strcat(pushee, ")/("), strcat(pushee, b), strcat(pushee, "))");
					strcpy(weifened, "((("), strcat(weifened, getBSTNode(a)->value), strcat(weifened, ")*("), strcat(weifened, b), strcat(weifened, ")-("), strcat(weifened, a), strcat(weifened, ")*("), strcat(weifened, getBSTNode(b)->value), strcat(weifened, "))/(("), strcat(weifened, b), strcat(weifened, ")^2))");
					break;

				case '^':
					// build pushee
					strcpy(pushee, "(("), strcat(pushee, a), strcat(pushee, ")^("), strcat(pushee, b), strcat(pushee, "))");

					// build weifened: 2 cases
					// e.g. (3x)^(5x)
					if (hasVarWhichIsGoingToBeWeifenedIn(b)) {
						char orig[MAX_ELE_LEN];
						strcpy(orig, "(("), strcat(orig, a), strcat(orig, ")^("), strcat(orig, b), strcat(orig, "))");

						char restPart_l[MAX_ELE_LEN];
						strcpy(restPart_l, "(("),
							strcat(restPart_l, getBSTNode(a)->value),
							strcat(restPart_l, ")/("),
							strcat(restPart_l, a),
							strcat(restPart_l, "))*("),
							strcat(restPart_l, b),
							strcat(restPart_l, ")");

						char restPart_r[MAX_ELE_LEN];
						strcpy(restPart_r, "ln("),
							strcat(restPart_r, a),
							strcat(restPart_r, ")*("),
							strcat(restPart_r, getBSTNode(b)->value),
							strcat(restPart_r, ")");

						strcpy(weifened, "("),
							strcat(weifened, orig),
							strcat(weifened, "*("),
							strcat(weifened, restPart_l),
							strcat(weifened, "+"),
							strcat(weifened, restPart_r),
							strcat(weifened, "))");
					}

					// e.g. (3x)^(5)
					else {
						strcpy(weifened, "(("), strcat(weifened, b), strcat(weifened, ")*("), strcat(weifened, a), strcat(weifened, ")^(("), strcat(weifened, b), strcat(weifened, ")-1)*("), strcat(weifened, getBSTNode(a)->value), strcat(weifened, "))");
					}
					break;
			}

			strcpy(stack[stkTop++], pushee);
			addBSTNode(pushee, weifened);
		}

		// uniry operator (pos, neg)
		else if (postfix[k][0] == '\'' || postfix[k][0] == '\"') {
			// neg
			if (postfix[k][0] == '\'') {
				char topEle[MAX_ELE_LEN];
				strcpy(topEle, stack[--stkTop]);

				char pushee[MAX_ELE_LEN];
				char weifened[MAX_ELE_LEN];

				strcpy(pushee, "(-("), strcat(pushee, topEle), strcat(pushee, "))");
				strcpy(weifened, "(-("), strcat(weifened, getBSTNode(topEle)->value), strcat(weifened, "))");

				strcpy(stack[stkTop++], pushee);
				addBSTNode(pushee, weifened);
			}
		}
	}

	strcpy(weifenedEquation, getBSTNode(stack[--stkTop])->value);
	return;
}

bool hasVarWhichIsGoingToBeWeifenedIn(char* str) {
	int len = strlen(str);
	for (int k = 0; k < len; ++k) {
		if (str[k] == variableWhichIsGoingToBeWeifened[0])
			return true;
	}
	return false;
}

BSTNode* newBSTNode(char* key, char* val) {
	BSTNode* node = (BSTNode*)malloc(sizeof(BSTNode));
	strcpy(node->key, key);
	strcpy(node->value, val);
	node->left = node->right = NULL;

	return node;
}

void addBSTNode(char* key, char* val) {
	if (root == NULL)
		root = newBSTNode(key, val);
	else {
		BSTNode* p = root;
		BSTNode* q = NULL;
		int isLeft = 0;

		while (p != NULL) {
			int cmpRes = strcmp(p->key, key);

			// the key has already been in the tree, return directly
			if (cmpRes == 0)
				return;
			// go to right
			else if (cmpRes > 0)
				q = p, p = p->right, isLeft = 0;
			// go to left
			else
				q = p, p = p->left, isLeft = 1;
		}

		BSTNode* newNode = newBSTNode(key, val);
		if (isLeft)
			q->left = newNode;
		else
			q->right = newNode;
	}

	return;
}

BSTNode* getBSTNode(char* key) {
	BSTNode* p = root;

	while (p != NULL) {
		int cmpRes = strcmp(p->key, key);

		// found the key
		if (cmpRes == 0)
			return p;
		// go to right
		else if (cmpRes > 0)
			p = p->right;
		// go to left
		else
			p = p->left;
	}

	// key not found
	return NULL;
}
