// File name: b04902023_HW3_NonogramPuzzle.cpp
// Define NonogramPuzzle class functions
// Source:
//     b04902023_HW2_NonogramPuzzle.h

// Include Header File

#include <iostream> //cout, cin
#include <vector>
#include <string>
#include <sstream>

// #include <cctype> // isdigit
// #include <cstdio> // sscanf


#include "b04902023_HW3_NonogramPuzzle.h"

// constructor
NonogramPuzzle::NonogramPuzzle() {
    nRow = 0;
    nColumn = 0;
    row.clear();
    column.clear();
}
void NonogramPuzzle::clear_and_resize(int m, int n) {
    nRow = m;
    nColumn = n;
    row.reserve(m);
    row.clear();
    column.reserve(n);
    column.clear();
}
int NonogramPuzzle::rowCount() const {
    return nRow;
}
int NonogramPuzzle::columnCount() const {
    return nColumn;
}

// destructor
NonogramPuzzle::~NonogramPuzzle() {
    // do nothing because all the destructor is written in STL vector
}

std::istream & operator >> (std::istream & input, NonogramPuzzle & puzzle) {
    std::string oneLineInputBufferString;
    std::stringstream oneLineInputBufferStringstream;

    std::getline(input, oneLineInputBufferString, '\n');
    oneLineInputBufferStringstream.str("");
    oneLineInputBufferStringstream.clear(); // very inportant (to clear)
    oneLineInputBufferStringstream << oneLineInputBufferString;
    
    int m, n;
    oneLineInputBufferStringstream >> std::skipws >> m >> n;
    
    puzzle.nRow = m;
    puzzle.nColumn = n;
    puzzle.row.reserve(m);
    puzzle.column.reserve(n);
    
    for (int i = 0; i < m; i++) {
        std::getline(input, oneLineInputBufferString, '\n');
        oneLineInputBufferStringstream.str("");
        oneLineInputBufferStringstream.clear(); // very inportant (to clear)
        oneLineInputBufferStringstream << oneLineInputBufferString;
        
        std::vector<int> tmpVector;
        int tmpParsedInteger;
        tmpVector.clear();
        while (oneLineInputBufferStringstream >> tmpParsedInteger) {
            tmpVector.push_back(tmpParsedInteger);
        }
        puzzle.row.push_back(tmpVector);
    }
    for (int i = 0; i < n; i++) {
        std::getline(input, oneLineInputBufferString, '\n');
        oneLineInputBufferStringstream.str("");
        oneLineInputBufferStringstream.clear(); // very inportant (to clear)
        oneLineInputBufferStringstream << oneLineInputBufferString;
        
        std::vector<int> tmpVector;
        int tmpParsedInteger;
        tmpVector.clear();
        while (oneLineInputBufferStringstream >> tmpParsedInteger) {
            tmpVector.push_back(tmpParsedInteger);
        }
        puzzle.column.push_back(tmpVector);
    }
    return input;
}

