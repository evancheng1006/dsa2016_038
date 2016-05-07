#ifndef BIDHEAP_H
#define BIDHEAP_H

#include <vector>
#include <map>

#include "bid.h"

class BidHeap {
private:
	std::map<int, int> sellHeapIndex;
	std::map<int, int> buyHeapIndex;
	inline void removeSellByHeapIndex(unsigned int index);
	inline void removeSellByBidId(int bidId);
	inline void removeBuyByHeapIndex(unsigned int index);
	inline void removeBuyByBidId(int bidId);

	inline unsigned int sizeSell();
	inline unsigned int sizeBuy();
	inline void insertSell(const struct bid & obj);
	inline void insertBuy(const struct bid & obj);
public:
	int finishedTrans;
	std::vector<struct bid> sell;
	std::vector<struct bid> buy;
	inline BidHeap();
	inline ~BidHeap();

	inline bool emptySell();
	inline bool emptyBuy();
	inline void insert(const struct bid & obj);

	inline struct bid minSell();
	inline struct bid maxBuy();
	inline void removeMinSell();
	inline void removeMaxBuy();

	inline void removeByBidId(int bidId);
	inline void display(std::ostream & output);

	inline int whereIs(int bidId);
};

inline BidHeap::BidHeap() {
	finishedTrans = 0;
	sell.resize(1);
	buy.resize(1);
	sellHeapIndex.clear();
	buyHeapIndex.clear();
}

inline BidHeap::~BidHeap() {
	// do nothing
}

inline unsigned int BidHeap::sizeSell() {
	return (sell.size() - 1);
}
inline bool BidHeap::emptySell() {
	if (sell.size() <= 1) {
		return true;
	}
	return false;
}
inline unsigned int BidHeap::sizeBuy() {
	return (buy.size() - 1);
}
inline bool BidHeap::emptyBuy() {
	if (buy.size() <= 1) {
		return true;
	}
	return false;
}

inline void BidHeap::insertSell(const struct bid & obj) {
	unsigned int curr = sell.size();

	sell.push_back(obj);

	sellHeapIndex[obj.bidId] = curr;

	while (curr > 1) {
		if (sell[curr] < sell[curr/2]) {
			sellHeapIndex[sell[curr/2].bidId] = curr;
			sellHeapIndex[sell[curr].bidId] = curr/2;
			struct bid tmp = sell[curr/2];
			sell[curr/2] = sell[curr];
			sell[curr] = tmp;
			curr /= 2;
		} else {
			curr = 1;
		}
	}
	return;
}
inline void BidHeap::insertBuy(const struct bid & obj) {
	unsigned int curr = buy.size();

	buy.push_back(obj);

	buyHeapIndex[obj.bidId] = curr;

	while (curr > 1) {
		if (buy[curr] > buy[curr/2]) {
			buyHeapIndex[buy[curr/2].bidId] = curr;
			buyHeapIndex[buy[curr].bidId] = curr/2;
			struct bid tmp = buy[curr/2];
			buy[curr/2] = buy[curr];
			buy[curr] = tmp;
			curr /= 2;
		} else {
			curr = 1;
		}
	}
	return;
}
inline void BidHeap::insert(const struct bid & obj) {
	switch (obj.action) {
		case BID_ACTION_BUY:
			insertBuy(obj);
			break;
		case BID_ACTION_SELL:
			insertSell(obj);
			break;
		case BID_ACTION_CANCEL: default:
			removeByBidId(obj.price); // "price" is bidId
			break;
	}
	return;
}

inline struct bid BidHeap::minSell() {
	if (sell.size() > 1) {
		return sell[1];
	}
	return sell[0];
}
inline struct bid BidHeap::maxBuy() {
	if (buy.size() > 1) {
		return buy[1];
	}
	return buy[1];
}
inline void BidHeap::removeMinSell() {
	removeSellByHeapIndex(1);
}
inline void BidHeap::removeMaxBuy() {
	removeBuyByHeapIndex(1);
}

