#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "database.h"
#if DEBUG==1
extern void generateConfusionSetSingleWord(const std::string & str, std::vector<std::string> & result);
#endif
#if DEBUG==2
extern void generateConfusionSetWithDuplication(const std::string & str, int distance, std::vector<std::string> & result);
#endif

extern void QueryProcess(std::istream & input, DATABASE & db, std::ostream & output); 
int main() {	
	char dictionaryPath[] = "/tmp2/dsa2016_hw5/cmudict-0.7b";
	std::ifstream fin;

	fin.open(dictionaryPath);

	DATABASE db(fin);

	fin.close();

	QueryProcess(std::cin, db, std::cout);
//
#if DEBUG==1
	std::string mystr;
	std::vector<std::string> result;
	mystr = "";
	generateConfusionSetSingleWord(mystr, result);
	for (unsigned int i = 0; i < result.size(); i++) {
		std::cout << result[i] << "\n";
	}
	mystr = "j";
	generateConfusionSetSingleWord(mystr, result);
	for (unsigned int i = 0; i < result.size(); i++) {
		std::cout << result[i] << "\n";
	}
	mystr = "gj";
	generateConfusionSetSingleWord(mystr, result);
	for (unsigned int i = 0; i < result.size(); i++) {
		std::cout << result[i] << "\n";
	}
#endif
#if DEBUG==2
	std::string mystr;
	std::vector<std::string> result;
	mystr = "something";
	generateConfusionSetWithDuplication(mystr, 2, result);
	for (unsigned int i = 0; i < result.size(); i++) {
		std::cout << result[i] << "\n";
	}
#endif
	return 0;
}
