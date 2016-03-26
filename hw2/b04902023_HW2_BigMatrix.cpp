// File name: b04902023_HW2_BigMatrix.cpp

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm> //sort

#include "b04902023_HW2_BigMatrix.h"

BigMatrix::BigMatrix() {
	selectedDisplayArray = &sortByItemIdUserIdUnixTimeStamp;
	const unsigned int INPUTLINES = 73209277;
	try {
//		raw.reserve(INPUTLINES);
		sortByUserIdItemIdUnixTimeStamp.reserve(INPUTLINES);
		sortByItemIdUserIdUnixTimeStamp.reserve(INPUTLINES);
		sortByUnixTimeStampItemIdUserId.reserve(INPUTLINES);
	}
	catch(std::bad_alloc & ba) {
//		std::cerr << "bad allocation" << std::endl;
	}
}

static bool sortByItemIdUserIdUnixTimeStampCompare(const BigMatrixSingleRow & a, const BigMatrixSingleRow & b) {
	if (a.ItemId == b.ItemId) {
		if (a.UserId == b.UserId) {
			return (a.UnixTimeStamp < b.UnixTimeStamp);
		}
		return (a.UserId < b.UserId);
	}
	return (a.ItemId < b.ItemId);
}
static bool sortByUserIdItemIdUnixTimeStampCompare(const BigMatrixSingleRow & a, const BigMatrixSingleRow & b) {
	if (a.UserId == b.UserId) {
		if (a.ItemId == b.ItemId) {
			return (a.UnixTimeStamp < b.UnixTimeStamp);
		}
		return (a.ItemId < b.ItemId);
	}
	return (a.UserId < b.UserId);
}
static bool sortByUnixTimeStampItemIdUserIdCompare(const BigMatrixSingleRow & a, const BigMatrixSingleRow & b) {
	if (a.UnixTimeStamp == b.UnixTimeStamp) {
		if (a.ItemId == b.ItemId) {
			return (a.UserId < b.UserId);
		}
		return (a.ItemId < b.ItemId);
	}
	return (a.UnixTimeStamp < b.UnixTimeStamp);
}
static bool sortByItemTimesRecommendedTimesUserIdCompare(const BigMatrixItemTimesSingleRow & a, const BigMatrixItemTimesSingleRow & b) {
	if (a.ItemId == b.ItemId) {
		if (a.RecommendedTimes == b.RecommendedTimes) {
			return (a.UserId < b.UserId);
		}
		return (a.RecommendedTimes < b.RecommendedTimes);
	}
	return (a.ItemId < b.ItemId);
}

