#pragma warning (disable:4996)

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#define GRAPHIC_SIZE 21
#define MAXL 2002
#define MAXN 20002
#define MAXP_OP_LEN 11
typedef long double ldouble;
char graphic[GRAPHIC_SIZE][GRAPHIC_SIZE + 1];

char expression[MAXL];

char opStk[MAXN][MAXP_OP_LEN];
int opStkTop;

ldouble numStk[MAXN];
int numStkTop;

char postfix[MAXN][MAXL];
int postfixNum;

inline void toPostfix();
inline int getOperatorPriority(char);
inline int getValueOfExpression(int);
inline ldouble string2LongDouble(char*);
int main() {
	while (gets(expression)) {
		toPostfix();

		for (int r = 0; r < GRAPHIC_SIZE; ++r) {
			for (int c = 0; c < GRAPHIC_SIZE; ++c) {
				if (r == 10 && c == 10)
					graphic[10][10] = '+';
				else if (r == 10)
					graphic[10][c] = '-';
				else if (c == 10)
					graphic[r][10] = '|';
				else
					graphic[r][c] = '.';
			}
			graphic[r][GRAPHIC_SIZE] = '\0';
		}

		for (int x = -10; x <= 10; ++x) {
			int y = getValueOfExpression(x);
			if (y >= -10 && y <= 10)
				graphic[20 - (y + 10)][x + 10] = '*';
		}

		for (int r = 0; r < GRAPHIC_SIZE; ++r)
			puts(graphic[r]);
	}

	return 0;
}

void toPostfix() {
	int len = strlen(expression), startIdx = 0;
	char tmp[MAXL];
	bool start = false;

	postfixNum = opStkTop = 0;
	for (int k = 0; k < len; ++k) {
		char c = expression[k];

		if (c == '=') {
			start = true;
			++k;
			while (k < 0 && expression[k] == ' ')
				++k;
			startIdx = k;
			c = expression[k];
		}
		if (!start)
			continue;

		// a number
		if ((c >= 48 && c <= 57) || c == '.') {
			int i = 0;
			while (k < len && ((expression[k] >= 48 && expression[k] <= 57) || expression[k] == '.' || expression[k] == ' ')) {
				if (expression[k] != ' ')
					tmp[i++] = expression[k];
				++k;
			}
			--k;
			tmp[i] = '\0';

			strcpy(postfix[postfixNum++], tmp);
		}

		// left parenthesis
		else if (c == '(')
			strcpy(opStk[opStkTop++], "(");

		// right parenthesis
		else if (c == ')') {
			while (opStkTop > 0 && opStk[opStkTop - 1][0] != '#' && strcmp(opStk[opStkTop - 1], "("))
				strcpy(postfix[postfixNum++], opStk[--opStkTop]);

			// it's a function
			if (opStkTop > 0 && opStk[opStkTop - 1][0] == '#')
				strcpy(postfix[postfixNum++], opStk[--opStkTop]);

			// it's just a left parenthesis
			else
				--opStkTop;
		}

		// basic operators
		else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
			// a '+' or a '-' is a unary operator if the character before it is an operator or an opened parenthesis or a ','
			// or it's the first character in the expression
			if ((c == '+' || c == '-') && (k == startIdx || expression[k - 1] == '(' || expression[k - 1] == '+' || expression[k - 1] == '-' || expression[k - 1] == '*' || expression[k - 1] == '/' || expression[k - 1] == '^' || expression[k - 1] == ','))
				c = c == '+' ? '\"' : '\''; // " -> positive, ' -> negative

			while (opStkTop > 0 && opStk[opStkTop - 1][0] != '#' && getOperatorPriority(opStk[opStkTop - 1][0]) >= getOperatorPriority(c)) {
				if (getOperatorPriority(opStk[opStkTop - 1][0]) == 6 && getOperatorPriority(c) == 6)
					break;
				strcpy(postfix[postfixNum++], opStk[--opStkTop]);
			}

			switch (c) {
				case '+': strcpy(opStk[opStkTop++], "+"); break;
				case '-': strcpy(opStk[opStkTop++], "-"); break;
				case '/': strcpy(opStk[opStkTop++], "/"); break;
				case '*': strcpy(opStk[opStkTop++], "*"); break;
				case '^': strcpy(opStk[opStkTop++], "^"); break;
				case '\"': strcpy(opStk[opStkTop++], "\""); break; // positive sign
				case '\'': strcpy(opStk[opStkTop++], "\'"); break; // negative sign
			}
		}

		// variable or function
		else if (c == '_' || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
			int i = 0;

			while (k < len && (expression[k] == '_' || (expression[k] >= '0' && expression[k] <= '9') || (expression[k] >= 'a' && expression[k] <= 'z') || (expression[k] >= 'A' && expression[k] <= 'Z'))) {
				tmp[i++] = expression[k];
				++k;
			}
			tmp[i] = '\0';

			while (k < len && expression[k] == ' ')
				++k;

			// variable
			if (k == len || expression[k] != '(') {
				--k;
				strcpy(postfix[postfixNum++], tmp);
			}

			// function
			else {
				// add function to operator stack, e.g. #dot, #norm ...
				for (int h = i; h > 0; --h)
					tmp[h] = tmp[h - 1];
				tmp[0] = '#', tmp[i + 1] = '\0';

				strcpy(opStk[opStkTop++], tmp);
			}
		}
	}

	// operator stack still has some operators
	while (opStkTop > 0)
		strcpy(postfix[postfixNum++], opStk[--opStkTop]);

