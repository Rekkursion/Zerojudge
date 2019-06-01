#pragma warning (disable:4996)

#include <stdio.h>
#include <math.h>
#define RAID_0 0
#define RAID_1 1
#define RAID_5 5
#define DISK_NUM 4
#define MAX_DISK_CAN_USE_NUM 8
#define INF 2147483647

typedef struct dnode {
	int size;
	int price;
}Disk;
Disk diskList[DISK_NUM];

int main() {
	int needSize, raidLevel, cheapestPrice, cheapestIdx, qty, minQty;

	diskList[0].size = 250, diskList[0].price = 75;
	diskList[1].size = 400, diskList[1].price = 110;
	diskList[2].size = 500, diskList[2].price = 140;
	diskList[3].size = 750, diskList[3].price = 250;

	while (~scanf("%d %d", &needSize, &raidLevel)) {
		if (raidLevel == RAID_1)
			needSize <<= 1;

		cheapestPrice = INF;
		qty = INF;
		minQty = INF;

		for (int d = 0; d < DISK_NUM; ++d) {
			qty = (int)ceil((double)(needSize + (raidLevel == RAID_5 ? diskList[d].size : 0)) / (double)diskList[d].size);
			if (qty > MAX_DISK_CAN_USE_NUM)
				continue;
			if (raidLevel == RAID_1 && (qty & 1))
				continue;

			if (qty * diskList[d].price < cheapestPrice)
				cheapestIdx = d,
				cheapestPrice = qty * diskList[d].price,
				minQty = qty;
		}

		printf("Qty: %d Disk: %dGB Price: $%d\n", minQty, diskList[cheapestIdx].size, diskList[cheapestIdx].price);
		printf("Total price of this %dGB array: $%d\n\n", ((minQty * diskList[cheapestIdx].size) >> (raidLevel == RAID_1 ? 1 : 0)) - (raidLevel == RAID_5 ? diskList[cheapestIdx].size : 0), cheapestPrice);
	}

	return 0;
}