std::istream & operator >> (std::istream & input, BigMatrix & matrix) {
	int i; // matrix index
        struct BigMatrixSingleRow tmp; // tmpInput
	matrix.sortByItemIdUserIdUnixTimeStamp.clear();
	while (input >> tmp) {
		// since all two exact same rows appears continuously, this algorithm can remove all duplications.
		if (tmp != matrix.sortByItemIdUserIdUnixTimeStamp[matrix.sortByItemIdUserIdUnixTimeStamp.size()-1]) {
			matrix.sortByItemIdUserIdUnixTimeStamp.push_back(tmp);
		}
	}
	matrix.ConstructDataStructure();
}
void BigMatrix::ConstructDataStructure() {
//	std::cout << matrix.raw.size();
//	sortByItemIdUserIdUnixTimeStamp = raw;
	sort(sortByItemIdUserIdUnixTimeStamp.begin(), sortByItemIdUserIdUnixTimeStamp.end(), sortByItemIdUserIdUnixTimeStampCompare);

	sortByUserIdItemIdUnixTimeStamp = sortByItemIdUserIdUnixTimeStamp;
	sort(sortByUserIdItemIdUnixTimeStamp.begin(), sortByUserIdItemIdUnixTimeStamp.end(), sortByUserIdItemIdUnixTimeStampCompare);
	
//	matrix.sortByUnixTimeStampItemIdUserId = matrix.raw;
//	sort(matrix.sortByUnixTimeStampItemIdUserId.begin(), matrix.sortByUnixTimeStampItemIdUserId.end(), sortByUnixTimeStampItemIdUserIdCompare);

	// sortByItemTimesRecommendedTimesUserId
	int sourceSize = sortByItemIdUserIdUnixTimeStamp.size();
	
	sortByItemTimesRecommendedTimesUserId.clear();
	
	BigMatrixItemTimesSingleRow tmpRow;
	if (sourceSize > 0) {
        // create a new one but don't do anything
		tmpRow.UserId = sortByItemIdUserIdUnixTimeStamp[0].UserId;
		tmpRow.ItemId = sortByItemIdUserIdUnixTimeStamp[0].ItemId;
		tmpRow.RecommendedTimes = 0;
		tmpRow.Accept = 0;
		sortByItemTimesRecommendedTimesUserId.push_back(tmpRow);
	}
	int iSourceRow = 0; // counter
	while (iSourceRow < sourceSize) {
		if (sortByItemIdUserIdUnixTimeStamp[iSourceRow].ItemId == sortByItemTimesRecommendedTimesUserId[sortByItemTimesRecommendedTimesUserId.size()-1].ItemId && 
			sortByItemIdUserIdUnixTimeStamp[iSourceRow].UserId == sortByItemTimesRecommendedTimesUserId[sortByItemTimesRecommendedTimesUserId.size()-1].UserId) {
			
			sortByItemTimesRecommendedTimesUserId[sortByItemTimesRecommendedTimesUserId.size()-1].RecommendedTimes++;
			if (sortByItemIdUserIdUnixTimeStamp[iSourceRow].Result == 1) {
				sortByItemTimesRecommendedTimesUserId[sortByItemTimesRecommendedTimesUserId.size()-1].Accept = 1;
			}
			iSourceRow++;
        } else {
			// create a new one but don't do anything
			tmpRow.UserId = sortByItemIdUserIdUnixTimeStamp[iSourceRow].UserId;
			tmpRow.ItemId = sortByItemIdUserIdUnixTimeStamp[iSourceRow].ItemId;
			tmpRow.RecommendedTimes = 0;
			tmpRow.Accept = 0;
			sortByItemTimesRecommendedTimesUserId.push_back(tmpRow);
		}
	}
	sort(sortByItemTimesRecommendedTimesUserId.begin(), sortByItemTimesRecommendedTimesUserId.end(), sortByItemTimesRecommendedTimesUserIdCompare);
	
	// calculate REAL recommeded times
	// Time complexity of find() in std::map? log(n)
	
	// fucking spec
	givenItemTimes.clear();
	sourceSize = sortByItemIdUserIdUnixTimeStamp.size();
	for (iSourceRow = 0; iSourceRow < sourceSize; iSourceRow++) {
		if (givenItemTimes.find(sortByItemIdUserIdUnixTimeStamp[iSourceRow].UserId) == givenItemTimes.end()) {
			givenItemTimes[sortByItemIdUserIdUnixTimeStamp[iSourceRow].UserId] = 1;
		} else {
			givenItemTimes[sortByItemIdUserIdUnixTimeStamp[iSourceRow].UserId]++;
		}
	}
	// rewrite
	int sortByItemTimesRecommendedTimesUserIdSize = sortByItemTimesRecommendedTimesUserId.size();
	for (int iDestRow = 0; iDestRow < sortByItemTimesRecommendedTimesUserIdSize; iDestRow++) {
		sortByItemTimesRecommendedTimesUserId[iDestRow].RecommendedTimes = givenItemTimes[sortByItemTimesRecommendedTimesUserId[iDestRow].UserId];
	}
	
//	for (std::map<int, int>::const_iterator it = matrix.givenItemTimes.begin(); it != matrix.givenItemTimes.end(); it++) {
//		std::cout << it->first << " " << it->second << std::endl;
//	}
	sort(sortByItemTimesRecommendedTimesUserId.begin(), sortByItemTimesRecommendedTimesUserId.end(), sortByItemTimesRecommendedTimesUserIdCompare);
	
//	for (int iDestRow = 0; iDestRow < matrix.sortByItemTimesRecommendedTimesUserId.size(); iDestRow++) {
//		std::cout << matrix.sortByItemTimesRecommendedTimesUserId[iDestRow];
//	}	
}

