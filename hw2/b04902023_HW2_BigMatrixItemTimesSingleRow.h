#ifndef B04902023_HW2_BIGMATRIXITEMTIMESSINGLEROW_H
#define B04902023_HW2_BIGMATRIXITEMTIMESSINGLEROW_H

#include <iostream>
#include <iomanip> //setw, setfill, left

class BigMatrixItemTimesSingleRow {
public:
	int UserId;
	int ItemId;
	int RecommendedTimes;
	int Accept; //1: accept, 0: doesn't accept

	friend std::istream & operator >> (std::istream & input, BigMatrixItemTimesSingleRow & row) {
		input >> row.UserId >> row.ItemId >> row.RecommendedTimes >> row.Accept;
		return input;
	}
	friend std::ostream & operator << (std::ostream & output, const BigMatrixItemTimesSingleRow & row) {
		output << std::setfill(' ') << std::setw(8) << std::left << row.UserId << std::setfill(' ') << std::setw(8) << std::left << row.ItemId << std::setfill(' ') << std::setw(8) << std::left << row.RecommendedTimes << std::setfill(' ') << std::setw(10) << std::left << row.Accept << std::endl;
		return output;
	}
};

#endif
