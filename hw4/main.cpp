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
//	int helppause;

	while (std::cin >> tmpBid) {
		bdh.insert(tmpBid);
//		std::cout << "after insert\n";bdh.display(std::cout);std::cin >> helppause;
		transaction(bdh, tmpTrans);
//		std::cout << "after transaction\n";bdh.display(std::cout);std::cin >> helppause;
		for (unsigned int i = 0; i < tmpTrans.size(); i++) {
			std::cout << tmpTrans[i] << "\n";
		}
	}
//	bdh.display(std::cout);
	return 0;
}