std::ostream & operator << (std::ostream & output, const BigMatrix & matrix) {
	for (int i = 0; i < matrix.selectedDisplayArray->size(); i++) {
		output << (*matrix.selectedDisplayArray)[i];
	}
	return output;
}

int BigMatrix::get_size() {
	return raw.size();
}
void BigMatrix::select_display_array(const std::string & arrayName) {
	if (arrayName == "raw") {
		selectedDisplayArray = &raw;
	} else if (arrayName == "sortByUserIdItemIdUnixTimeStamp") {
		selectedDisplayArray = &sortByUserIdItemIdUnixTimeStamp;
	} else if (arrayName == "sortByItemIdUserIdUnixTimeStamp") {
		selectedDisplayArray = &sortByItemIdUserIdUnixTimeStamp;
	} else if (arrayName == "sortByUnixTimeStampItemIdUserId") {
		selectedDisplayArray = &sortByUnixTimeStampItemIdUserId;
	} else {
		//do nothing
	}
	return;
}


static int sortByUserIdItemIdUnixTimeStampCompareWithEquality(const BigMatrixSingleRow & a, const BigMatrixSingleRow & b) {
	// called by accept()
	// return value: -1: a<b, 0: a==b, 1: a>b
	if (a.UserId < b.UserId) {
		return -1;
	} else if (a.UserId > b.UserId) {
		return 1;
	}
	if (a.ItemId < b.ItemId) {
		return -1;
	} else if (a.ItemId > b.ItemId) {
		return 1;
	}
	if (a.UnixTimeStamp < b.UnixTimeStamp) {
		return -1;
	} else if (a.UnixTimeStamp > b.UnixTimeStamp) {
		return 1;
	}
	return 0;
}

int BigMatrix::accept(int userId, int itemId, int unixTimeStamp) {
	// binary search
	// return value: 1: accept, -1: reject, 0: not found
	// search sortByUserIdItemIdUnixTimeStamp
	// searchLowerBound <= index <= searchUpperBound
	// when the search is finished, make searchLowerBound > searchUpperBound
	// please write this function carefully, DO NOT make index out of bound.
	// Therefore, we don't need vector.at(i) to check.
	int searchLowerBound, searchUpperBound;
	searchLowerBound = 0;
	searchUpperBound = sortByUserIdItemIdUnixTimeStamp.size() - 1;

	BigMatrixSingleRow target;
	target.UserId = userId;
	target.ItemId = itemId;
	target.UnixTimeStamp = unixTimeStamp;
	// default result : 0 (not found)
	// because when the vector size is 0, we will skip the search, and the result will be 0(not found).
	// the result will be stored in target.Result after binary search
	target.Result = 0;

	while (searchLowerBound <= searchUpperBound) {
		int tmpSelected = (searchLowerBound + searchUpperBound) / 2; // initialise binary search
		// compare
		// do compare only once
		int compareResult = sortByUserIdItemIdUnixTimeStampCompareWithEquality(target, sortByUserIdItemIdUnixTimeStamp[tmpSelected]);
		if (compareResult == 1) {
			// target is larger
			searchLowerBound = tmpSelected + 1;
		} else if (compareResult == -1) {
			// target is smaller
			searchUpperBound = tmpSelected - 1;
		} else {
			// target found
			target.Result = sortByUserIdItemIdUnixTimeStamp[tmpSelected].Result;
			// end search
			searchUpperBound = -2;
			searchLowerBound = -1;
		}
	}
	return target.Result;
}

