#include <iostream>
#include <cctype>
#include <algorithm>
#include <string>
#include <vector>
#include "database.h"

void generateConfusionSetSingleWord(const std::string & str, std::vector<std::string> & result) {
	result.clear();
	result.push_back(str);
	unsigned int len = str.length();
	std::string tmp;
	// Insert
	for (unsigned int insertPlace = 0; insertPlace <= len; insertPlace++) {
		for (char insertChar = 'a'; insertChar <= 'z'; insertChar++) {
			tmp.clear();
			for (unsigned int i = 0; i < insertPlace; i++) {
				tmp.push_back(str[i]);
			}
			tmp.push_back(insertChar);
			for (unsigned int i = insertPlace; i < len; i++) {
				tmp.push_back(str[i]);
			}
			result.push_back(tmp);
		}
	}
	// Delete
	if (len > 0) {
		for (unsigned int deletePlace = 0; deletePlace < len; deletePlace++) {
			tmp.clear();
			for (unsigned int i = 0; i < len; i++) {
				if (i != deletePlace) {
					tmp.push_back(str[i]);
				}
			}
			result.push_back(tmp);
		}
	}
	// Subsitute
	for (unsigned int substitudePlace = 0; substitudePlace < len; substitudePlace++) {
		for (char substitudeChar = 'a'; substitudeChar <= 'z'; substitudeChar++) {
			tmp = str;
			tmp[substitudePlace] = substitudeChar;
			result.push_back(tmp);
		}
	}
	// Transpose
	if (len > 1) {
		for (unsigned int transPlace = 1; transPlace < len; transPlace++) {
			tmp = str;
			char tmpChar;
			tmpChar = tmp[transPlace];
			tmp[transPlace] = tmp[transPlace - 1];
			tmp[transPlace - 1] = tmpChar;
			result.push_back(tmp);
		}
	}
}

void generateConfusionSetWithDuplication(const std::string & str, int distance, std::vector<std::string> & result) {
	result.clear();
	result.push_back(str);
	for (int i = 0; i < distance; i++) {
		unsigned int currentSize = result.size();
		std::vector<std::string> tmp;
		for (unsigned int j = 0; j < currentSize; j++) {
			generateConfusionSetSingleWord(result[j], tmp);
			// add result
			result.insert(result.end(), tmp.begin(), tmp.end());
		}
	}
}

void QueryProcess(std::istream & input, DATABASE & db, std::ostream & output) {
	std::string buffer;
	std::string word;
	std::string originalWord;

	while (std::getline(input, buffer)) {
		word.clear();
		originalWord.clear();
		unsigned int len = buffer.length();

		// get first word
		for (unsigned int i = 0; i < len; i++) {
			if (!isblank(buffer[i])) {
				originalWord.push_back(buffer[i]);
//				word.push_back(tolower(buffer[i]));
				word.push_back(buffer[i]);
			} else {
				i = len; //end loop
			}
		}

		std::cout << originalWord << " ==>";
		if (db.exist(word)) {
			std::cout << " OK\n";
		} else {
			// generate confusion set if not OK
			// this operation does not remove duplication
			std::vector<std::string> confusion;
			generateConfusionSetWithDuplication(word, 2, confusion);

			std::vector<std::string> outWord;
			for (unsigned int i = 0; i < confusion.size(); i++) {
				if (db.exist(confusion[i])) {
					outWord.push_back(confusion[i]);
				}
			}
			if (outWord.empty()) {
				std::cout << " NONE\n";
			} else {
				sort(outWord.begin(), outWord.end());
				unsigned int currentEnd = 0;
				std::string prev = outWord[0];
				for (unsigned int i = 1; i < outWord.size(); i++) {
					if (outWord[i] != prev) {
						currentEnd++;
						outWord[currentEnd] = outWord[i];
						prev = outWord[i];
					}
				}
				outWord.resize(currentEnd + 1);

				for (unsigned int i = 0; i <= currentEnd; i++) {
					std::cout << ' ' << outWord[i];
				}
				std::cout << "\n";
			}
		}
		
	}
	return;
}
