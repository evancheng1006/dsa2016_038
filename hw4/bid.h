#ifndef BID_H
#define BID_H

#include <iostream>

struct bid {
	int bidId, clientId, action, price, shareCount;
	inline friend std::istream & operator >> (std::istream & input, struct bid & bd); 
	inline friend std::ostream & operator << (std::ostream & output, const struct bid & bd);
};
typedef struct bid Bid;

inline bool operator < (const struct bid & lhs, const struct bid & rhs) {
	// warning: only used in minheap
	if (lhs.price < rhs.price) {
		return true;
	} else if (lhs.price > rhs.price) {
		return false;
	} else {
		return (lhs.bidId < lhs.bidId);
	}
	return false;
}
inline bool operator > (const struct bid & lhs, const struct bid & rhs) {
	// warning: only used in maxheap
	if (lhs.price > rhs.price) {
		return true;
	} else if (lhs.price < rhs.price) {
		return false;
	} else {
		return (lhs.bidId < lhs.bidId);
	}
	return false;
}

inline std::istream & operator >> (std::istream & input, struct bid & bd) {
	input >> bd.bidId >> bd.clientId >> bd.action >> bd.price >> bd.shareCount;
	return input;
}
inline std::ostream & operator << (std::ostream & output, const struct bid & bd) {
	output << bd.bidId << ' ' << bd.clientId << ' ' << bd.action << ' ' << bd.price << ' ' << bd.shareCount;
	return output;
}


#define BID_ACTION_BUY (0)
#define BID_ACTION_SELL (1)
#define BID_ACTION_CANCEL (2)


#endif
