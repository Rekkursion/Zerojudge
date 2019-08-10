#pragma warning (disable:4996)

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <map>
#include <string>
#include <cmath>
using namespace std;

#define islowercasechar(c) ((c) >= 97 && (c) <= 122)
#define isuppercasechar(c) ((c) >= 65 && (c) <= 90)
#define isalphabetchar(c) (islowercasechar(c) || isuppercasechar(c))
#define isnumberchar(c) ((c) >= 48 && (c) <= 57)
#define isechar(c) ((c) == 'e')
#define isxyzchar(c) ((c) == 'x' || (c) == 'y' || (c) == 'z')
#define issctchar(c) ((c) == 's' || (c) == 'c' || (c) == 't')

#define ZERO_CHECK_THRESHOLD (0.01)
#define abs(v) ((v) < 0 ? (-(v)) : (v))
#define iszero(v) ((v) <= ZERO_CHECK_THRESHOLD)

#define E 2.71828182845904523536

#define MAXL 1001
#define QQ

vector<string> systemInput;
vector<string> systemOutput;
vector<string> userOutput;

map<string, string> result;

int opPriorities[255];

void getThreeFilesContent(char*, char*, char*);
void initOpPriorities();
void initResult();
void doJudge();
string preprocessEquation(string);
vector<string> toPostfix(string);
double evaluate(vector<string>, double, double, double);
void setResult(string, int, string, string, string);

int main(int argc, char* argv[]) {
	if (argc != 4)
		return 0;

	getThreeFilesContent(argv[1], argv[2], argv[3]);
	initOpPriorities();
	initResult();
	doJudge();

	for (map<string, string>::iterator it = result.begin(); it != result.end(); ++it)
		printf("%s=%s\n", it->first.c_str(), it->second.c_str());

	return 0;
}

