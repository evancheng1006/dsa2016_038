// File name: b04902023_HW3_NonogramPuzzle.h
// Define NonogramPuzzle class

// Maze traversal
//
// In this homework, you need to write a program to solve the game of nonogram. More info about the game can be found at Wikipedia (English, Chinese). You can also google "nonogram" or "picross" to find interactive pages to play the game, such as this one.
//
// Write a program to output the map based on the input criteria. The input has the following format:
//
//
// m n ¡ö The numbers of rows and columns of the bit map (matrix)
// a11 a12 . . . . . .  ¡ö lengths of unbroken lines in row 1
// a21 a22 . . . . . .  ¡ö lengths of unbroken lines in row 2
// .
// .
// .
// am1 am2 . . . . . .  ¡ö lengths of unbroken lines in row m
// b11 b12 . . . . . .  ¡ö lengths of unbroken lines in column 1
// b21 b22 . . . . . .  ¡ö lengths of unbroken lines in column 2
// .
// .
// .
// bn1 bn2 . . . . . .  ¡ö lengths of unbroken lines in column n
// Here are some example of nonograms:





// header gaurds
#ifndef B04902023_HW3_NONOGRAMPUZZLE_H
#define B04902023_HW3_NONOGRAMPUZZLE_H

#include <vector>
#include <iostream> // to overload operators << and >>

/*
// index of the elements start from 1
class NonogramPuzzle {
    private:
//        int m, n;
//        int * elementA;
//        int * elementB;
        // in order to access the element faster, make all member variables visible so that easy to access.
    public:
        int m, n;
        int * elementA;
        int * elementB;
           
        NonogramPuzzle(); // constructor
        ~NonogramPuzzle(); // destructor
        friend std::istream & operator >> (std::istream & input, NonogramPuzzle & image);
        friend std::ostream & operator << (std::ostream & output, const NonogramPuzzle & puzzle);
        int a(int row, int ith);    // access elements (slow)
        int b(int column, int ith); // access elements (slow)
};
*/

class NonogramPuzzle {
    private:
        int nRow, nColumn;
        //m: number of rows
        //n: number of columns
        // in order to access the element faster, make all member variables visible so that easy to access.
    public:
        std::vector<std::vector<int> > row;
        std::vector<std::vector<int> > column;
        
        void clear_and_resize(int m, int n);
        int rowCount() const;
        int columnCount() const;
        
        // no need design copy consturctor and assignment operator
        NonogramPuzzle(); // constructor
        ~NonogramPuzzle(); // destructor
        friend std::istream & operator >> (std::istream & input, NonogramPuzzle & image);
        friend std::ostream & operator << (std::ostream & output, const NonogramPuzzle & puzzle);
        friend bool operator == (const NonogramPuzzle & puzzle1, const NonogramPuzzle & puzzle2);
};


// header gaurds
#endif
