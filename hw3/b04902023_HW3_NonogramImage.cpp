// File name: b04902023_HW3_NonogramImage.cpp
// Define NonogramImage class functions
// Source:
//     b04902023_HW2_NonogramImage.h

// Include Header File

#include <iostream> //cout, cin
#include <vector>
#include <string>
#include "b04902023_HW3_NonogramImageConst.h"
#include "b04902023_HW3_NonogramImage.h"

// constructor
NonogramImage::NonogramImage() {
    nRow = 0;
    nColumn = 0;
    array.clear();
}
NonogramImage::NonogramImage(int m, int n) {
    nRow = m;
    nColumn = n;
    array.reserve(m * n);
    array.clear();
    array.resize(m * n, NONOGRAM_IMAGE_CONST_UNDETERMINED);
}
void NonogramImage::clear_and_resize(int m, int n) {
    nRow = m;
    nColumn = n;
    array.reserve(m * n);
    array.clear();
    array.resize(m * n, NONOGRAM_IMAGE_CONST_UNDETERMINED);
}
int NonogramImage::rowCount() const {
    return nRow;
}
int NonogramImage::columnCount() const {
    return nColumn;
}

// destructor
NonogramImage::~NonogramImage() {
    // do nothing
}
void NonogramImage::read_row(int rowId, std::vector<int> & vec) const {
    if (rowId >= nRow || rowId < 0) {
        vec.clear();
        return; //EMPTY
    } else {
        vec.resize(nColumn);
        for (int i = 0; i < nColumn; i++) {
            vec[i] = array[rowId * nColumn + i];
        }
    }
    return;
}
void NonogramImage::read_column(int columnId, std::vector<int> & vec) const {
    if (columnId >= nColumn || columnId < 0) {
        vec.clear();
        return; //EMPTY
    } else {
        vec.resize(nRow);
        for (int i = 0; i < nRow; i++) {
            vec[i] = array[i * nColumn + columnId];
        }
    }
    return;
}
int NonogramImage::write_row(int rowId, const std::vector<int> & vec) {
    if (rowId >= nRow || rowId < 0 || vec.size() != (unsigned int)nColumn) {
        return 0;
    }
    for (int i = 0; i < nColumn; i++) {
        array[rowId * nColumn + i] = vec[i];
    }
    return 1;
}
int NonogramImage::write_column(int columnId, const std::vector<int> & vec) {
    if (columnId >= nColumn || columnId < 0 || vec.size() != (unsigned int)nRow) {
        return 0;
    }
    for (int i = 0; i < nRow; i++) {
        array[i * nColumn + columnId] = vec[i];
    }
    return 1;
}

// overloading >> operator to use cin
std::istream & operator >> (std::istream & input, NonogramImage & image) {
    // clear image
    image.nRow = 0;
    image.nColumn = 0;
    image.array.clear();

    std::string oneLine;
    
    // input first line
    std::getline(input, oneLine);
    image.nColumn = oneLine.length();
    for (int i = 0; i < image.nColumn; i++) {
        switch (oneLine[i]) {
        case '#':
            image.array.push_back(NONOGRAM_IMAGE_CONST_SELECTED);
            break;
        case '.':
            image.array.push_back(NONOGRAM_IMAGE_CONST_UNSELECTED);
            break;
        default:
            image.array.push_back(NONOGRAM_IMAGE_CONST_UNDETERMINED);
            break;
        }
    }
    image.nRow = 1;
    
    while (std::getline(input, oneLine)) {
        image.nRow++;
        for (int i = 0; i < image.nColumn; i++) {
            switch (oneLine[i]) {
            case '#':
                image.array.push_back(NONOGRAM_IMAGE_CONST_SELECTED);
                break;
            case '.':
                image.array.push_back(NONOGRAM_IMAGE_CONST_UNSELECTED);
                break;
            default:
                image.array.push_back(NONOGRAM_IMAGE_CONST_UNDETERMINED);
                break;
            }
        }
    }
    
    return input;
}


std::ostream & operator << (std::ostream & output, const NonogramImage & puzzle) {
    for (int i = 0; i < puzzle.nRow; i++) {
        for (int j = 0; j < puzzle.nColumn; j++) {
            switch (puzzle.array[i * puzzle.nColumn + j]) {
            case NONOGRAM_IMAGE_CONST_SELECTED:
                 output << '#';
                 break;
            case NONOGRAM_IMAGE_CONST_UNSELECTED:
                 output << '.';
                 break;
            case NONOGRAM_IMAGE_CONST_UNDETERMINED:
                 output << '@';
                 break;
            default:
                 output << ' ';
                 break;
            }
        }
        output << '\n';
    }
    return output;
}


