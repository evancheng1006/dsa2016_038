// File name: b04902023_HW3.cpp
// Main file.
// Source:
//     b04902023_HW2_NonogramPuzzle.h
//     b04902023_HW2_NonogramImage.h
//     (function)b04902023_HW2_NonogramSolveAndCreatePuzzle.cpp

// Include Header File

#include <iostream>

#include "b04902023_HW3_NonogramPuzzle.h"
#include "b04902023_HW3_NonogramImage.h"

// extern functions

extern int SolvePuzzle(const NonogramPuzzle & puzzle, NonogramImage & image); // return whether there is a solution
extern void CreatePuzzle(NonogramPuzzle & puzzle, const NonogramImage & image);

// main function
int main() {
    NonogramImage img;
    NonogramPuzzle puzz;
    
    std::cin >> puzz;
//    std::cout << puzz;
    
    SolvePuzzle(puzz, img);
//    CreatePuzzle(puzz, img);

    
//    std::cin >> img;
//    std::cout << puzz;
    std::cout << img;
    NonogramPuzzle puzz2;
//    CreatePuzzle(puzz2, img);
//    std::cout << puzz2;

//    CreatePuzzle(puzz, img);
    
//    std::cout << puzz;
    
//    std::cout << puzz;
/*
    std::vector<int> manip;
    img.read_row(0, manip);
    manip[3] = NONOGRAM_IMAGE_CONST_SELECTED;
    img.write_column(2, manip);
    std::cout << img;
*/
/*
    NonogramPuzzle B = puzz;
    NonogramPuzzle C;
    C = puzz;
    std::cout << "B\n" << B;
    std::cout << "C\n" << C;
    std::cout << "Change\n";
    puzz.row[0][0] = 707;
    puzz.row[2][1] = 353;
    std::cout << "puzz\n" << puzz;
    std::cout << "B\n" << B;
    std::cout << "C\n" << C;
*/



    return 0;
}
