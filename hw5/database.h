#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <cctype>
#include <string>
#include <set>

class DATABASE {
	private:
		std::set<std::string> realWord;
	public:
		inline DATABASE(std::istream & input);
		inline int exist(const std::string & word);
};

inline DATABASE::DATABASE(std::istream & input) {
	realWord.clear();
	std::string buffer;
	std::string word;
	while (std::getline(input, buffer)) {
		word.clear();
		unsigned int len = buffer.length();

		// get first word
		for (unsigned int i = 0; i < len; i++) {
			if (!isblank(buffer[i])) {
				word.push_back(tolower(buffer[i]));
			} else {
				i = len; //end loop
			}
		}
		realWord.insert(word);
	}
}
inline int DATABASE::exist(const std::string & word) {
	if (realWord.find(word) != realWord.end()) {
		return 1;
	}
	return 0;
}

#endif
