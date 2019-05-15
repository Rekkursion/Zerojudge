#pragma warning (disable:4996)

#include <stdio.h>
#include <string.h>
#define MAXL 12
char inpStr[MAXL];

int main() {
	int hex, r, g, b;
	while (~scanf("%s", inpStr)) {

		// hex to rgb
		if (inpStr[0] == '#') {
			sscanf(inpStr, "%*c%x", &hex);
			b = hex % (16 * 16);
			g = (hex / (16 * 16)) % (16 * 16);
			r = (hex / (16 * 16) / (16 * 16)) % (16 * 16);

			printf("%d %d %d\n", r, g, b);
		}

		// rgb to hex
		else {
			sscanf(inpStr, "%d", &r);
			scanf("%d %d", &g, &b);

			printf("#%02X%02X%02X\n", r, g, b);
		}
	}

	return 0;
}
