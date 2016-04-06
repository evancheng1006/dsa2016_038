// File name: b04902023_HW3_NonogramImage.h
// Define NonogramImage class

// header gaurds
#ifndef B04902023_HW2_NONOGRAMIMAGE_H
#define B04902023_HW2_NONOGRAMIMAGE_H

// constants
#include "b04902023_HW3_NonogramImageConst.h"

#include <iostream> // to overload operators << and >>
#include <vector>

class NonogramImage {
    private:
        int nRow, nColumn;
    public:
        std::vector<int> array;
           
        NonogramImage(); // constructor
        NonogramImage(int m, int n); // constructor
        ~NonogramImage(); // destructor

        void clear_and_resize(int m, int n);
        int rowCount() const;
        int columnCount() const;
        
        void read_row(int rowId, std::vector<int> & vec) const;
        void read_column(int columnId, std::vector<int> & vec) const;
        int write_row(int rowId, const std::vector<int> & vec); //1: success
        int write_column(int columnId, const std::vector<int> & vec);
        
        friend std::istream & operator >> (std::istream & input, NonogramImage & image);
        friend std::ostream & operator << (std::ostream & output, const NonogramImage & puzzle);
};

// header gaurds
#endif
