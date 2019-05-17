#pragma warning (disable:4996)

#include <stdio.h>

int summation_recursion(int);
int summation_terminal(int);
int (*summation[2])(int) = { summation_recursion, summation_terminal };

int main() {
	int n;
	scanf("%d", &n);
	printf("%d\n", summation[n == 1](n));

	return 0;
}

int summation_recursion(int n) {
	return n + summation[n == 2](n - 1);
}

int summation_terminal(int n) {
	return 1;
}
