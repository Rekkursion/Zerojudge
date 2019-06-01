#pragma warning (disable:4996)

#include <stdio.h>
#include <math.h>
#define MAXN 10

typedef struct pnode {
	double x, y;
}Point;
Point ptList[MAXN];

int main() {
	double area;
	int n;

	while (~scanf("%d", &n)) {
		// surveyor's formula
		area = 0.0;
		for (int k = 0; k < n; ++k) {
			scanf("%lf %lf", &ptList[k].x, &ptList[k].y);
			if (k > 0)
				area += ptList[k - 1].x * ptList[k].y,
				area -= ptList[k - 1].y * ptList[k].x;
		}
		area += ptList[n - 1].x * ptList[0].y;
		area -= ptList[n - 1].y * ptList[0].x;

		area = 0.5 * fabs(area);
		
		printf("%.2lf\n", area);
	}

	return 0;
}
