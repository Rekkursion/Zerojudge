#pragma warning (disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max(a, b) ((a) < (b) ? (b) : (a))
#define to_date_stamp(y, m) (((y) * 100) + (m))
#define next_date_stamp(d) ((d) % 100 == 12 ? (((d) / 100) * 100) + 101 : (d) + 1)
#define MAX_CITY_LEN 20
#define MAX_CITY_NUM 100
#define MAX_EVENT_LEN 6
#define MAX_RECORD_NUM 100
//#define DEBUG
typedef long long ll;

int initYear, initMonth, initDateStamp;
int lastYear, lastMonth, lastDateStamp;
ll X, Y;
ll grossProperty;

typedef struct cnode {
	ll monthlyIncome;
	int cityNo;
	char cityName[MAX_CITY_LEN + 1];
}CityNode;
CityNode cityList[MAX_CITY_NUM];
int cityNum;

typedef struct rnode {
	int dateStamp;
	int year, month;
	char cityName[MAX_CITY_LEN + 1];
	char _event[MAX_EVENT_LEN + 1];
}RecordNode;
RecordNode recordList[MAX_RECORD_NUM];
int recordNum;

inline void getInputData();
inline void getCities();
inline void getRecords();
inline void stringToInt(char*, int*, int*);
inline void solve();
inline void outputData();
inline void updateGrossProperty();
inline int findCityIndexByCityName(char*);
int cmp_byDateStamp(const void*, const void*);
int cmp_byMonthlyIncome(const void*, const void*);
int main() {
	getInputData();
	solve();
	outputData();

	return 0;
}

void getInputData() {
	scanf("%d%*c%d %lld", &initYear, &initMonth, &grossProperty);
	initDateStamp = to_date_stamp(initYear, initMonth);

	getCities();
	getRecords();

	scanf("%d%*c%d", &lastYear, &lastMonth);
	lastDateStamp = to_date_stamp(lastYear, lastMonth);

#ifdef DEBUG
	printf("%d/%d = %d, %llu\n", initYear, initMonth, initDateStamp, grossProperty);
	for (int k = 0; k < cityNum; ++k)
		printf("|%s|%llu|\n", cityList[k].cityName, cityList[k].monthlyIncome);
	for (int k = 0; k < recordNum; ++k)
		printf("|%d/%d=%d|%s|%s|\n", recordList[k].year, recordList[k].month, recordList[k].dateStamp, recordList[k].cityName, recordList[k]._event);
	printf("%d/%d = %d\n", lastYear, lastMonth, lastDateStamp);
#endif

	return;
}

void getCities() {
	char newCityName[MAX_CITY_LEN + 1];
	ll newMonthlyIncome;

	cityNum = 0;
	while (scanf("%s", newCityName) && newCityName[0] != '-') {
		scanf("%lld", &newMonthlyIncome);

		cityList[cityNum].monthlyIncome = newMonthlyIncome;
		cityList[cityNum].cityNo = cityNum;
		strcpy(cityList[cityNum++].cityName, newCityName);
	}

	return;
}

void getRecords() {
	scanf("%lld %lld", &X, &Y);

	char dateStr[8];
	char newCityName[MAX_CITY_LEN + 1], newEvent[MAX_EVENT_LEN + 1];
	int newYear, newMonth, newDateStamp;

	recordNum = 0;
	while (scanf("%s", dateStr) && dateStr[0] != '-') {
		scanf("%s %s", newCityName, newEvent);
		stringToInt(dateStr, &newYear, &newMonth);

		newDateStamp = to_date_stamp(newYear, newMonth);

		recordList[recordNum].year = newYear;
		recordList[recordNum].month = newMonth;
		recordList[recordNum].dateStamp = newDateStamp;
		strcpy(recordList[recordNum].cityName, newCityName);
		strcpy(recordList[recordNum++]._event, newEvent);
	}
	qsort(recordList, recordNum, sizeof(RecordNode), cmp_byDateStamp);

	return;
}

void stringToInt(char* str, int* year, int* month) {
	int len = strlen(str);
	int idx = 0;

	*year = 0;
	for (; str[idx] != '/'; ++idx)
		*year = (*year * 10) + (str[idx] - 48);

	*month = 0;
	for (++idx; idx < len; ++idx)
		*month = (*month * 10) + (str[idx] - 48);

	return;
}

void solve() {
	int currentDateStamp;
	int recIdx = 0;

	for (currentDateStamp = next_date_stamp(initDateStamp); currentDateStamp <= lastDateStamp; currentDateStamp = next_date_stamp(currentDateStamp)) {
		updateGrossProperty();

		while (recIdx < recordNum && recordList[recIdx].dateStamp == currentDateStamp) {
			int cityIdx = findCityIndexByCityName(recordList[recIdx].cityName);

			// BUILT
			if (recordList[recIdx]._event[3] == 'L')
				cityList[cityIdx].monthlyIncome += X;
			// BOOST
			else if (recordList[recIdx]._event[3] == 'S')
				cityList[cityIdx].monthlyIncome += X * X;
			// DAMAGE
			else if (recordList[recIdx]._event[3] == 'A')
				cityList[cityIdx].monthlyIncome = max(0, cityList[cityIdx].monthlyIncome - Y);
			// RUIN
			else /* if (recordList[recIdx]._event[3] == 'N') */
				cityList[cityIdx].monthlyIncome = 0;

			++recIdx;
		}
	}
	qsort(cityList, cityNum, sizeof(CityNode), cmp_byMonthlyIncome);

	return;
}

void outputData() {
	printf("%04d/%02d %lld\n", lastYear, lastMonth, grossProperty);
	for (int k = 0; k < cityNum; ++k)
		printf("%s %lld\n", cityList[k].cityName, cityList[k].monthlyIncome);
	return;
}

void updateGrossProperty() {
	for (int k = 0; k < cityNum; ++k)
		grossProperty += cityList[k].monthlyIncome;
	return;
}

int findCityIndexByCityName(char* pCityName) {
	for (int k = 0; k < cityNum; ++k) {
		if (!strcmp(cityList[k].cityName, pCityName))
			return k;
	}

	return -1;
}

int cmp_byDateStamp(const void* a, const void* b) {
	RecordNode* ra = (RecordNode*)a;
	RecordNode* rb = (RecordNode*)b;

	return ra->dateStamp - rb->dateStamp;
}

int cmp_byMonthlyIncome(const void* a, const void* b) {
	CityNode* ca = (CityNode*)a;
	CityNode* cb = (CityNode*)b;

	if (ca->monthlyIncome != cb->monthlyIncome)
		return ca->monthlyIncome - cb->monthlyIncome;
	return ca->cityNo - cb->cityNo;
}
