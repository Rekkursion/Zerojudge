#pragma warning (disable:4996)

#include <stdio.h>
#include <stdlib.h>
#define MAXN 10005

typedef struct point {
	int x, y;
}Point;
Point points[MAXN];

int cmp(const void*, const void*);
int main() {
	int n;

	while (~scanf("%d", &n) && n) {
		for (int k = 0; k < n; ++k)
			scanf("%d %d", &points[k].x, &points[k].y);

		qsort(points, n, sizeof(Point), cmp);

		int centerX_doubled = points[0].x + points[n - 1].x;
		int centerY_doubled = points[0].y + points[n - 1].y;
		int hasCenter = 1;

		for (int k = 1; k < n - 1; ++k) {
			if (points[k].x + points[n - 1 - k].x != centerX_doubled ||
				points[k].y + points[n - 1 - k].y != centerY_doubled) {
				hasCenter = 0;
				break;
			}
		}

		puts(hasCenter ? "yes" : "no");
	}

	return 0;
}

int cmp(const void* a, const void* b) {
	Point* pa = (Point*)a;
	Point* pb = (Point*)b;

	if (pa->x != pb->x)
		return pa->x - pb->x;
	return pa->y - pb->y;
}