std::vector<int> BigMatrix::items(int userId1, int userId2) {
	// search sortByUserIdItemIdUnixTimeStamp
	// Algorithm:
	// use binary search to find the starting index of userId1
	// use binary search to find the starting index of userId2
	// search common items
	
	std::vector<int> result;

	int userId1StartIndex, userId2StartIndex;
	int searchLowerBound, searchUpperBound;

	// userId1
	searchLowerBound = 0;
	searchUpperBound = sortByUserIdItemIdUnixTimeStamp.size() - 1;
	// default index : -1 (not found)
	// if the index isn't found, we will end our search and return an empty vector
	userId1StartIndex = -1;

	while (searchLowerBound <= searchUpperBound) {
		// be careful not to be out of range
		int tmpSelected = (searchLowerBound + searchUpperBound) / 2; // initialise binary search
		// compare
		if (sortByUserIdItemIdUnixTimeStamp[tmpSelected].UserId < userId1) {
			// search upper half
			searchLowerBound = tmpSelected + 1;
		} else if (sortByUserIdItemIdUnixTimeStamp[tmpSelected].UserId > userId1) {
			// search lower half
			searchUpperBound = tmpSelected - 1;
		} else {
			// has the same userId
			if (tmpSelected == 0) {
				// tmpSelected - 1 does not exit
				// exception
				// target found, end loop
				userId1StartIndex = tmpSelected;
				searchUpperBound = -2;
				searchLowerBound = -1;
			} else {
				// check whether is the start
				if (sortByUserIdItemIdUnixTimeStamp[tmpSelected - 1].UserId < userId1) {
					// target found, end loop
					userId1StartIndex = tmpSelected;
					searchUpperBound = -2;
					searchLowerBound = -1;
				} else {
					// search lower half
					searchUpperBound = tmpSelected - 1;
				}
			}
		}
	}
	// userId2
	searchLowerBound = 0;
	searchUpperBound = sortByUserIdItemIdUnixTimeStamp.size() - 1;
	// default index : -1 (not found)
	// if the index isn't found, we will end our search and return an empty vector
	userId2StartIndex = -1;

	while (searchLowerBound <= searchUpperBound) {
		// be careful not to be out of range
		int tmpSelected = (searchLowerBound + searchUpperBound) / 2; // initialise binary search
		// compare
		if (sortByUserIdItemIdUnixTimeStamp[tmpSelected].UserId < userId2) {
			// search upper half
			searchLowerBound = tmpSelected + 1;
		} else if (sortByUserIdItemIdUnixTimeStamp[tmpSelected].UserId > userId2) {
			// search lower half
			searchUpperBound = tmpSelected - 1;
		} else {
			// has the same userId
			if (tmpSelected == 0) {
				// tmpSelected - 1 does not exit
				// exception
				// target found, end loop
				userId2StartIndex = tmpSelected;
				searchUpperBound = -2;
				searchLowerBound = -1;
			} else {
				// check whether is the start
				if (sortByUserIdItemIdUnixTimeStamp[tmpSelected - 1].UserId < userId2) {
					// target found, end loop
					userId2StartIndex = tmpSelected;
					searchUpperBound = -2;
					searchLowerBound = -1;
				} else {
					// search lower half
					searchUpperBound = tmpSelected - 1;
				}
			}
		}
	}

	if (userId1StartIndex < 0 || userId2StartIndex < 0) {
		result.clear();
		return result; // end function
	}

	// find common elements
	int tmpUserId1Index = userId1StartIndex;
	int tmpUserId2Index = userId2StartIndex;

	int IndexMaxLimit = sortByUserIdItemIdUnixTimeStamp.size();
	int contLoop = 1;
	while (tmpUserId1Index < IndexMaxLimit && tmpUserId2Index < IndexMaxLimit && contLoop) {
		if (sortByUserIdItemIdUnixTimeStamp[tmpUserId1Index].UserId != userId1 || sortByUserIdItemIdUnixTimeStamp[tmpUserId2Index].UserId != userId2) {
			contLoop = 0;
		} else {
			if (sortByUserIdItemIdUnixTimeStamp[tmpUserId1Index].ItemId < sortByUserIdItemIdUnixTimeStamp[tmpUserId2Index].ItemId) {
				tmpUserId1Index++;
			} else if (sortByUserIdItemIdUnixTimeStamp[tmpUserId1Index].ItemId > sortByUserIdItemIdUnixTimeStamp[tmpUserId2Index].ItemId) {
				tmpUserId2Index++;
			} else {
				// common item found
				// save result if not the same element
				if (result.size() == 0) {
					result.push_back(sortByUserIdItemIdUnixTimeStamp[tmpUserId1Index].ItemId);
				} else {
					if (result[result.size() - 1] != sortByUserIdItemIdUnixTimeStamp[tmpUserId1Index].ItemId) {
						result.push_back(sortByUserIdItemIdUnixTimeStamp[tmpUserId1Index].ItemId);
					}
				}
				// increase either index is OK
				tmpUserId1Index++;
			}
		}
	}

	return result;
}

