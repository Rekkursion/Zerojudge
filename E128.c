#pragma warning (disable:4996)

#include <stdio.h>
#include <math.h>

int main() {
	int sec;

	while (~scanf("%d", &sec) && sec) {
		int sec_sqrt = (int)ceil(sqrt((double)sec));
		int shed = (sec_sqrt * sec_sqrt) - (sec_sqrt - 1);
		int x = sec_sqrt, y = sec_sqrt;

		if (sec_sqrt & 1) {
			if (sec > shed)
				x -= sec - shed;
			else
				y -= shed - sec;
		} else {
			if (sec > shed)
				y -= sec - shed;
			else
				x -= shed - sec;
		}

		printf("%d %d\n", x, y);
	}

	return 0;
}
