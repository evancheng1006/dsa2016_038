#include "queryprocess.h"

#include <list>
#include <cstring>
#include <algorithm>

inline void combine(LONGWORD & result, const std::vector<LONGWORD> & shortWords) {
	if (shortWords.size() == 0) {
		result.c[0] = '\0';
		return;
	}
	result.c[0] = '\0';
	for (unsigned int i = 0; i < shortWords.size(); i++) {
		// only combine non-empty strings
		if (shortWords[i].c[0] != '\0') {
			if (result.c[0] != '\0') {
				// not the first word
				strcat(result.c, " ");
			}
			strcat(result.c, shortWords[i].c);
		}
	}
	return;
}
inline void split(const LONGWORD & query, std::vector<LONGWORD> & shortWords) {
	LONGWORD tmpWord;
	unsigned int tmpWordChar = 0;
	for (unsigned int i = 0; i < MAXWORD && query.c[i] != '\0'; i++) {
		if (isblank(query.c[i])) {
			shortWords.push_back(tmpWord);
			tmpWord.c[0] = '\0';
			tmpWordChar = 0;
		} else {
			tmpWord.c[tmpWordChar] = query.c[i];
			tmpWordChar++;
			tmpWord.c[tmpWordChar] = '\0';
		}
	}
	if (tmpWord.c[0] != '\0') {
		shortWords.push_back(tmpWord);
	}
	return;
}
inline void GeneratePrepEditSet(const std::vector<LONGWORD> & prep, std::vector<LONGWORD> & edit) {
	edit.clear();
	unsigned int nPrep = prep.size();

	LONGWORD tmp;
	// self is not needed because it already exist in substitution
//	combine(tmp, prep);
//	edit.push_back(tmp);

	std::vector<LONGWORD> tmpBeforeCombine;

	// insert
	for (unsigned int iPrep = 0; iPrep <= nPrep; iPrep++) {
		tmpBeforeCombine.clear();
		for (unsigned int jPrep = 0; jPrep < iPrep; jPrep++) {
			tmpBeforeCombine.push_back(prep[jPrep]);
		}
		tmpBeforeCombine.push_back(prep[0]);// push anything here is fine...
		for (unsigned int jPrep = iPrep; jPrep < nPrep; jPrep++) {
			tmpBeforeCombine.push_back(prep[jPrep]);
		}
		for (unsigned int i = 0; i < 20; i++) {
			strcpy(tmpBeforeCombine[iPrep].c, PREP[i]);
			combine(tmp, tmpBeforeCombine);
			edit.push_back(tmp);
		}	
	}
	// delete
	// there my be an empty string, but we should still keep that empty string	
	for (unsigned int iPrep = 0; iPrep < nPrep; iPrep++) {
		tmpBeforeCombine.clear();
		for (unsigned int jPrep = 0; jPrep < nPrep; jPrep++) {
			if (jPrep != iPrep) {
				tmpBeforeCombine.push_back(prep[jPrep]);
			}
		}
		combine(tmp, tmpBeforeCombine);
		edit.push_back(tmp);
	}
	// substitude	
	for (unsigned int iPrep = 0; iPrep < nPrep; iPrep++) {
		tmpBeforeCombine = prep;
		for (unsigned int i = 0; i < 20; i++) {
			strcpy(tmpBeforeCombine[iPrep].c, PREP[i]);
			combine(tmp, tmpBeforeCombine);
			edit.push_back(tmp);
		}
	}

	return;
}
void GenerateCandidateSet(const LONGWORD & query, std::vector<LONGWORD> & candidateSet) {
	candidateSet.clear();
	candidateSet.push_back(query);

	// split
	std::vector<LONGWORD> shortWords;
	split(query, shortWords);
	// find preps
	std::vector<int> isPrep;
	int nPrep = 0;
	for (unsigned int i = 0; i < shortWords.size(); i++) {
		int tmpIsPrep = 0;
		for (int iPrep = 0; iPrep < 20; iPrep++) {
			if (!strcmp(shortWords[i].c, PREP[iPrep])) {
				tmpIsPrep = 1;
			}
		}
		isPrep.push_back(tmpIsPrep);
	}
	nPrep = 0;
	for (unsigned int i = 0; i < isPrep.size(); i++) {
		if (isPrep[i]) {
			nPrep++;	
		}
	}
#if DEBUG==1
	for (unsigned int i = 0; i < shortWords.size(); i++) {
		std::cout << shortWords[i].c << '\t' << strlen(shortWords[i].c) << '\t' << isPrep[i] << '\n';
	}
	std::cout << nPrep << '\n';
#endif
	// insert, delete, substitude
	// nPrep = 0: can insert anywhere (from index 0 to shortWords.size())
	if (nPrep == 0) {
		std::vector<LONGWORD> tmpOutputShortWords;
		LONGWORD tmpOutputWord;

		// insertOne
		for (unsigned int insertPlace = 0; insertPlace <= shortWords.size(); insertPlace++) {
			tmpOutputShortWords.clear();
			for (unsigned int iPlace = 0; iPlace < insertPlace; iPlace++) {
				tmpOutputShortWords.push_back(shortWords[iPlace]);
			}
			tmpOutputShortWords.push_back(shortWords[0]); // prep
			for (unsigned int iPlace = insertPlace; iPlace < shortWords.size(); iPlace++) {
				tmpOutputShortWords.push_back(shortWords[iPlace]);
			}
			for (unsigned int iPrep = 0; iPrep < 20; iPrep++) {
				strcpy(tmpOutputShortWords[insertPlace].c, PREP[iPrep]);
				combine(tmpOutputWord, tmpOutputShortWords);
				candidateSet.push_back(tmpOutputWord);
			}	
		}
		// insertTwo
		tmpOutputShortWords.resize(shortWords.size() + 2);
		for (unsigned int iNewPlace = 0; iNewPlace <= shortWords.size(); iNewPlace++) {
			for (unsigned int jNewPlace = iNewPlace + 1; jNewPlace <= shortWords.size() + 1; jNewPlace++) {
				// put other words
				unsigned int shortWordsIndex = 0;
				for (unsigned int i = 0; i <= shortWords.size() + 1; i++) {
					if (i != iNewPlace && i != jNewPlace) {
						strcpy(tmpOutputShortWords[i].c, shortWords[shortWordsIndex].c);
						shortWordsIndex++;
					}
				}

				// scan 400 possibilities
				for (unsigned int iPrep = 0; iPrep < 20; iPrep++) {
					strcpy(tmpOutputShortWords[iNewPlace].c, PREP[iPrep]);
					for (unsigned int jPrep = 0; jPrep < 20; jPrep++) {
						strcpy(tmpOutputShortWords[jNewPlace].c, PREP[jPrep]);
						combine(tmpOutputWord, tmpOutputShortWords);
						candidateSet.push_back(tmpOutputWord);
					}
				}	
			}
		}


	} else {
		// combine mixed.size() words
		std::vector<std::vector<LONGWORD> > mixed;

		// seperate prep and non-prep
		// combine all non-prep and generate edit set for preposition
		int prevType = isPrep[0];
		std::vector<LONGWORD> tmpSameType;
		std::vector<LONGWORD> tmpEditSet;
		// non-prep: tmpEditSet.size() == 1
		for (unsigned int i = 0; i < shortWords.size(); i++) {
			if (isPrep[i] != prevType) {
				if (prevType == 0) {
					LONGWORD combinedNonPrep;
					combine(combinedNonPrep, tmpSameType);
					tmpEditSet.clear();
					tmpEditSet.push_back(combinedNonPrep);
					mixed.push_back(tmpEditSet);
				} else {
					GeneratePrepEditSet(tmpSameType, tmpEditSet);
					mixed.push_back(tmpEditSet);
				}
				tmpSameType.clear();
			}
			tmpSameType.push_back(shortWords[i]);
			prevType = isPrep[i];
		}
		if (prevType == 0) {
			LONGWORD combinedNonPrep;
			combine(combinedNonPrep, tmpSameType);
			tmpEditSet.clear();
			tmpEditSet.push_back(combinedNonPrep);
			mixed.push_back(tmpEditSet);
		} else {
			GeneratePrepEditSet(tmpSameType, tmpEditSet);
			mixed.push_back(tmpEditSet);
		}
#if DEBUG==1
		std::cout << "mixed size(run): " << mixed.size() << " \n";
		for (unsigned int i = 0; i < mixed.size(); i++) {
			std::cout << i << "(" << mixed[i].size() << ")"": ";
			for (unsigned int j = 0; j < mixed[i].size(); j++) {
				std::cout << mixed[i][j].c << "|";
			}
			std::cout << "\n";
		}
#endif
		std::vector<unsigned int> selector;
		selector.clear();
		unsigned int mixedSize = mixed.size();
		selector.resize(mixedSize + 1, 0); // fill all zero
		std::vector<LONGWORD> tmpBeforeCombine;
		LONGWORD tmpAfterCombine;
		tmpBeforeCombine.resize(mixedSize);
		while (selector[mixedSize] == 0) {
#if DEBUG==1
			std::cout << "select";
			for (unsigned int iDigit = 0; iDigit < mixedSize; iDigit++) {
				std::cout << ' ' << selector[iDigit];
			}
			std::cout << '\n';
#endif
			for (unsigned int iDigit = 0; iDigit < mixedSize; iDigit++) {
				strcpy(tmpBeforeCombine[iDigit].c, (mixed[iDigit][(selector[iDigit])]).c);
			}
			combine(tmpAfterCombine, tmpBeforeCombine);
#if DEBUG==1
			std::cout << tmpAfterCombine.c << "\n";
#endif
			candidateSet.push_back(tmpAfterCombine);
			// refresh selector
			selector[0]++;
			for (unsigned int iDigit = 0; iDigit < mixedSize; iDigit++) {
				if (selector[iDigit] >= mixed[iDigit].size()) {
					selector[iDigit] = 0;
					selector[iDigit + 1]++;
				}
			}
		}

	}
	return;
}

