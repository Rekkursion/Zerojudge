#pragma warning (disable:4996)

#include <stdio.h>
#define MAXL 5
char command[MAXL];

int main() {
	int stkTop_1 = 0;
	int stkTop_2 = 0;

	while (~scanf("%s", command)) {
		// push
		if (command[1] == 'u') {
			scanf("%*d");

			putchar('1');
			++stkTop_1;
		}

		// pop
		else /* if (command[1] == 'o') */ {
			// empty
			if (stkTop_2 == 0) {
				for (int k = 0; k < stkTop_1; ++k)
					putchar('5');

				stkTop_2 = stkTop_1 - 1;
				stkTop_1 = 0;

				putchar('4');
			}

			// not empty
			else {
				--stkTop_2;
				putchar('4');
			}
		}
	}

	putchar('\n');
	return 0;
}