std::vector<int> BigMatrix::users(int itemId1, int itemId2, int unixTimeStamp1, int unixTimeStamp2) {
	// search sortByItemIdUserIdUnixTimeStamp
	// Algorithm:
	// use binary search to find the starting index of itemId1
	// use binary search to find the starting index of itemId2
	// search common users with unixTimeStamp filtering
	
	std::vector<int> result;
	
	int itemId1StartIndex, itemId2StartIndex;
	int searchLowerBound, searchUpperBound;
	
	// itemId1
	searchLowerBound = 0;
	searchUpperBound = sortByItemIdUserIdUnixTimeStamp.size() - 1;
	// default index : -1 (not found)
	// if the index isn't found, we will end our search and return an empty vector
	itemId1StartIndex = -1;
	
	while (searchLowerBound <= searchUpperBound) {
		int tmpSelected = (searchLowerBound + searchUpperBound) / 2;
		if (sortByItemIdUserIdUnixTimeStamp[tmpSelected].ItemId < itemId1) {
			// search upper half
			searchLowerBound = tmpSelected + 1;
		} else if (sortByItemIdUserIdUnixTimeStamp[tmpSelected].ItemId > itemId1) {
			// search lower half
			searchUpperBound = tmpSelected - 1;
		} else {
			// has the same userId
			if (tmpSelected == 0) {
				// tmpSelected - 1 does not exit
				// exception
				// target found, end loop
				itemId1StartIndex = tmpSelected;
				searchUpperBound = -2;
				searchLowerBound = -1;
			} else {
				// check whether is the start
				if (sortByItemIdUserIdUnixTimeStamp[tmpSelected - 1].ItemId < itemId1) {
					// target found, end loop
					itemId1StartIndex = tmpSelected;
					searchUpperBound = -2;
					searchLowerBound = -1;
				} else {
					// search lower half
					searchUpperBound = tmpSelected - 1;
				}
			}
		}
	}
	
	// itemId2
	searchLowerBound = 0;
	searchUpperBound = sortByItemIdUserIdUnixTimeStamp.size() - 1;
	// default index : -1 (not found)
	// if the index isn't found, we will end our search and return an empty vector
	itemId2StartIndex = -1;
	
	while (searchLowerBound <= searchUpperBound) {
		int tmpSelected = (searchLowerBound + searchUpperBound) / 2;
		if (sortByItemIdUserIdUnixTimeStamp[tmpSelected].ItemId < itemId2) {
			// search upper half
			searchLowerBound = tmpSelected + 1;
		} else if (sortByItemIdUserIdUnixTimeStamp[tmpSelected].ItemId > itemId2) {
			// search lower half
			searchUpperBound = tmpSelected - 1;
		} else {
			// has the same userId
			if (tmpSelected == 0) {
				// tmpSelected - 1 does not exit
				// exception
				// target found, end loop
				itemId2StartIndex = tmpSelected;
				searchUpperBound = -2;
				searchLowerBound = -1;
			} else {
				// check whether is the start
				if (sortByItemIdUserIdUnixTimeStamp[tmpSelected - 1].ItemId < itemId2) {
					// target found, end loop
					itemId2StartIndex = tmpSelected;
					searchUpperBound = -2;
					searchLowerBound = -1;
				} else {
					// search lower half
					searchUpperBound = tmpSelected - 1;
				}
			}
		}
	}
	
	if (itemId1StartIndex < 0 || itemId2StartIndex < 0) {
		result.clear();
		return result; // end function
	}
	
	// find common elements
	int tmpItemId1Index = itemId1StartIndex;
	int tmpItemId2Index = itemId2StartIndex;

	int IndexMaxLimit = sortByItemIdUserIdUnixTimeStamp.size();
	int contLoop = 1;
	while (tmpItemId1Index < IndexMaxLimit && tmpItemId2Index < IndexMaxLimit && contLoop) {
		if (sortByItemIdUserIdUnixTimeStamp[tmpItemId1Index].ItemId != itemId1 || sortByItemIdUserIdUnixTimeStamp[tmpItemId2Index].ItemId != itemId2) {
			contLoop = 0;
		} else {
			if (sortByItemIdUserIdUnixTimeStamp[tmpItemId1Index].UserId < sortByItemIdUserIdUnixTimeStamp[tmpItemId2Index].UserId) {
				tmpItemId1Index++;
			} else if (sortByItemIdUserIdUnixTimeStamp[tmpItemId1Index].UserId > sortByItemIdUserIdUnixTimeStamp[tmpItemId2Index].UserId) {
				tmpItemId2Index++;
			} else {
				// common user found and find if there is a solution with valid time
				
				// make a valid time for tmpItemId1Index
				// make a valid time for tmpItemId2Index
				if (sortByItemIdUserIdUnixTimeStamp[tmpItemId1Index].UnixTimeStamp < unixTimeStamp1 || sortByItemIdUserIdUnixTimeStamp[tmpItemId1Index].UnixTimeStamp > unixTimeStamp2) {
					tmpItemId1Index++;
				} else if (sortByItemIdUserIdUnixTimeStamp[tmpItemId2Index].UnixTimeStamp < unixTimeStamp1 || sortByItemIdUserIdUnixTimeStamp[tmpItemId2Index].UnixTimeStamp > unixTimeStamp2) {
					tmpItemId2Index++;
				} else {
					// now the time is valid
					if (result.size() == 0) {
						result.push_back(sortByItemIdUserIdUnixTimeStamp[tmpItemId1Index].UserId);
					} else {
						if (result[result.size() - 1] != sortByItemIdUserIdUnixTimeStamp[tmpItemId1Index].UserId) {
							result.push_back(sortByItemIdUserIdUnixTimeStamp[tmpItemId1Index].UserId);
						}
					}
					// after writing, increase either index is OK
					tmpItemId1Index++;
				}
			}
		}
	}

//	result.push_back(itemId1StartIndex);
//	result.push_back(itemId2StartIndex);
	
	return result;
}

