#include "database.h"
#include <iostream>
#include <cstdint> // cstdint since c++11


DATABASE::DATABASE() {
	
}
DATABASE::~DATABASE() {

}
void DATABASE::insert(const LONGWORD & word, uint32_t freq) {
	all[word] = freq;
	return;
}
uint32_t DATABASE::getFreq(const LONGWORD & word) {
	auto it = all.find(word);
	if (it == all.end()) {
		return 0;
	}
	return it->second;
}
