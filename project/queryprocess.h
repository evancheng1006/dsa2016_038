#ifndef QUERYPROCESS_H
#define QUERYPROCESS_H

#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <cctype>

#include "longword.h"
#include "database.h"

typedef struct wORDFREQPAIR {
	LONGWORD w;
	uint32_t f;
} WORDFREQPAIR;

inline bool operator < (const WORDFREQPAIR & lhs, const WORDFREQPAIR & rhs) {
	// strange operator
	if (lhs.f > rhs.f) {
		return true;
	} else if (lhs.f == rhs.f) {
		if (strcmp(lhs.w.c, rhs.w.c) < 0) {
			return true;
		}
	}
	return false;
}

void GenerateCandidateSet(const LONGWORD & query, std::vector<LONGWORD> & candidateSet);
void SingleQueryProcess(const LONGWORD & word, std::ostream & output, DATABASE & db);
void QueryProcess(std::istream & input, std::ostream & output, DATABASE & db);

static const char PREP [20][8] = {
	"of", "to", "in", "for", "with",
	"on", "at", "by", "from", "up",
	"about", "than", "after", "before", "down",
	"between", "under", "since", "without", "near"
};
#endif
