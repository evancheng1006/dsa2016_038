#include "trans.h"
#include "bid.h"
#include "bidheap.h"

#include <vector>

void transaction(BidHeap & bdh, std::vector<struct trans> & result) {
	result.clear();
	int contLoop = 1;
	while (!bdh.emptySell() && !bdh.emptyBuy() && contLoop) {
		if (bdh.minSell().price <= bdh.maxBuy().price) {
			struct trans tmpTrans;

			struct bid bdMin = bdh.minSell();
			struct bid bdMax = bdh.maxBuy();
			bdh.removeMinSell();
			bdh.removeMaxBuy();
			tmpTrans.transId = bdh.finishedTrans;
			bdh.finishedTrans++;
			tmpTrans.buyClientId = bdMax.clientId;
			tmpTrans.sellClientId = bdMin.clientId;
			tmpTrans.transPrice = bdMin.price; //seller's price
			tmpTrans.transShareCount = ((bdMin.shareCount < bdMax.shareCount) ? bdMin.shareCount : bdMax.shareCount);
			bdMin.shareCount -= tmpTrans.transShareCount;
			bdMax.shareCount -= tmpTrans.transShareCount;
			if (bdMin.shareCount != 0) {
				bdh.insert(bdMin);
			}
			if (bdMax.shareCount != 0) {
				bdh.insert(bdMax);
			}

			result.push_back(tmpTrans);
		} else {
			contLoop = 0;
		}
	}


	return;
}