#ifdef DEBUG
	for (int k = 0; k < postfixNum; ++k)
		printf("|%s|\n", postfix[k]);
	puts("");
#endif

	return;
}

int getOperatorPriority(char op) {
	switch (op) {
		case '\"':
		case '\'':
			return 6;

		case '^':
			return 5;

		case '*':
		case '/':
			return 2;

		case '+':
		case '-':
			return 1;

		// case '(':
		// case ')':
		default: return -1;
	}

	return -1;
}

int getValueOfExpression(int x) {
	numStkTop = 0;

	for (int k = 0; k < postfixNum; ++k) {
		// a number
		if (postfix[k][0] == '.' || (postfix[k][0] >= 48 && postfix[k][0] <= 57))
			numStk[numStkTop++] = string2LongDouble(postfix[k]);

		// a variable
		else if (postfix[k][0] == '_' || (postfix[k][0] >= 'a' && postfix[k][0] <= 'z') || (postfix[k][0] >= 'A' && postfix[k][0] <= 'Z'))
			numStk[numStkTop++] = x;

		// negative or positive sign
		else if (postfix[k][0] == '\'' || postfix[k][0] == '\"') {
			// if it's a negative sign (positive sign needn't to do anything)
			if (postfix[k][0] == '\'')
				numStk[numStkTop - 1] = -numStk[numStkTop - 1];
		}

		// basic operator
		else if (postfix[k][0] == '+' || postfix[k][0] == '-' || postfix[k][0] == '*' || postfix[k][0] == '/' || postfix[k][0] == '^') {
			ldouble b = numStk[--numStkTop];
			ldouble a = numStk[--numStkTop];
			ldouble result = 0.0;

			switch (postfix[k][0]) {
				case '+':
					result = a + b; break;
				case '-':
					result = a - b; break;
				case '*':
					result = a * b; break;
				case '/':
					result = a / b; break;
				case '^':
					result = powl(a, b); break;
			}

			numStk[numStkTop++] = result;
		}

		// function
		else /* if (postfix[k][0] == '#') */ {
			if (!strcmp(postfix[k], "#sin"))
				numStk[numStkTop - 1] = sinl(numStk[numStkTop - 1]);
			else if (!strcmp(postfix[k], "#cos"))
				numStk[numStkTop - 1] = cosl(numStk[numStkTop - 1]);
			else /* if (!strcmp(postfix[k], "#log10")) */
				numStk[numStkTop - 1] = log10l(numStk[numStkTop - 1]);
		}
	}

	ldouble ret_double = numStk[--numStkTop];
	return (int)floorl(ret_double);
}

ldouble string2LongDouble(char* str) {
	int len = strlen(str);

	if (len == 0)
		return 0.0;

	char c = str[0];
	int k = 0;
	bool isDecimalMode = (c == '.');
	ldouble num = 0.0, deciDig = 0.1;

	if (c == '.')
		++k;
	while (k < len && str[k] >= 48 && str[k] <= 57) {
		if (isDecimalMode)
			num += (ldouble)(str[k] - 48) * deciDig,
			deciDig *= 0.1;
		else
			num = (num * 10.0) + (ldouble)(str[k] - 48);

		++k;
	}

	if (str[k] == '.') {
		deciDig = 0.1;
		++k;
		while (k < len && str[k] >= 48 && str[k] <= 57) {
			num += (ldouble)(str[k] - 48) * deciDig; deciDig *= 0.1;
			++k;
		}
	}
	--k;

	return num;
}
