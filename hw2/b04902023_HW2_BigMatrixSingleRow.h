#ifndef B04902023_HW2_BIGMATRIXSINGLEROW_H
#define B04902023_HW2_BIGMATRIXSINGLEROW_H

#include <iostream>
#include <iomanip> //setw, setfill, left

class BigMatrixSingleRow {
public:
	int UserId;
	int ItemId;
	int Result;
	int UnixTimeStamp;

	friend std::istream & operator >> (std::istream & input, BigMatrixSingleRow & row) {
		input >> row.UserId >> row.ItemId >> row.Result >> row.UnixTimeStamp;
		return input;
	}
	friend std::ostream & operator << (std::ostream & output, const BigMatrixSingleRow & row) {
		output << std::setfill(' ') << std::setw(8) << std::left << row.UserId << std::setfill(' ') << std::setw(8) << std::left << row.ItemId << std::setfill(' ') << std::setw(8) << std::left << row.Result << std::setfill(' ') << std::setw(10) << std::left << row.UnixTimeStamp << std::endl;
		return output;
	}

	bool operator == (BigMatrixSingleRow & b) {
		if ((UserId == b.UserId) && (ItemId == b.ItemId) && (Result == b.Result) && (UnixTimeStamp == b.UnixTimeStamp)) {
			return true;
		} else {
			return false;
		}
	}
	bool operator != (BigMatrixSingleRow & b) {
		if ((UserId == b.UserId) && (ItemId == b.ItemId) && (Result == b.Result) && (UnixTimeStamp == b.UnixTimeStamp)) {
			return false;
		} else {
			return true;
		}
	}

};

/*
bool operator == (const BigMatrixSingleRow & a, const BigMatrixSingleRow & b) {
	if ((a.UserId == b.UserId) && (a.ItemId == b.ItemId) && (a.Result == b.Result) && (a.UnixTimeStamp == b.UnixTimeStamp)) {
		return true;
	} else {
		return false;
	}
}

bool operator != (const BigMatrixSingleRow & a, const BigMatrixSingleRow & b) {
	if ((a.UserId == b.UserId) && (a.ItemId == b.ItemId) && (a.Result == b.Result) && (a.UnixTimeStamp == b.UnixTimeStamp)) {
		return false;
	} else {
		return true;
	}

}
*/

#endif
