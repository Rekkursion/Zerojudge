//#pragma warning (disable:4996)
//
//// The source files come from WXF (World Xiangqi Federation) format
//
//#include <stdio.h>
//#include <string.h>
//#define islowercase(c) ((c) >= 97 && (c) <= 122)
//#define isuppercase(c) ((c) >= 65 && (c) <= 90)
//#define isnumberchr(c) ((c) >= 48 && (c) <= 57)
//#define abs(n) ((n) < 0 ? (-(n)) : (n))
//#define MAXL 202
//#define PROBLEM_NO "c422"
//char inpFilename[MAXL], outpFilename[MAXL], inpStr[MAXL];
//char board[10][10];
//
//void initializeBoard();
//void setBoard(int, int, char, int, int, char);
//void printBoard(FILE*);
//int findRoad(char);
//int findY_byRoad(char, int);
//int findY_byRoadAndOrder(char, int, char, int);
//int is_horse_or_advisor_or_elephant(char);
//int main() {
//	initializeBoard();
//
//	int len, start, fileIdx = 0, road, y, isRedsTurn, dstRoad, dstY, dis;
//	FILE* fin, * fout;
//
//	while (~scanf("%s", inpFilename)) {
//		if (!(fin = fopen(inpFilename, "r")))
//		{
//			puts("file not found"); continue;
//		}
//
//		isRedsTurn = 1;
//		start = 0;
//		sprintf(outpFilename, "%s_%02d.in", PROBLEM_NO, fileIdx++);
//		fout = fopen(outpFilename, "w");
//
//		while (~fscanf(fin, "%s", inpStr)) {
//			if (inpStr[0] == '}')
//				break;
//
//			len = strlen(inpStr);
//			if (!start && inpStr[len - 1] == '.')
//				start = 1,
//				printBoard(fout);
//
//			if (start)
//				if (inpStr[len - 1] == '.');
//				else {
//					if (isnumberchr(inpStr[1])) {
//						road = isuppercase(inpStr[0]) ? 8 - (inpStr[1] - 49) : inpStr[1] - 49;
//						y = findY_byRoad(inpStr[0], road);
//					}
//					else {
//						road = findRoad(inpStr[0]);
//						y = findY_byRoadAndOrder(inpStr[0], road, inpStr[1], isRedsTurn);
//					}
//
//					if (inpStr[2] == '+') {
//						if (is_horse_or_advisor_or_elephant(board[y][road])) {
//							dstRoad = isuppercase(inpStr[0]) ? 8 - (inpStr[3] - 49) : inpStr[3] - 49;
//							switch (board[y][road]) {
//							case 'A': dstY = y - 1; break;
//							case 'a': dstY = y + 1; break;
//							case 'E': dstY = y - 2; break;
//							case 'e': dstY = y + 2; break;
//							case 'H': dstY = abs(road - dstRoad) == 2 ? y - 1 : y - 2; break;
//							case 'h': dstY = abs(road - dstRoad) == 2 ? y + 1 : y + 2; break;
//							}
//						}
//						else {
//							dis = inpStr[3] - 48;
//							dstRoad = road;
//							dstY = isuppercase(inpStr[0]) ? y - dis : y + dis;
//						}
//					}
//					else if (inpStr[2] == '-') {
//						if (is_horse_or_advisor_or_elephant(board[y][road])) {
//							dstRoad = isuppercase(inpStr[0]) ? 8 - (inpStr[3] - 49) : inpStr[3] - 49;
//							switch (board[y][road]) {
//							case 'A': dstY = y + 1; break;
//							case 'a': dstY = y - 1; break;
//							case 'E': dstY = y + 2; break;
//							case 'e': dstY = y - 2; break;
//							case 'H': dstY = abs(road - dstRoad) == 2 ? y + 1 : y + 2; break;
//							case 'h': dstY = abs(road - dstRoad) == 2 ? y - 1 : y - 2; break;
//							}
//						}
//						else {
//							dis = inpStr[3] - 48;
//							dstRoad = road;
//							dstY = isuppercase(inpStr[0]) ? y + dis : y - dis;
//						}
//					}
//					else /* if (inpStr[2] == '.') */ {
//						dstY = y;
//						dstRoad = isuppercase(inpStr[0]) ? 8 - (inpStr[3] - 49) : inpStr[3] - 49;
//					}
//
//					setBoard(y, road, '.', dstY, dstRoad, board[y][road]);
//					putc('\n', fout), printBoard(fout);
//
//					isRedsTurn = !isRedsTurn;
//				}
//		}
//
//		fclose(fin), fclose(fout);
//		puts("done");
//	}
//
//	return 0;
//}
//
//void initializeBoard() {
//	for (int k = 0; k < 10; ++k) {
//		for (int j = 0; j < 9; ++j)
//			board[k][j] = '.';
//		board[k][9] = '\0';
//	}
//
//	board[0][0] = board[0][8] = 'r';
//	board[0][1] = board[0][7] = 'h';
//	board[0][2] = board[0][6] = 'e';
//	board[0][3] = board[0][5] = 'a';
//	board[0][4] = 'k';
//	board[2][1] = board[2][7] = 'c';
//	board[3][0] = board[3][2] = board[3][4] = board[3][6] = board[3][8] = 'p';
//
//	board[9][0] = board[9][8] = 'R';
//	board[9][1] = board[9][7] = 'H';
//	board[9][2] = board[9][6] = 'E';
//	board[9][3] = board[9][5] = 'A';
//	board[9][4] = 'K';
//	board[7][1] = board[7][7] = 'C';
//	board[6][0] = board[6][2] = board[6][4] = board[6][6] = board[6][8] = 'P';
//
//	return;
//}
//
//void setBoard(int y0, int x0, char newCh0, int y1, int x1, char newCh1) {
//	board[y0][x0] = newCh0, board[y1][x1] = newCh1;
//	return;
//}
//
//void printBoard(FILE * fp) {
//	for (int k = 0; k < 10; ++k)
//		fprintf(fp, "%s\n", board[k]);
//	putc('#', fp);
//
//	return;
//}
//
//int findRoad(char chess) {
//	for (int k = 0; k < 10; ++k) {
//		for (int j = 0; j < 9; ++j) {
//			if (board[k][j] == chess)
//				return j;
//		}
//	}
//
//	return -1;
//}
//
//int findY_byRoad(char chess, int road) {
//	for (int k = 0; k < 10; ++k) {
//		if (board[k][road] == chess)
//			return k;
//	}
//
//	return -1;
//}
//
//int findY_byRoadAndOrder(char chess, int road, char order, int isRedsTurn) {
//	if ((isRedsTurn && order == '+') || (!isRedsTurn && order == '-')) {
//		for (int k = 0; k < 10; ++k) {
//			if (board[k][road] == chess)
//				return k;
//		}
//	}
//	else {
//		for (int k = 9; k >= 0; --k) {
//			if (board[k][road] == chess)
//				return k;
//		}
//	}
//
//	return -1;
//}
//
//int is_horse_or_advisor_or_elephant(char chess) {
//	return
//		chess == 'H' || chess == 'h' ||
//		chess == 'A' || chess == 'a' ||
//		chess == 'E' || chess == 'e';
//}