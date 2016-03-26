#include <iostream>
#ifndef B04902023_HW2_BIGMATRIX_H
#define B04902023_HW2_BIGMATRIX_H

#include <vector>
#include <string> //string name
#include <map>
#include <set>

#include "b04902023_HW2_BigMatrixSingleRow.h"
#include "b04902023_HW2_BigMatrixItemTimesSingleRow.h"

class BigMatrix {
	private:
		std::vector<BigMatrixSingleRow> * selectedDisplayArray;
		std::vector<BigMatrixSingleRow> raw;

		
		std::map<int, int> givenItemTimes;
		std::vector<BigMatrixItemTimesSingleRow> sortByItemTimesRecommendedTimesUserId;
	public:

		std::vector<BigMatrixSingleRow> sortByUserIdItemIdUnixTimeStamp;
		std::vector<BigMatrixSingleRow> sortByItemIdUserIdUnixTimeStamp;
		std::vector<BigMatrixSingleRow> sortByUnixTimeStampItemIdUserId;
		BigMatrix();
		friend std::istream & operator >> (std::istream & input, BigMatrix & matrix);
		void ConstructDataStructure();
		friend std::ostream & operator << (std::ostream & output, const BigMatrix & matrix);
		int get_size();
		void select_display_array(const std::string & arrayName);

		int accept(int userId, int itemId, int unixTimeStamp);
		std::vector<int> items(int userId1, int userId2);
		std::vector<int> users(int itemId1, int itemId2, int unixTimeStamp1, int unixTimeStamp2);
		std::vector<int> ratio(int itemId, int threshold); // only two integers, the first is accept and the second is total
		std::vector<int> findtime_item(int itemId, const std::set<int> & Us);
};

#endif