inline void BidHeap::removeSellByHeapIndex(unsigned int index) {
	if (sell.size() == 1) {
		return;
	}
	if (index < 1 || index >= sell.size()) {
		return;
	}
	sellHeapIndex[sell[index].bidId] = 0; // clear
	sellHeapIndex.erase(sell[index].bidId);
	sell[index] = sell.back();
	if (sellHeapIndex.find(sell.back().bidId) != sellHeapIndex.end()) {
		sellHeapIndex[sell.back().bidId] = index;
	}
	sell.pop_back();

	unsigned int curr = index;
	while (curr < sell.size()) {
		unsigned int smaller = curr;
		if (curr * 2 < sell.size()) {
			smaller = curr * 2;
		}
		if (curr * 2 + 1 < sell.size()) {
			if (sell[curr * 2 + 1] < sell[curr * 2]) {
				smaller = curr * 2 + 1;
			}
		}
		if (sell[smaller] < sell[curr]) {
			sellHeapIndex[sell[smaller].bidId] = curr;
			sellHeapIndex[sell[curr].bidId] = smaller;
			struct bid tmp = sell[curr];
			sell[curr] = sell[smaller];
			sell[smaller] = tmp;
			curr = smaller;
		} else {
			curr = sell.size();
		}
	}

	return;
}
inline void BidHeap::removeBuyByHeapIndex(unsigned int index) {
	if (buy.size() == 1) {
		return;
	}
	if (index < 1 || index >= buy.size()) {
		return;
	}
	buyHeapIndex[buy[index].bidId] = 0; // clear
	buyHeapIndex.erase(buy[index].bidId);
	buy[index] = buy.back();
	if (buyHeapIndex.find(buy.back().bidId) != buyHeapIndex.end()) {
		buyHeapIndex[buy.back().bidId] = index;
	}
	buy.pop_back();

	unsigned int curr = index;
	while (curr < buy.size()) {
		unsigned int larger= curr;
		if (curr * 2 < buy.size()) {
			larger = curr * 2;
		}
		if (curr * 2 + 1 < buy.size()) {
			if (buy[curr * 2 + 1] > buy[curr * 2]) {
				larger = curr * 2 + 1;
			}
		}
		if (buy[larger] > buy[curr]) {
			buyHeapIndex[buy[larger].bidId] = curr;
			buyHeapIndex[buy[curr].bidId] = larger;
			struct bid tmp = buy[curr];
			buy[curr] = buy[larger];
			buy[larger] = tmp;
			curr = larger;
		} else {
			curr = buy.size();
		}
	}

	return;
}
inline void BidHeap::removeSellByBidId(int bidId) {
	removeSellByHeapIndex(sellHeapIndex[bidId]);
}
inline void BidHeap::removeBuyByBidId(int bidId) {
	removeBuyByHeapIndex(buyHeapIndex[bidId]);
}
inline void BidHeap::removeByBidId(int bidId) {
	switch(whereIs(bidId)) {
	case 0:
		removeBuyByBidId(bidId);
		break;
	case 1:
		removeSellByBidId(bidId);
		break;
	default:
		break;
	}
	return;
}
inline int BidHeap::whereIs(int bidId) {
	// 0: buy, 1: sell, -1, not found
	// called by removebybidId
#if DEBUG == 1
	std::cout << "cancel bidId = " << bidId << "\n";
#endif
	if (buyHeapIndex.find(bidId) != buyHeapIndex.end()) {
		if (buy[buyHeapIndex[bidId]].bidId == bidId) {
#if DEBUG == 1
			std::cout << "bidId " << bidId << "exist in buy\n";
#endif
			return 0;
		}
	}
	if (sellHeapIndex.find(bidId) != sellHeapIndex.end()) {
		if (sell[sellHeapIndex[bidId]].bidId == bidId) {
#if DEBUG == 1
			std::cout << "bidId " << bidId << "exist in sell\n";
#endif
			return 1;
		}
	}
#if DEBUG == 1
	std::cout << "not found\n";
#endif
	return -1;
}

inline void BidHeap::display(std::ostream & output) {
	output << "sell:\n";
	for (unsigned int i = 1; i < sell.size(); i++) {
		output << i << ": " << sell[i] << "\n";
	}
	output << "buy:\n";
	for (unsigned int i = 1; i < buy.size(); i++) {
		output << i << ": " << buy[i] << "\n";
	}
	output << "sellHeapIndex:\n";
	for (std::map<int, int>::iterator it = sellHeapIndex.begin(); it!=sellHeapIndex.end(); it++) {
		std::cout << it->first << " " << it->second << "\n";
	}
	output << "buyHeapIndex:\n";
	for (std::map<int, int>::iterator it = buyHeapIndex.begin(); it!=buyHeapIndex.end(); it++) {
		std::cout << it->first << " " << it->second << "\n";
	}
	output << "\n\n";
	return;
}

#endif