void SingleQueryProcess(const LONGWORD & query, std::vector<WORDFREQPAIR> & result, DATABASE & db) {
	static const unsigned int topNQuery = 10;
//	since topNQuery is small, there is no need to build a search tree
//	Just Simple Vector, with insert time complexity O(topNQuery)
//	we have to filter same request if the request is already existed in the top queries
	std::vector<LONGWORD> candidateSet;
	GenerateCandidateSet(query, candidateSet);
	
	result.clear();
	unsigned int candidateSetSize = candidateSet.size();
	WORDFREQPAIR tmp;
	for (unsigned int i = 0; i < candidateSetSize; i++) {
		tmp.w = candidateSet[i];
		tmp.f = db.getFreq(tmp.w);
		if (tmp.f != 0) {
			// if there is an existed query, then ignore it
			int isANewQuery = 1;
			for (unsigned int cmp = 0; cmp < result.size(); cmp++) {
				if (!strcmp(tmp.w.c, result[cmp].w.c)) {
					isANewQuery = 0;
				}
			}
			if (isANewQuery) {
				// insert and compare
				result.push_back(tmp);
				for (unsigned int cmp = result.size() - 1; cmp > 0; cmp--) {
					if (result[cmp].f > result[cmp - 1].f) {
						// swap
						WORDFREQPAIR tmpswap = result[cmp - 1];
						result[cmp - 1] = result[cmp];
						result[cmp] = tmpswap;
					}
				}
				if (result.size() > topNQuery) {
					result.pop_back(); // to keep the size
				}
			}
		}
	}
	// dictionary order
	// use stable_sort in <algorithm>
	if (result.size() != 0) {
		stable_sort(result.begin(), result.end());
	}
	return;
}

void QueryProcess(std::istream & input, std::ostream & output, DATABASE & db) {
	LONGWORD query;
	std::vector<WORDFREQPAIR> result;
	while (input.getline(query.c, MAXWORD,'\n')){
		// '\n' will be discarded
		SingleQueryProcess(query, result, db);

		output << "query: " << query.c << '\n';
		output << "output: " << result.size() << '\n';
		for (unsigned int i = 0; i < result.size(); i++) {
			output << result[i].w.c << '\t' << result[i].f << '\n';
		}
	}
	return;
}

