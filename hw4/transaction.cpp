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
#if DEBUG == 1
			std::cout << "!!!!!!!!!!!!\n";
			bdh.display(std::cout);
			std::cout << "!!!!!!!!!!!!\n";
#endif
			bdh.removeMinSell();
#if DEBUG == 1
			std::cout << "@@@@@@@@@@@@\n";
			bdh.display(std::cout);
			std::cout << "@@@@@@@@@@@@\n";
#endif
			bdh.removeMaxBuy();
#if DEBUG == 1
			std::cout << "############\n";
			bdh.display(std::cout);
			std::cout << "############\n";
#endif
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
#if DEBUG == 1
			bdh.display(std::cout);
#endif
		} else {
			contLoop = 0;
		}
	}


	return;
}