void getThreeFilesContent(char* argv0, char* argv1, char* argv2) {
	ifstream f_in(argv0);
	ifstream f_ans(argv1);
	ifstream f_out(argv2);
	string line;

	systemInput.clear();
	systemOutput.clear();
	userOutput.clear();

	while (getline(f_in, line))
		systemInput.push_back(line);
	while (getline(f_ans, line))
		systemOutput.push_back(line);
	while (getline(f_out, line))
		userOutput.push_back(line);

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

void initResult() {
	result.clear();

	result.insert(make_pair("$JUDGE_RESULT", ""));
	result.insert(make_pair("$LINECOUNT", ""));
	result.insert(make_pair("$USEROUT", ""));
	result.insert(make_pair("$SYSTEMOUT", ""));
	result.insert(make_pair("$MESSAGE", ""));

	return;
}

void doJudge() {
	if (userOutput.size() == 0) {
		setResult("WA", 1, "", "", "輸出為空。");
		return;
	} else if (userOutput.size() > 1) {
		setResult("WA", 1, "", "", "請勿分行，每筆輸出只佔一行。");
		return;
	}

	string weifened = userOutput[0];
	string preprocessed = preprocessEquation(weifened);
	vector<string> postfix = toPostfix(preprocessed);

	double x, y, z, correctEvaluatedValue, userEvaluatedValue;
	for (int k = 0; k < systemOutput.size(); ++k) {
		sscanf(systemOutput[k].c_str(), "%lf %lf %lf %lf", &x, &y, &z, &correctEvaluatedValue);
		userEvaluatedValue = evaluate(postfix, x, y, z);

#ifdef QQ
		printf("correct:|%lf|    user:|%lf|\n", correctEvaluatedValue, userEvaluatedValue);
#endif

		if (!iszero(abs(correctEvaluatedValue - userEvaluatedValue))) {
			char userOutStr[MAXL], sysOutStr[MAXL];
			sprintf(userOutStr, "%lf", userEvaluatedValue);
			sprintf(sysOutStr, "%lf", correctEvaluatedValue);
			setResult("WA", k + 1, userOutStr, sysOutStr, "計算結果不正確。");
			return;
		}
	}

	setResult("AC", 0, "", "", "");
	return;
}

string preprocessEquation(string equation) {
	int k, i, j;

	// remove spaces
	string eq = "";
	for (k = 0; k < equation.length(); ++k) {
		if (equation[k] != ' ')
			eq += equation[k];
	}

	// add omitted multiply-signs
	string tmp = "";
	for (i = 0; i < eq.length(); ++i) {
		tmp += eq[i];
	
		// 括弧 數字 變數 函數 運算符 自然指數
		if (i + 1 < eq.length()) {
			char nextch = eq[i + 1];
	
			// ')' * ['(' or number or variable or function or 'e']
			if (eq[i] == ')' && (nextch == '(' || isnumberchar(nextch) || nextch == '.' || isxyzchar(nextch) || issctchar(nextch) || nextch == 'l' || isechar(nextch)))
				tmp += "*";
			// number * ['(' or variable or function or 'e']
			if ((isnumberchar(eq[i]) || eq[i] == '.') && (nextch == '(' || isxyzchar(nextch) || issctchar(nextch) || nextch == 'l' || isechar(nextch)))
				tmp += "*";
			// variable * ['(' or number or variable or function or 'e']
			if (isxyzchar(eq[i]) && (nextch == '(' || isnumberchar(nextch) || nextch == '.' || isxyzchar(nextch) || issctchar(nextch) || nextch == 'l' || isechar(nextch)))
				tmp += "*";
			// 'e' * ['(' or number or variable or function or 'e']
			if (isechar(eq[i]) && (nextch == '(' || isnumberchar(nextch) || nextch == '.' || isxyzchar(nextch) || issctchar(nextch) || nextch == 'l' || isechar(nextch)))
				tmp += "*";
		}
	}
	eq = tmp;

	// assure the correctness of associativities of exponent-operations
	// numbers, operators, functions, variables, parentheses
	int parDepth = 0;
	string lhs, rhs, llhs, rrhs;
	for (k = eq.length() - 1; k >= 0; --k) {
		if (eq[k] == '^') {
	
			// get the left-side element
			parDepth = 0;
			for (i = k - 1; i >= 0; --i) {
	
				// right parenthesis (including function)
				if (eq[k - 1] == ')') {
					if (eq[i] == ')')
						++parDepth;
					else if (eq[i] == '(') {
						--parDepth;
						if (parDepth == 0) {
							// function: ln (natural log)
							if (i > 1 && eq[i - 1] == 'n' && eq[i - 2] == 'l')
								i -= 2;
							// function: trigonometrics
							else if (i > 0 && (eq[i - 1] == 'n' || eq[i - 1] == 's' || eq[i - 1] == 't' || eq[i - 1] == 'c'))
								i -= 3;
							break;
						}
					}
				}
	
				// number
				else if (isnumberchar(eq[k - 1]) || eq[k - 1] == '.') {
					// deal with scientific notation with sign, e.g. 3.4E+3, 1.32E-9
					if (eq[i] == '+' || eq[i] == '-') {
						if (i > 0 && eq[i - 1] == 'E')
							--i;
						else {
							++i;
							break;
						}
					}
					// general situation
					else if (!isnumberchar(eq[i]) && eq[i] != '.' && eq[i] != 'E') {
						++i;
						break;
					}
				}
	
				// variable or 'e'
				else if (isxyzchar(eq[k - 1]) || isechar(eq[k - 1]))
					break;
			}
			if (i < 0)
				i = 0;
			lhs = eq.substr(i, k - i);
			llhs = eq.substr(0, i);
	
			// get the right-side element
			parDepth = 0;
			int checkIdx = eq[k + 1] == '+' || eq[k + 1] == '-' ? k + 2 : k + 1;
			for (j = checkIdx; j < eq.length(); ++j) {
	
				// left parenthesis or function
				if (eq[checkIdx] == '(' || issctchar(eq[checkIdx]) || eq[checkIdx] == 'l') {
					if (eq[j] == '(')
						++parDepth;
					else if (eq[j] == ')') {
						--parDepth;
						if (parDepth == 0)
							break;
					}
				}
	
				// number
				else if (isnumberchar(eq[checkIdx]) || eq[checkIdx] == '.' || eq[checkIdx] == 'E') {
					if (!isnumberchar(eq[j]) && eq[j] != '.' && eq[j] != 'E') {
						if ((eq[j] == '+' || eq[j] == '-') && j > 0 && eq[j - 1] == 'E');
						else {
							--j;
							break;
						}
					}
				}
	
				// variable or 'e'
				else if (isxyzchar(eq[checkIdx]) || isechar(eq[checkIdx]))
					break;
			}
			if (j >= eq.length())
				j = eq.length() - 1;
			rhs = eq.substr(k + 1, j - k);
			rrhs = eq.substr(j + 1);
	
			eq = llhs + "(" + lhs + "^" + rhs + ")" + rrhs;
			++k;

#ifdef QQ
			printf("||%s||\n", eq.c_str());
#endif
		}
	}

	return eq;
}

vector<string> toPostfix(string equation) {
	int eqLen = equation.length();
	stack<string> stack;
	vector<string> postfix;

	postfix.clear();
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
			postfix.push_back(equation.substr(k, j - k));
			k = j - 1;
		}

		// left parenthesis
		else if (ch == '(')
			stack.push("(");

		// right parenthesis
		else if (ch == ')') {
			while (!stack.empty() && stack.top()[0] != '#' && strcmp(stack.top().c_str(), "(") != 0) {
				postfix.push_back(stack.top());
				stack.pop();
			}

			// it was a function
			if (!stack.empty() && stack.top()[0] == '#') {
				postfix.push_back(stack.top());
				stack.pop();
			}
			// it was just a left parenthesis
			else
				stack.pop();
		}

		// operator
		else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^') {
			// a '+' or a '-' is a unary operator if the character before it is an operator or an opened parenthesis or a ','
			// or it's the first character in the expression
			if ((ch == '+' || ch == '-') && (k == 0 || equation[k - 1] == '(' || equation[k - 1] == '+' || equation[k - 1] == '-' || equation[k - 1] == '*' || equation[k - 1] == '/' || equation[k - 1] == '^' || equation[k - 1] == ','))
				ch = ch == '+' ? '\"' : '\''; // " -> positive, ' -> negative

			while (!stack.empty() && stack.top()[0] != '#' && opPriorities[stack.top()[0]] >= opPriorities[ch]) {
				if (opPriorities[stack.top()[0]] == 6 && opPriorities[ch] == 6)
					break;
				postfix.push_back(stack.top());
				stack.pop();
			}

			switch (ch) {
				case '+':  stack.push("+"); break;
				case '-':  stack.push("-"); break;
				case '/':  stack.push("/"); break;
				case '*':  stack.push("*"); break;
				case '^':  stack.push("^"); break; // zhishu
				case '\"': stack.push("\""); break; // positive sign
				case '\'': stack.push("\'"); break; // negative sign
			}
		}

		// variable
		else if (ch == 'x' || ch == 'y' || ch == 'z') {
			switch (ch) {
				case 'x': postfix.push_back("x"); break;
				case 'y': postfix.push_back("y"); break;
				case 'z': postfix.push_back("z"); break;
			}
		}

		// 'e'
		else if (isechar(ch))
			postfix.push_back("e");
		
		// trigonometric function (sin/cos/tan/cot/sec/csc)
		else if (ch == 's' || ch == 'c' || ch == 't') {
			string funName = "#";
		
			switch (ch) {
				// sin/sec
				case 's': funName += equation[k + 1] == 'i' ? "sin" : "sec";
					break;
				// cos/cot/csc
				case 'c':
					switch (equation[k + 2]) {
						case 's': funName += "cos"; break;
						case 't': funName += "cot"; break;
						case 'c': funName += "csc"; break;
					}
					break;
				// tan
				case 't': funName += "tan";
					break;
			}

			stack.push(funName);
			k += 3;
		}
		
		// ln (natural log)
		else if (ch == 'l') {
			stack.push("#ln");
			k += 2;
		}
	}
		
	// if operator-stack still has some operators
	while (!stack.empty()) {
		postfix.push_back(stack.top());
		stack.pop();
	}

