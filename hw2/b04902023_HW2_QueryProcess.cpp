#ifndef B04902023_HW2_QUERYPROCESS_H
#define B04902023_HW2_QUERYPROCESS_H

#include <iostream>
#include <string>
#include <sstream>

#include "b04902023_HW2_BigMatrix.h"

void SingleQueryProcess(std::istream & input, BigMatrix & matrix ,std::ostream & output) {
	std::string functionName;
	std::string numberBuffer;
	std::stringstream integersInOneLineString;
	std::vector<int> integersInOneLineInt;

	std::getline(input, functionName);
	std::getline(input, numberBuffer);

	integersInOneLineString << numberBuffer;
	
	int tmpParsedInteger;
	integersInOneLineInt.clear();
	while (integersInOneLineString >> tmpParsedInteger) {
		integersInOneLineInt.push_back(tmpParsedInteger);
	}

	if (functionName == "accept") {
		int u = integersInOneLineInt[0];
		int i = integersInOneLineInt[1];
		int t = integersInOneLineInt[2];
		int response = matrix.accept(u, i, t);
		output << response << std::endl;
	} else if (functionName == "items") {
		int u1 = integersInOneLineInt[0];
		int u2 = integersInOneLineInt[1];
		std::vector<int> response = matrix.items(u1, u2);

		if (response.size() == 0) {
			output << "EMPTY" << std::endl;
		} else {
			for (std::vector<int>::const_iterator it = response.begin(); it != response.end(); it++) {
				output << *it << std::endl;
			}
		}
	} else if (functionName == "users") {
		int i1 = integersInOneLineInt[0];
		int i2 = integersInOneLineInt[1];
		int t1 = integersInOneLineInt[2];
		int t2 = integersInOneLineInt[3];
		std::vector<int> response = matrix.users(i1, i2, t1, t2);

		if (response.size() == 0) {
			output << "EMPTY" << std::endl;
		} else {
			for (std::vector<int>::const_iterator it = response.begin(); it != response.end(); it++) {
				output << *it << std::endl;
			}
		}
	} else if (functionName == "ratio") {
		int i = integersInOneLineInt[0];
		int threshold = integersInOneLineInt[1];
		std::vector<int> response = matrix.ratio(i, threshold);
		output << response[0] << '/' << response[1] << std::endl;
	} else if (functionName == "findtime_item") {
		std::set<int> Us;
		Us.clear();
		int itemId = integersInOneLineInt[0];
		for (int i = 1; i < integersInOneLineInt.size(); i++) {
			Us.insert(integersInOneLineInt[i]);
		}

		std::vector<int> response = matrix.findtime_item(itemId, Us);

		if (response.size() == 0) {
			output << "EMPTY" << std::endl;
		} else {
			for (std::vector<int>::const_iterator it = response.begin(); it != response.end(); it++) {
				output << *it << std::endl;
			}
		}
	} else {
	}
/*
	for (int i = 0; i < integersInOneLineInt.size(); i++) {
		output << integersInOneLineInt[i] << ' ';
	}
	output << integersInOneLineInt.size() << std::endl;
*/
}
void QueryProcess(std::istream & input, BigMatrix & matrix ,std::ostream & output) {
	int n;
	std::string firstLine;
	std::stringstream integersInOneLineString;

	std::getline(input, firstLine);
	integersInOneLineString << firstLine;
	integersInOneLineString >> n;

	for (int i = 0; i < n; i++) {
		SingleQueryProcess(input, matrix, output);
	}
}

#endif
