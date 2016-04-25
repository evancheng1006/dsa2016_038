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
		bdh.insert(tmpBid);
		transaction(bdh, tmpTrans);
		for (unsigned int i = 0; i < tmpTrans.size(); i++) {
			std::cout << tmpTrans[i] << "\n";
		}
	}
//	bdh.display(std::cout);
	return 0;
}

