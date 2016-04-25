#ifndef TRANS_H
#define TRANS_H

#include <iostream>

struct trans {
	int transId, buyClientId, sellClientId, transPrice, transShareCount;
	inline friend std::istream & operator >> (std::istream & input, struct trans & tr);
	inline friend std::ostream & operator << (std::ostream & output, const struct bid & tr);
};
typedef struct trans Trans;
inline std::istream & operator >> (std::istream & input, struct trans & tr) {
	input >> tr.transId >> tr.buyClientId >> tr.sellClientId >> tr.transPrice >> tr.transShareCount;
	return input;
}
inline std::ostream & operator << (std::ostream & output, const struct trans & tr) {
	output << tr.transId << ' ' << tr.buyClientId << ' ' << tr.sellClientId << ' ' << tr.transPrice << ' ' << tr.transShareCount;
	return output;
}
#endif
