#pragma warning (disable:4996)

#include <stdio.h>
#include <math.h>
#define IS_ZERO(a) ((a) < 1e-3)

typedef struct pnode {
	double x, y;
}Point;

inline Point getMiddlePoint(Point, Point);
inline double getDistance(Point, Point);
int main() {
	Point fstStartPoint, fstEndPoint;
	Point secStartPoint, secEndPoint;
	Point midPtBetweenStartPts, midPtBetweenEndPts;
	int move_x, move_y;
	double zoomRate, m1, m2, spinAngle;

	while (~scanf("%lf %lf %lf %lf %lf %lf %lf %lf", &fstStartPoint.x, &fstStartPoint.y, &fstEndPoint.x, &fstEndPoint.y, &secStartPoint.x, &secStartPoint.y, &secEndPoint.x, &secEndPoint.y) && (fstStartPoint.x || fstStartPoint.y || fstEndPoint.x || fstEndPoint.y || secStartPoint.x || secStartPoint.y || secEndPoint.x || secEndPoint.y)) {
		// calculate relative moves of x and y
		midPtBetweenStartPts = getMiddlePoint(fstStartPoint, secStartPoint);
		midPtBetweenEndPts = getMiddlePoint(fstEndPoint, secEndPoint);
		move_x = (int)(midPtBetweenEndPts.x - midPtBetweenStartPts.x);
		move_y = (int)(midPtBetweenEndPts.y - midPtBetweenStartPts.y);

		// calculate zoom rate
		zoomRate = getDistance(fstEndPoint, secEndPoint) / getDistance(fstStartPoint, secStartPoint);

		// calculate spin angle
		m1 = (fstStartPoint.y - secStartPoint.y) / (fstStartPoint.x - secStartPoint.x);
		m2 = (fstEndPoint.y - secEndPoint.y) / (fstEndPoint.x - secEndPoint.x);
		spinAngle = atan((m2 - m1) / (1 + m1 * m2));
		if (IS_ZERO(fabs(spinAngle)))
			spinAngle = 0.0;

		printf("%d %d %.3lf %.3lf\n", move_x, move_y, zoomRate, spinAngle);

	}

	return 0;
}

inline Point getMiddlePoint(Point p1, Point p2) {
	Point ret;
	ret.x = (p1.x + p2.x) / 2.0;
	ret.y = (p1.y + p2.y) / 2.0;
	return ret;
}

inline double getDistance(Point p1, Point p2) {
	return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}
