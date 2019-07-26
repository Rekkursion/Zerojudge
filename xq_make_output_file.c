//#pragma warning (disable:4996)
//
//// The source files come from WXF (World Xiangqi Federation) format
//
//#include <stdio.h>
//#include <string.h>
//#define islowercase(c) ((c) >= 97 && (c) <= 122)
//#define isuppercase(c) ((c) >= 65 && (c) <= 90)
//#define MAXL 202
//#define PROBLEM_NO "c422"
//char inpFilename[MAXL], outpFilename[MAXL], inpStr[MAXL];
//char wxf2hanzi[256][4];
//
//void initialize();
//int main() {
//	initialize();
//
//	int len, start, huihe, fileIdx = 0, isTurnOfBlack;
//	FILE* fin, * fout;
//
//	while (~scanf("%s", inpFilename)) {
//		if (!(fin = fopen(inpFilename, "r")))
//		{
//			puts("file not found"); continue;
//		}
//
//		start = isTurnOfBlack = 0;
//		sprintf(outpFilename, "%s_%02d.out", PROBLEM_NO, fileIdx++);
//		fout = fopen(outpFilename, "w");
//
//		while (~fscanf(fin, "%s", inpStr)) {
//			if (inpStr[0] == '}')
//				break;
//
//			len = strlen(inpStr);
//			if (inpStr[len - 1] == '.')
//				start = 1;
//
//			if (start)
//				if (inpStr[len - 1] == '.')
//					sscanf(inpStr, "%d.", &huihe),
//					fprintf(fout, "%03d. ", huihe);
//				else {
//					if (inpStr[1] == '+')
//						fprintf(fout, "前%s", wxf2hanzi[inpStr[0]]);
//					else if (inpStr[1] == '-')
//						fprintf(fout, "後%s", wxf2hanzi[inpStr[0]]);
//					else
//						if (isuppercase(inpStr[0]))
//							fprintf(fout, "%s%s", wxf2hanzi[inpStr[0]], wxf2hanzi[inpStr[1]]);
//						else
//							fprintf(fout, "%s%c", wxf2hanzi[inpStr[0]], inpStr[1]);
//
//					if (isuppercase(inpStr[0]))
//						fprintf(fout, "%s%s", wxf2hanzi[inpStr[2]], wxf2hanzi[inpStr[3]]);
//					else
//						fprintf(fout, "%s%c", wxf2hanzi[inpStr[2]], inpStr[3]);
//
//					fprintf(fout, "%s", isTurnOfBlack ? "\n" : " ");
//
//					isTurnOfBlack = !isTurnOfBlack;
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
//void initialize() {
//	strcpy(wxf2hanzi['1'], "一");
//	strcpy(wxf2hanzi['2'], "二");
//	strcpy(wxf2hanzi['3'], "三");
//	strcpy(wxf2hanzi['4'], "四");
//	strcpy(wxf2hanzi['5'], "五");
//	strcpy(wxf2hanzi['6'], "六");
//	strcpy(wxf2hanzi['7'], "七");
//	strcpy(wxf2hanzi['8'], "八");
//	strcpy(wxf2hanzi['9'], "九");
//
//	strcpy(wxf2hanzi['+'], "進");
//	strcpy(wxf2hanzi['-'], "退");
//	strcpy(wxf2hanzi['.'], "平");
//
//	strcpy(wxf2hanzi['K'], "帥");
//	strcpy(wxf2hanzi['k'], "將");
//
//	strcpy(wxf2hanzi['A'], "仕");
//	strcpy(wxf2hanzi['a'], "士");
//
//	strcpy(wxf2hanzi['E'], "相");
//	strcpy(wxf2hanzi['e'], "象");
//
//	strcpy(wxf2hanzi['H'], "傌");
//	strcpy(wxf2hanzi['h'], "馬");
//
//	strcpy(wxf2hanzi['R'], "俥");
//	strcpy(wxf2hanzi['r'], "車");
//
//	strcpy(wxf2hanzi['C'], "炮");
//	strcpy(wxf2hanzi['c'], "砲");
//
//	strcpy(wxf2hanzi['P'], "兵");
//	strcpy(wxf2hanzi['p'], "卒");
//
//	return;
//}