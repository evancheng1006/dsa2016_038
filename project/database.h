#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <cstdint> // cstdint since c++11

#ifdef SLOW
#include <map>
#else
#endif

#include "longword.h"

class DATABASE {
public:
	DATABASE();
	~DATABASE();

	void insert(const LONGWORD & word, uint32_t freq);
	uint32_t getFreq(const LONGWORD & word);

#ifdef SLOW
	std::map<LONGWORD, uint32_t> all;
#else

#endif
private:
};


#endif