#ifdef QQ
	puts("postfix:");
	for (int k = 0; k < postfix.size(); ++k)
		printf("|%s", postfix[k].c_str());
	puts("|");
#endif

	return postfix;
}

double evaluate(vector<string> postfix, double xVal, double yVal, double zVal) {
	stack<double> stack;

	for (int k = 0; k < postfix.size(); ++k) {
		string obj = postfix[k];

		// number
		if (isnumberchar(obj[0]) || obj[0] == '.') {
			double num;
			sscanf(obj.c_str(), "%lf", &num);
			stack.push(num);
		}

		// variable
		else if (isxyzchar(obj[0])) {
			double num;
			switch (obj[0]) {
				case 'x': num = xVal; break;
				case 'y': num = yVal; break;
				case 'z': num = zVal; break;
			}
			stack.push(num);
		}

		// 'e'
		else if (isechar(obj[0])) {
			stack.push(E);
		}

		// operator
		else if (obj[0] == '+' || obj[0] == '-' || obj[0] == '*' || obj[0] == '/' || obj[0] == '^') {
			double b = stack.top(); stack.pop();
			double a = stack.top(); stack.pop();
			double ret;

			switch (obj[0]) {
				case '+': ret = a + b; break;
				case '-': ret = a - b; break;
				case '*': ret = a * b; break;
				case '/': ret = a / b; break;
				case '^': ret = pow(a, b); break;
			}

			stack.push(ret);
		}

		// function
		else if (obj[0] == '#') {
			double arg = stack.top(); stack.pop();
			double ret;

			// ln
			if (!strcmp(obj.c_str(), "#ln"))
				ret = log(arg);
			// sin
			else if (!strcmp(obj.c_str(), "#sin"))
				ret = sin(arg);
			// cos
			else if (!strcmp(obj.c_str(), "#cos"))
				ret = cos(arg);
			// tan
			else if (!strcmp(obj.c_str(), "#tan"))
				ret = tan(arg);
			// cot
			else if (!strcmp(obj.c_str(), "#cot"))
				ret = 1.0 / tan(arg);
			// sec
			else if (!strcmp(obj.c_str(), "#sec"))
				ret = 1.0 / cos(arg);
			// csc
			else if (!strcmp(obj.c_str(), "#csc"))
				ret = 1.0 / sin(arg);

			stack.push(ret);
		}
	}

	return stack.top();
}

void setResult(string judgeResult, int lineCount, string userOut, string systemOut, string message) {
	char lineCountString[100];
	sprintf(lineCountString, "%d", lineCount);

	result["$JUDGE_RESULT"] = judgeResult;
	result["$LINECOUNT"] = lineCountString;
	result["$USEROUT"] = userOut;
	result["$SYSTEMOUT"] = systemOut;
	result["$MESSAGE"] = message;

	return;
}
