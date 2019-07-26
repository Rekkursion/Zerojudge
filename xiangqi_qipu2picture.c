#pragma warning (disable:4996)

#include <stdio.h>
#include <string.h>
#define isuppercase(c) ((c) >= 65 && (c) <= 90)
#define islowercase(c) ((c) >= 97 && (c) <= 122)
#define abs(n) ((n) < 0 ? (-(n)) : (n))
#define BOARD_HEIGHT 10
#define BOARD_WIDTH 9
char line[BOARD_WIDTH + 1];
char board[BOARD_HEIGHT][BOARD_WIDTH + 1], lastBoard[BOARD_HEIGHT][BOARD_WIDTH + 1];
char wxf2hanzi[256][4];

void initialize();
void save2LastBoard();
void makePu(int, int);
int areTwoSameChessesAtTheSameRoad(int, int, char[][BOARD_WIDTH + 1], int);
int main() {
	initialize();

	int rowIdx = 0, first = 1, isRedsTurn = 1, turn = 0;
	while (~scanf("%s", line)) {
		if (line[0] == '#') {
			rowIdx = 0;

			if (first)
				first = 0;
			else
				makePu(isRedsTurn, turn),
				isRedsTurn = !isRedsTurn;

			if (isRedsTurn)
				++turn;

			save2LastBoard();
		}

		else
			strcpy(board[rowIdx], line),
			++rowIdx;
	}
	if (!isRedsTurn)
		putchar('\n');

	return 0;
}

void initialize() {
	strcpy(wxf2hanzi[1], "1");
	strcpy(wxf2hanzi[2], "2");
	strcpy(wxf2hanzi[3], "3");
	strcpy(wxf2hanzi[4], "4");
	strcpy(wxf2hanzi[5], "5");
	strcpy(wxf2hanzi[6], "6");
	strcpy(wxf2hanzi[7], "7");
	strcpy(wxf2hanzi[8], "8");
	strcpy(wxf2hanzi[9], "9");

	strcpy(wxf2hanzi['1'], "一");
	strcpy(wxf2hanzi['2'], "二");
	strcpy(wxf2hanzi['3'], "三");
	strcpy(wxf2hanzi['4'], "四");
	strcpy(wxf2hanzi['5'], "五");
	strcpy(wxf2hanzi['6'], "六");
	strcpy(wxf2hanzi['7'], "七");
	strcpy(wxf2hanzi['8'], "八");
	strcpy(wxf2hanzi['9'], "九");

	strcpy(wxf2hanzi['+'], "進");
	strcpy(wxf2hanzi['-'], "退");
	strcpy(wxf2hanzi['.'], "平");

	strcpy(wxf2hanzi['K'], "帥");
	strcpy(wxf2hanzi['k'], "將");

	strcpy(wxf2hanzi['A'], "仕");
	strcpy(wxf2hanzi['a'], "士");

	strcpy(wxf2hanzi['E'], "相");
	strcpy(wxf2hanzi['e'], "象");

	strcpy(wxf2hanzi['H'], "傌");
	strcpy(wxf2hanzi['h'], "馬");

	strcpy(wxf2hanzi['R'], "俥");
	strcpy(wxf2hanzi['r'], "車");

	strcpy(wxf2hanzi['C'], "炮");
	strcpy(wxf2hanzi['c'], "砲");

	strcpy(wxf2hanzi['P'], "兵");
	strcpy(wxf2hanzi['p'], "卒");

	return;
}

void save2LastBoard() {
	for (int k = 0; k < 10; ++k) {
		for (int j = 0; j < 9; ++j)
			lastBoard[k][j] = board[k][j];
		lastBoard[k][9] = '\0';
	}
	return;
}

void makePu(int isRedsTurn, int turn) {
	int y0 = 0, x0 = 0, y1 = 0, x1 = 0, first = 1;
	int ySrc, xSrc, yDst, xDst, atSameRoad;

	for (int k = 0; k < BOARD_HEIGHT; ++k) {
		for (int j = 0; j < BOARD_WIDTH; ++j) {
			if (board[k][j] != lastBoard[k][j]) {
				if (first)
					y0 = j, x0 = k, first = 0;
				else
					{ y1 = j, x1 = k; k = BOARD_HEIGHT; break; }
			}
		}
	}

	if (isRedsTurn) {
		if (isuppercase(lastBoard[x0][y0]))
			ySrc = 8 - y0, xSrc = x0, yDst = 8 - y1, xDst = x1;
		else
			ySrc = 8 - y1, xSrc = x1, yDst = 8 - y0, xDst = x0;
	} else {
		if (islowercase(lastBoard[x0][y0]))
			ySrc = y0, xSrc = x0, yDst = y1, xDst = x1;
		else
			ySrc = y1, xSrc = x1, yDst = y0, xDst = x0;
	}

	if (isRedsTurn)
		printf("%03d.", turn);

	atSameRoad = areTwoSameChessesAtTheSameRoad(xSrc, isRedsTurn ? 8 - ySrc : ySrc, lastBoard, isRedsTurn);
	if (atSameRoad != 0)
		printf(" %s%s", atSameRoad < 0 ? "後" : "前", wxf2hanzi[lastBoard[xSrc][isRedsTurn ? 8 - ySrc : ySrc]]);
	else
		printf(" %s%s", wxf2hanzi[lastBoard[xSrc][isRedsTurn ? 8 - ySrc : ySrc]], isRedsTurn ? wxf2hanzi[ySrc + 49] : wxf2hanzi[ySrc + 1]);

	// slash movement
	if (ySrc != yDst && xSrc != xDst) {
		if (isRedsTurn)
			printf("%s%s", xSrc > xDst ? "進" : "退", wxf2hanzi[yDst + 49]);
		else
			printf("%s%d\n", xSrc < xDst ? "進" : "退", yDst + 1);
	}
	// vertical movement
	else if (ySrc == yDst) {
		if (isRedsTurn)
			printf("%s%s", xSrc > xDst ? "進" : "退", wxf2hanzi[abs(xSrc - xDst) + 48]);
		else
			printf("%s%d\n", xSrc < xDst ? "進" : "退", abs(xSrc - xDst));
	}
	// horizontal movement
	else {
		if (isRedsTurn)
			printf("平%s", wxf2hanzi[yDst + 49]);
		else
			printf("平%d\n", yDst + 1);
	}

	return;
}

int areTwoSameChessesAtTheSameRoad(int y, int x, char pBoard[][BOARD_WIDTH + 1], int isRedsTurn) {
	char chess = pBoard[y][x];

	for (int r = 0; r < 10; ++r) {
		if (r == y)
			continue;
		if (pBoard[r][x] == pBoard[y][x])
			return isRedsTurn ? r - y : y - r;
	}

	return 0;
}