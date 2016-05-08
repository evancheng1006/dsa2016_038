#include <iostream>
#include <vector>

#include "bid.h"
#include "trans.h"

#include "bidheap.h"
#include "minheap.h"

extern void transaction(BidHeap & bdh, std::vector<struct trans> & result);
int main() {
	struct bid tmpBid;
	std::vector<struct trans> tmpTrans;
	BidHeap bdh;

	while (std::cin >> tmpBid) {
#if DEBUG == 2
		std::cout << "input :" << tmpBid << "\n";
		if (!bdh.structureCheck()) {
			std::cout << "structure fail\n";
		}
#endif
#if DEBUG == 1
		std::cout << "input :" << tmpBid << "\n";
#endif
		bdh.insert(tmpBid);
#if DEBUG == 1
		std::cout << "after insert\n";bdh.display(std::cout);
#endif
		transaction(bdh, tmpTrans);
#if DEBUG == 1
		std::cout << "after transaction\n";bdh.display(std::cout);
#endif
		for (unsigned int i = 0; i < tmpTrans.size(); i++) {
			std::cout << tmpTrans[i] << "\n";
		}
	}
	return 0;
}