std::ostream & operator << (std::ostream & output, const NonogramPuzzle & puzzle) {
    int m, n;
    m = puzzle.nRow;
    n = puzzle.nColumn;
    output << m << ' ' << n << "\n";
    for (int i = 0; i < m; i++) {
        for (unsigned int j = 0; j < puzzle.row[i].size(); j++) {
            output << puzzle.row[i][j];
            if (j != puzzle.row[i].size() - 1) {
                output << ' ';
            } else {
                output << "\n";
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (unsigned int j = 0; j < puzzle.column[i].size(); j++) {
            output << puzzle.column[i][j];
            if (j != puzzle.column[i].size() - 1) {
                output << ' ';
            } else {
                output << "\n";
            }
        }
    }
    return output;
}
bool operator == (const NonogramPuzzle & puzzle1, const NonogramPuzzle & puzzle2) {
    if ((puzzle1.nRow == puzzle2.nRow) &&
        (puzzle1.nColumn == puzzle2.nColumn) &&
        (puzzle1.row == puzzle2.row) &&
        (puzzle1.column == puzzle2.column)) {
        return true;
    }
    return false;
}

/*
// constructor
NonogramPuzzle::NonogramPuzzle() {
    m = 0;
    n = 0;
    elementA = NULL;
    elementB = NULL;
}

// destructor
NonogramPuzzle::~NonogramPuzzle() {
    if (elementA != NULL) {
        delete [] elementA;
        elementA = NULL;
    }
    if (elementB != NULL) {
        delete [] elementB;
        elementB = NULL;
    }
}

// copy constructor

// assignment

// overloading >> operator to use cin
std::istream & operator >> (std::istream & input, NonogramPuzzle & puzzle)
{
    // in the first line, there are two unsigned heximal integers
    // sizeof(int) * 3 * 2 + 10 is a safe size of a char array that is able to store these two integers.
    size_t safeFirstLineBufferLength = sizeof(int) * 3 * 2 + 10;
    char firstLineBuffer[safeFirstLineBufferLength];
    input.getline(firstLineBuffer, safeFirstLineBufferLength, '\n');
    // std::cout << "firstline = " << firstLineBuffer << std::endl;
    sscanf(firstLineBuffer, "%d%d", &(puzzle.m), &(puzzle.n));
    
    // now we have m and n
    // a have m rows. every line has at most ceil(n/2) elements
    // b have n rows. every line has at most ceil(m/2) elements
    // allocate memory (no error check)
    puzzle.elementA = new int[puzzle.m * puzzle.n];
    puzzle.elementB = new int[puzzle.n * puzzle.m];
    
    // clear memory
    for (int i = 0; i < puzzle.m * puzzle.n; i++) {
        puzzle.elementA[i] = 0;
        puzzle.elementB[i] = 0;
    }
    
    // read a
    // to avoid using std::string, allocate line buffer manually.
    // no error check
    // the size is able to store puzzle.n integers
    size_t safeNewLineBufferForReadingPuzzleElementALength = sizeof(int) * 3 * (puzzle.n + puzzle.m) + 10;
    char * newLineBufferForReadingPuzzleElementA = new char [safeNewLineBufferForReadingPuzzleElementALength];
    // i is the row number that start from 0
    // j is the column number that    
    // a have m rows. every line has at most ceil(n/2) elements
    for (int i = 0; i < puzzle.m; i++) {
        input.getline(newLineBufferForReadingPuzzleElementA, safeNewLineBufferForReadingPuzzleElementALength, '\n');
     //   std::cout << "in = " << newLineBufferForReadingPuzzleElementA << std::endl;
        // parsing the string
        int j = 0;
        int helpParseElementAState = 0; //state 0: wait for digit, state 1: wait for space
        for (int helpParseElementA = 0; newLineBufferForReadingPuzzleElementA[helpParseElementA] != '\0'; helpParseElementA++) {
            if (helpParseElementAState == 0) {
                // wait for digit
                if (isdigit(newLineBufferForReadingPuzzleElementA[helpParseElementA])) {
                    sscanf(newLineBufferForReadingPuzzleElementA + helpParseElementA, "%d", &(puzzle.elementA[i * puzzle.n + j]));
                    j++;
                    helpParseElementAState = 1;
                }
            } else {
                // wait for space
                if (!isdigit(newLineBufferForReadingPuzzleElementA[helpParseElementA])) {
                    helpParseElementAState = 0;
                }
            }
        }
    };
    delete [] newLineBufferForReadingPuzzleElementA;
    
    // read b
    // to avoid using std::string, allocate line buffer manually.
    // no error check
    // the size is able to store puzzle.n integers
    size_t safeNewLineBufferForReadingPuzzleElementBLength = sizeof(int) * 3 * (puzzle.n + puzzle.m) + 10;
    char * newLineBufferForReadingPuzzleElementB = new char [safeNewLineBufferForReadingPuzzleElementBLength];
    // i is the row number that start from 0
    // j is the column number that start from 0   
    // b have n rows. every line has at most ceil(m/2) elements
    for (int i = 0; i < puzzle.n; i++) {
        input.getline(newLineBufferForReadingPuzzleElementB, safeNewLineBufferForReadingPuzzleElementBLength, '\n');
//        std::getline(input, newLineBufferForReadingPuzzleElementB);
        // parsing the string
        int j = 0;
        int helpParseElementBState = 0; //state 0: wait for digit, state 1: wait for space
        for (int helpParseElementB = 0; newLineBufferForReadingPuzzleElementB[helpParseElementB] != '\0'; helpParseElementB++) {
            if (helpParseElementBState == 0) {
                // wait for digit
                if (isdigit(newLineBufferForReadingPuzzleElementB[helpParseElementB])) {
                    sscanf(newLineBufferForReadingPuzzleElementB + helpParseElementB, "%d", &(puzzle.elementB[i * puzzle.m + j]));
                    j++;
                    helpParseElementBState = 1;
                }
            } else {
                // wait for space
                if (!isdigit(newLineBufferForReadingPuzzleElementB[helpParseElementB])) {
                    helpParseElementBState = 0;
                }
            }
        }
    };
    delete [] newLineBufferForReadingPuzzleElementB;
    
    return input;
}

// overloading << operator to use cout
std::ostream & operator << (std::ostream & output, const NonogramPuzzle & puzzle)
{
    output << puzzle.m << ' ' << puzzle.n << std::endl;
    for (int i = 0; i < puzzle.m; i++) {
        for (int j = 0; puzzle.elementA[i * puzzle.n + j] != 0; j++) {
            if (j > 0) {
                output << ' ';
            }
            output << puzzle.elementA[i * puzzle.n + j];
        }
        output << std::endl;
    }
    for (int i = 0; i < puzzle.n; i++) {
        for (int j = 0; puzzle.elementB[i * puzzle.m + j] != 0; j++) {
            if (j > 0) {
                output << ' ';
            }
            output << puzzle.elementB[i * puzzle.m + j];
        }
        output << std::endl;
    }
    return output;
}

int NonogramPuzzle::a(int row, int ith) {
    return elementA[(row-1) * n + (ith-1)];
}
int NonogramPuzzle::b(int column, int ith) {
    return elementB[(column-1) * m + (ith-1)];
}
*/