std::vector<int> BigMatrix::ratio(int itemId, int threshold) {
	// Algorithm:
	// use sortByItemTimesRecommendedTimesUserId
	// use binary search to find the starting index of itemId
	// use threshold to filter
	int accept;
	int total;
	std::vector<int> result;
	
	int itemIdStartIndex;
	int searchLowerBound, searchUpperBound;
	
	// itemId
	searchLowerBound = 0;
	searchUpperBound = sortByItemTimesRecommendedTimesUserId.size() - 1;
	// default index : -1 (not found)
	// if the index isn't found, we will end our search and return an empty vector
	itemIdStartIndex = -1;
	
	while (searchLowerBound <= searchUpperBound) {
		int tmpSelected = (searchLowerBound + searchUpperBound) / 2;
		if (sortByItemTimesRecommendedTimesUserId[tmpSelected].ItemId < itemId) {
			// search upper half
			searchLowerBound = tmpSelected + 1;
		} else if (sortByItemTimesRecommendedTimesUserId[tmpSelected].ItemId > itemId) {
			// search lower half
			searchUpperBound = tmpSelected - 1;
		} else {
			// has the same userId
			if (tmpSelected == 0) {
				// tmpSelected - 1 does not exit
				// exception
				// target found, end loop
				itemIdStartIndex = tmpSelected;
				searchUpperBound = -2;
				searchLowerBound = -1;
			} else {
				// check whether is the start
				if (sortByItemTimesRecommendedTimesUserId[tmpSelected - 1].ItemId < itemId) {
					// target found, end loop
					itemIdStartIndex = tmpSelected;
					searchUpperBound = -2;
					searchLowerBound = -1;
				} else {
					// search lower half
					searchUpperBound = tmpSelected - 1;
				}
			}
		}
	}
	
	
	total = 0;	
	for (std::map<int, int>::const_iterator it = givenItemTimes.begin(); it != givenItemTimes.end(); it++) {
		if (it->second > threshold) {
			total++;
		}
	}
	
	int iSourceRow = itemIdStartIndex;
	int contLoop = 1;
	accept = 0;
	while (iSourceRow < sortByItemTimesRecommendedTimesUserId.size() && contLoop) {
		if (sortByItemTimesRecommendedTimesUserId[iSourceRow].ItemId != itemId) {
			contLoop = 0;
		} else {
			if (sortByItemTimesRecommendedTimesUserId[iSourceRow].RecommendedTimes > threshold) {
				if (sortByItemTimesRecommendedTimesUserId[iSourceRow].Accept == 1) {
					accept++;
                }
			}
			iSourceRow++;
		}	
	}
	
	result.push_back(accept);
	result.push_back(total);
	return result;
}
std::vector<int> BigMatrix::findtime_item(int itemId, const std::set<int> & Us) {
	// Algorithm:
	// search sortByItemIdUserIdUnixTimeStamp
	// use binary search to find the starting index of itemId
	// save unsorted result in the set and then copy it to a vector
	std::set<int> unsortedResult;
	std::vector<int> result;
	
	
	int itemIdStartIndex;
	int searchLowerBound, searchUpperBound;
	

	
	// itemId
	searchLowerBound = 0;
	searchUpperBound = sortByItemIdUserIdUnixTimeStamp.size() - 1;
	// default index : -1 (not found)
	// if the index isn't found, we will end our search and return an empty vector
	itemIdStartIndex = -1;
	
	while (searchLowerBound <= searchUpperBound) {
		int tmpSelected = (searchLowerBound + searchUpperBound) / 2;
		if (sortByItemIdUserIdUnixTimeStamp[tmpSelected].ItemId < itemId) {
			// search upper half
			searchLowerBound = tmpSelected + 1;
		} else if (sortByItemIdUserIdUnixTimeStamp[tmpSelected].ItemId > itemId) {
			// search lower half
			searchUpperBound = tmpSelected - 1;
		} else {
			// has the same userId
			if (tmpSelected == 0) {
				// tmpSelected - 1 does not exit
				// exception
				// target found, end loop
				itemIdStartIndex = tmpSelected;
				searchUpperBound = -2;
				searchLowerBound = -1;
			} else {
				// check whether is the start
				if (sortByItemIdUserIdUnixTimeStamp[tmpSelected - 1].ItemId < itemId) {
					// target found, end loop
					itemIdStartIndex = tmpSelected;
					searchUpperBound = -2;
					searchLowerBound = -1;
				} else {
					// search lower half
					searchUpperBound = tmpSelected - 1;
				}
			}
		}
	}

	int iSourceRow = itemIdStartIndex;
	int contLoop = 1;
	
	unsortedResult.clear();
	while (iSourceRow < sortByItemIdUserIdUnixTimeStamp.size() && contLoop) {
		if (sortByItemIdUserIdUnixTimeStamp[iSourceRow].ItemId != itemId) {
			contLoop = 0;
		} else {
			if (Us.find(sortByItemIdUserIdUnixTimeStamp[iSourceRow].UserId) != Us.end()) {
				unsortedResult.insert(sortByItemIdUserIdUnixTimeStamp[iSourceRow].UnixTimeStamp);
			}
			iSourceRow++;
		}
	}
	result.reserve(unsortedResult.size());
	result.clear();
	
	for (std::set<int>::const_iterator it = unsortedResult.begin(); it != unsortedResult.end(); it++) {
		result.push_back(*it);
	}
	
	sort(result.begin(), result.end());

	return result;
}
