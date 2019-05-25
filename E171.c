#pragma warning (disable:4996)

#include <stdio.h>
#define MAXN 10000
#define max(a, b) ((a) < (b) ? (b) : (a))
#define min(a, b) ((a) < (b) ? (a) : (b))
//#define QQ

int group[MAXN << 1];
int possibleMax[MAXN << 1];
int haveTickets[MAXN];
int doesntHaveTickets[MAXN];

static inline int readNonNegativeInt(int* const);
static inline void printNonNegativeInt(const int* const);
int main() {
	int n;
	while (readNonNegativeInt(&n) && n) {
		int haveTicketLen = 0;
		int doesntHaveTicketLen = 0;
		int p, last_p = 0, first_p = 0;
		int extra;
		int h = 0, d = 0, pm = 0;
		int maxGroupSize = 0;

		// get inputs
		for (int k = 0; k <= n; ++k) {
			if (k < n) {
				readNonNegativeInt(&p);
				if (k == 0)
					first_p = p;

				if (p)
					++haveTicketLen, p = 1;
				else
					++doesntHaveTicketLen;
			}

			if (k == n || (k > 0 && last_p != p)) {
				if (last_p) {
					haveTickets[h++] = haveTicketLen;
					maxGroupSize = max(maxGroupSize, haveTicketLen);
					haveTicketLen = 0;
				}
				else {
					doesntHaveTickets[d++] = doesntHaveTicketLen;
					doesntHaveTicketLen = 0;
				}
			}

			last_p = p;
		}
		readNonNegativeInt(&extra);

		// make sure that the first element in group is represented for have-ticket-people
		if (!first_p)
			group[pm++] = 0;

		// build group array
		for (int k = 0; k < max(h, d); ++k) {
			if (first_p) {
				if (k < h)
					group[pm++] = haveTickets[k];
				if (k < d)
					group[pm++] = doesntHaveTickets[k];
			} else {
				if (k < d)
					group[pm++] = doesntHaveTickets[k];
				if (k < h)
					group[pm++] = haveTickets[k];
			}
		}

		// make sure that the last element in group is represented for have-ticket-people
		if (!last_p)
			group[pm++] = 0;

		// build possible max array
		possibleMax[0] = group[0];
		for (int k = 1; k < pm; ++k)
			possibleMax[k] = possibleMax[k - 1] + group[k];

#ifdef QQ
		puts("have tickets");
		for (int k = 0; k < h; ++k)
			printf("%d, ", haveTickets[k]);
		puts("");
		puts("doesnt have tickets");
		for (int k = 0; k < d; ++k)
			printf("%d, ", doesntHaveTickets[k]);
		puts("");
		puts("group");
		for (int k = 0; k < pm; ++k)
			printf("%d, ", group[k]);
		puts("");
		puts("possible max");
		for (int k = 0; k < pm; ++k)
			printf("%d, ", possibleMax[k]);
		puts("");
#endif

		// find the max group size
		for (int k = 1; k < pm; k += 2) {
			int remain = extra;
			int g = k;

			while (g < pm && remain >= group[g]) {
				remain -= group[g];
				g += 2;
			}

			int maxPossibleGroupSize = possibleMax[g - 1] - (k == 1 ? 0 : possibleMax[k - 2]);
			if (g < pm)
				maxPossibleGroupSize += remain;
			if (g >= pm && k > 1)
				maxPossibleGroupSize += min(remain, group[k - 2]);

			maxGroupSize = max(maxGroupSize, maxPossibleGroupSize);
		}

		printNonNegativeInt(&maxGroupSize), putchar('\n');
	}

	return 0;
}

static inline int readNonNegativeInt(int* const integer) {
	static char ch;
	while ((ch = getchar()) < 48 || ch > 57);

	if (ch < 48 || ch > 57)
		return 0;

	(*integer) = ch - 48;
	while ((ch = getchar()) >= 48 && ch <= 57)
		(*integer) = ((*integer) * 10) + (ch - 48);

	return 1;
}

static inline void printNonNegativeInt(const int* const integer) {
	if (*integer == 0) {
		putchar('0');
		return;
	}

	static char str[22];
	static int idx;
	static int number;

	number = *integer;
	idx = 0;

	while (number > 0) {
		str[idx++] = number % 10;
		number /= 10;
	}

	while (idx)
		putchar(str[--idx] + 48);

	return;
}
