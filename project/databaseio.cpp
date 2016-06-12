#include "database.h"
#include <iostream>
#include <fstream>
#include <cstdint>
#include <string>
#include <cctype>

std::istream & operator >> (std::istream & input, DATABASE & db) {
	std::string buffer;
	buffer.reserve(MAXWORD + 30);
	LONGWORD word;
	uint32_t freq;
	unsigned int iChar;
	while(std::getline(input, buffer)) {
		for (iChar = 0; buffer[iChar] != '\t' && iChar < MAXWORD; iChar++) {
			word.c[iChar] = buffer[iChar];
		}
		word.c[iChar] = '\0';
		iChar++;
		freq = 0;
		for (; isdigit(buffer[iChar]) && iChar < MAXWORD; iChar++) {
			freq *= 10ULL;
			freq += (buffer[iChar] - '0');
		}
		db.insert(word, freq);
	}
	return input;
}
std::ostream & operator << (std::ostream & output, const DATABASE & db) {
	output << db.all.size() << "\n";
//	for (auto i = db.all.begin(); i != db.all.end(); i++) {
//		output << i->first.c << "\t" << i->second << "\n";
//	}
	return output;
}
