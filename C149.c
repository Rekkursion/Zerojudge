#pragma warning (disable:4996)

#include <stdio.h>
#include <string.h>
#define MAX_SIZE 55
#define MAX_LEN 303
char map[MAX_SIZE + 1][MAX_SIZE + 2];
char plan[MAX_LEN + 1];
int directions[8][2] = { {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1} };
char directionSymbols[8][3] = { "N", "NE", "E", "SE", "S", "SW", "W", "NW" };
int failedSituation[MAX_SIZE * MAX_SIZE * 10];

int move(int*, int*, const int, const int, const int);
int main() {
	int R, C;
	scanf("%d %d", &R, &C);
	for (int r = 0; r < R; ++r)
		scanf("%s", map[r]);

	int x, y, dirIdx, planLen, moveResult, finished = 0, breaked;
	char dir[3];

	while (~scanf("%d %d %s %s", &x, &y, dir, plan)) {
		// already arrived at teleport
		if (finished) {
			puts("I think I don\'t need to move anymore.");
			continue;
		}

		// initialize the direction index
		if (strlen(dir) == 1) {
			if (dir[0] == 'N') dirIdx = 0;
			else if (dir[0] == 'E') dirIdx = 2;
			else if (dir[0] == 'S') dirIdx = 4;
			else dirIdx = 6;
		} else {
			if (dir[0] == 'N' && dir[1] == 'E') dirIdx = 1;
			else if (dir[0] == 'S' && dir[1] == 'E') dirIdx = 3;
			else if (dir[0] == 'S' && dir[1] == 'W') dirIdx = 5;
			else dirIdx = 7;
		}

		planLen = strlen(plan);
		--x; --y;
		breaked = 0;

		for (int k = 0; k < planLen; ++k) {
			// M: move
			if (plan[k] == 'M') {
				moveResult = move(&x, &y, dirIdx, R, C);

				// fall out of map
				if (moveResult == 0) {
					int failedIdx = (((x * 50) + y) * 10) + dirIdx;

					// has not happened this failing situation
					if (!failedSituation[failedIdx]) {
						failedSituation[failedIdx] = 1;
						breaked = 1;
						printf("%d %d %s BAD PLAN!\n", x + 1, y + 1, directionSymbols[dirIdx]);
						break;
					}
				}

				// arrive at teleport
				else if (moveResult == 2) {
					finished = 1;
					breaked = 1;
					printf("%d %d FINISHED!\n", x + 1, y + 1);
					break;
				}
			}

			// R: turn right, L: turn left
			else {
				char r_or_l = plan[k];
				int angle = 0;

				++k;
				while (k < planLen && plan[k] >= 48 && plan[k] <= 57)
					angle = (angle * 10) + (plan[k] - 48), ++k;
				--k;

				angle /= 45;
				angle = dirIdx + (r_or_l == 'R' ? angle : (-angle));
				if (angle < 0) angle += 8;
				if (angle >= 8) angle -= 8;
				dirIdx = angle;
			}
		}
		
		// no fall out and no finished
		if (!breaked)
			printf("%d %d %s\n", x + 1, y + 1, directionSymbols[dirIdx]);
	}

	return 0;
}

int move(int* x, int* y, const int DIR_IDX, const int R, const int C) {
	int newLocationX = (*x) + directions[DIR_IDX][0];
	int newLocationY = (*y) + directions[DIR_IDX][1];

	// fall out of map
	if (newLocationX < 0 || newLocationX >= C ||
		newLocationY < 0 || newLocationY >= R ||
		map[newLocationY][newLocationX] == 'H') {

		return 0;
	}

	// re-assign location
	(*x) = newLocationX; (*y) = newLocationY;

	// arrive at teleport
	if (map[newLocationY][newLocationX] == 'T')
		return 2;

	// general case
	return 1;
}
