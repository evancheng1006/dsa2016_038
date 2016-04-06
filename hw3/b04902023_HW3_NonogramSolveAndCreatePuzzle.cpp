// File name: b04902023_HW3_NonogramSolveAndCreatePuzzle.cpp
// Main algorithm file.
// Source:
//     b04902023_HW3_NonogramPuzzle.h
//     b04902023_HW3_NonogramImage.h

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>

#include <stack>
#include <queue>


#include "b04902023_HW3_NonogramPuzzle.h"
#include "b04902023_HW3_NonogramImage.h"

#define DEBUG 0

// This function solves a nonogram puzzle
// Input : NonogramPuzzle
// Output: NonogramImage

static int ImageSingleRowToPuzzleSingleRow(const std::vector<int> & imageSingleRow, std::vector<int> & puzzleSingleRow) {
    // return value: 1: all determined, 0: not all determined
    int length = imageSingleRow.size();
    int isAllDetermined = 1;
    
    int prev = NONOGRAM_IMAGE_CONST_UNSELECTED;
    int contSelected = 0;
    
    puzzleSingleRow.clear();
    
    // find continous NONOGRAM_IMAGE_CONST_SELECTED
    for (int i = 0; i < length; i++) {
        switch (imageSingleRow[i]) {
        case NONOGRAM_IMAGE_CONST_SELECTED:
            contSelected++;
            break;
        case NONOGRAM_IMAGE_CONST_UNSELECTED:
            if (prev == NONOGRAM_IMAGE_CONST_SELECTED) {
                puzzleSingleRow.push_back(contSelected);
                contSelected = 0;
            }
            break;
        default:
            if (prev == NONOGRAM_IMAGE_CONST_SELECTED) {
                puzzleSingleRow.push_back(contSelected);
                contSelected = 0;
            }
            isAllDetermined = 0;
            break;
        }
        prev = imageSingleRow[i];
    }
    if (prev == NONOGRAM_IMAGE_CONST_SELECTED) {
        puzzleSingleRow.push_back(contSelected);
        contSelected = 0;
    }
    
    return isAllDetermined;
}

// This function creates a nonogram puzzle.
// Input : NonogramImage
// Output: NonogramPuzzle
void CreatePuzzle(NonogramPuzzle & puzzle, const NonogramImage & image) {
    puzzle.clear_and_resize(image.rowCount(), image.columnCount());
    int nRow = image.rowCount();
    int nColumn = image.columnCount();
    
    std::vector<int> imageLine;
    std::vector<int> puzzleLine;
    
    puzzle.row.clear();
    puzzle.column.clear();
    
    for (int i = 0; i < nRow; i++) {
        image.read_row(i, imageLine);
        ImageSingleRowToPuzzleSingleRow(imageLine, puzzleLine);
        puzzle.row.push_back(puzzleLine);
    }
    for (int i = 0; i < nColumn; i++) {
        image.read_column(i, imageLine);
        ImageSingleRowToPuzzleSingleRow(imageLine, puzzleLine);
        puzzle.column.push_back(puzzleLine);
    }
}

inline static int FindFirstUndetermined(NonogramImage & image) {
    // find first undetermined
    int firstUndetermined = -1;
    int imageSize = image.rowCount() * image.columnCount();
   
    for (int i = 0; i < imageSize && firstUndetermined == -1; i++) {
        if ((image.array[i] != NONOGRAM_IMAGE_CONST_UNSELECTED) && (image.array[i] != NONOGRAM_IMAGE_CONST_SELECTED)) {
            firstUndetermined = i;
        }
    }
    return firstUndetermined;
}

static void ImageStackMakeBranch(std::stack<NonogramImage> & imageStack) {
    if (imageStack.empty()) {
        return;
    }
    NonogramImage image = imageStack.top();
    int firstUndetermined = FindFirstUndetermined(image);
    
    if (firstUndetermined == -1) {
        // no branch, remove
        imageStack.pop();
        return;
    }
    
    // make two new branch
    NonogramImage image2 = image;
    image.array[firstUndetermined] = NONOGRAM_IMAGE_CONST_SELECTED;
    image2.array[firstUndetermined] = NONOGRAM_IMAGE_CONST_UNSELECTED;
    
    imageStack.pop(); // remove old
    imageStack.push(image2);
    imageStack.push(image);
    
    return;
}

// inline static int LogicSolveSingleBrick(const std::vector<int> & puzzleSingleRow, std::vector<int> & imageSingleRow, int brickId) {
// 
//    return NONOGRAM_IMAGE_LOGIC_SOLVE_SINGLE_BRICK_CONST_UNDETERMINED;
//}

inline static int PushBrickToTheHead(std::vector<int> & tmpImageSingleRow, int brickSize, int indexLowerBound) {
    // return value: the smallest index that the next brick can be placed. (new index lower bound)
    // find pattern : (UNDETERMINED/SELECTED) * n + (UNDETERMINED/UNSELECTED)
    
    // for convenience, push one undetermined into tmpImageSingleRow

#if DEBUG == 1
    std::cout << "PUSHBRICKTOTHEHEAD\n";
    std::cout << "tmpImageSingleRow:\n";
    for (unsigned int i = 0; i < tmpImageSingleRow.size(); i++) {
        switch (tmpImageSingleRow[i]) {
        case NONOGRAM_IMAGE_CONST_SELECTED:       std::cout << '#'; break;
        case NONOGRAM_IMAGE_CONST_UNSELECTED: std::cout << '.'; break;
        default:                                          std::cout << '@'; break;
        }
    }
    std::cout << "\n";
    std::cout << "brickSize: " << brickSize << "\n";
    std::cout << "indexLowerBound: " << indexLowerBound << "\n";
#endif
    unsigned int indexUpperBound = tmpImageSingleRow.size() - brickSize;
    
    tmpImageSingleRow.push_back(NONOGRAM_IMAGE_CONST_UNDETERMINED);
    
    unsigned int thisBrickValidIndexLowerBound = indexLowerBound;
    
    int contInPattern = 0;
    while (thisBrickValidIndexLowerBound <= indexUpperBound) {
        contInPattern = 0;
        for (int j = 0; j <= brickSize; j++) {
            if (j < brickSize) {
                if (tmpImageSingleRow[thisBrickValidIndexLowerBound + j] != NONOGRAM_IMAGE_CONST_UNSELECTED) {
                    contInPattern++;
                } else {
                    contInPattern = 0;
                }
            } else {
                if (tmpImageSingleRow[thisBrickValidIndexLowerBound + j] != NONOGRAM_IMAGE_CONST_SELECTED) {
                    contInPattern++;
                } else {
                    contInPattern = 0;
                }
            }
        }
        if (contInPattern > brickSize)
            break;
        thisBrickValidIndexLowerBound++;
    }

    tmpImageSingleRow.pop_back(); // recover
    
    int nextBrickIndexLowerBound = thisBrickValidIndexLowerBound + brickSize + 1;
    
    
    if (thisBrickValidIndexLowerBound > indexUpperBound) {
        return tmpImageSingleRow.size() * 5 + 3; // contradict
    }
    for (int i = 0; i < brickSize; i++) {
        tmpImageSingleRow[thisBrickValidIndexLowerBound + i] = NONOGRAM_IMAGE_CONST_SELECTED;
    }
#if DEBUG == 1
    std::cout << "After push\n";
    std::cout << "tmpImageSingleRow:\n";
    for (unsigned int i = 0; i < tmpImageSingleRow.size(); i++) {
        switch (tmpImageSingleRow[i]) {
        case NONOGRAM_IMAGE_CONST_SELECTED:       std::cout << '#'; break;
        case NONOGRAM_IMAGE_CONST_UNSELECTED: std::cout << '.'; break;
        default:                                          std::cout << '@'; break;
        }
    }
    std::cout << "\n";
    std::cout << "nextBrickIndexLowerBound = " << nextBrickIndexLowerBound << "\n";
#endif
    return nextBrickIndexLowerBound;
}
inline static int PushAllBrickToTheHead(std::vector<int> & tmpImageSingleRow, const std::vector<int> & brickList, unsigned int thisBrickIndexLowerBound) {
    for (unsigned int i = 0; i < brickList.size(); i++) {
        thisBrickIndexLowerBound = PushBrickToTheHead(tmpImageSingleRow, brickList[i], thisBrickIndexLowerBound);
        if (thisBrickIndexLowerBound > tmpImageSingleRow.size() * 5) {
#if DEBUG == 1
            std::cout << "CONTRADICT";
#endif
            return NONOGRAM_IMAGE_LOGIC_SOLVE_SINGLE_LINE_CONST_CONTRADICT;
        }
    }
    return NONOGRAM_IMAGE_LOGIC_SOLVE_SINGLE_LINE_CONST_UNDETERMINED;
}
/*
inline static int PushAllBrickToTheHeadAndReturnLastElementStartIndex(std::vector<int> & tmpImageSingleRow, const std::vector<int> & brickList, unsigned int thisBrickIndexLowerBound) {
#if DEBUG == 3
    std::cout << "list: ";
    for (unsigned int i = 0; i < brickList.size(); i++) {std::cout << brickList[i] << " "; }
    std::cout << "\n";
#endif
    // except last element
    for (unsigned int i = 0; i < brickList.size() - 1; i++) {
        thisBrickIndexLowerBound = PushBrickToTheHead(tmpImageSingleRow, brickList[i], thisBrickIndexLowerBound);
        if (thisBrickIndexLowerBound > tmpImageSingleRow.size() * 5) {
#if DEBUG == 1
            std::cout << "CONTRADICT";
#endif
            return tmpImageSingleRow.size();
        }
    }
    unsigned int brickSize = brickList[brickList.size() - 1];
    unsigned int indexUpperBound = tmpImageSingleRow.size() - brickSize;
    
    // find cont in pattern
    unsigned int contInPattern = 0;
    while (thisBrickIndexLowerBound <= indexUpperBound) {
        contInPattern = 0;
        for (unsigned int j = 0; j <= brickSize; j++) {
            if (j < brickSize) {
                if (tmpImageSingleRow[thisBrickIndexLowerBound + j] != NONOGRAM_IMAGE_CONST_UNSELECTED) {
                    contInPattern++;
                } else {
                    contInPattern = 0;
                }
            } else {
                if (tmpImageSingleRow[thisBrickIndexLowerBound + j] != NONOGRAM_IMAGE_CONST_SELECTED) {
                    contInPattern++;
                } else {
                    contInPattern = 0;
                }
            }
        }
        if (contInPattern > brickSize)
            break;
        thisBrickIndexLowerBound++;
    }
    if (thisBrickIndexLowerBound > indexUpperBound) {
        return NONOGRAM_IMAGE_LOGIC_SOLVE_SINGLE_LINE_CONST_CONTRADICT;
    }
    
    // fill
    for (unsigned int i = 0; i < brickSize; i++) {
        tmpImageSingleRow[thisBrickIndexLowerBound + i] = NONOGRAM_IMAGE_CONST_SELECTED;
    }
#if DEBUG == 3
    std::cout << "helpDetermineBoundImage: ";
    for (unsigned int j = 0; j < tmpImageSingleRow.size(); j++) {
        std::cout << std::setw(2) << tmpImageSingleRow[j] << " ";
    }
    std::cout << "\n";
#endif
    return thisBrickIndexLowerBound;
}
*/


inline static void reverseVec(std::vector<int> & x) {
    if (x.size() == 0) {
        return;
    }
    unsigned int sizeMinusOne = x.size() - 1;
    unsigned int upperBound = x.size() / 2;
    for (unsigned int i = 0; i < upperBound; i++) {
        int tmp = x[i];
        x[i] = x[sizeMinusOne - i];
        x[sizeMinusOne - i] = tmp;
    }
    return;
}

inline static int PushAllBrickToTheTail(std::vector<int> & tmpImageSingleRow, const std::vector<int> & brickList, unsigned int thisBrickIndexUpperBound) {
    std::vector<int> cpyBrickList = brickList;
    unsigned int thisBrickIndexReverseLowerBound = tmpImageSingleRow.size() - 1 - thisBrickIndexUpperBound;

    reverseVec(tmpImageSingleRow);
    reverseVec(cpyBrickList);
    int pushStatus = PushAllBrickToTheHead(tmpImageSingleRow, cpyBrickList, thisBrickIndexReverseLowerBound);
    reverseVec(tmpImageSingleRow);
    return pushStatus;
}
/*
inline static int PushAllBrickToTheTailAndReturnLastElementStartIndex(std::vector<int> & tmpImageSingleRow, const std::vector<int> & brickList, unsigned int thisBrickIndexUpperBound) {
    std::vector<int> cpyBrickList = brickList;
    unsigned int thisBrickIndexReverseLowerBound = tmpImageSingleRow.size() - 1 - thisBrickIndexUpperBound;

    reverseVec(tmpImageSingleRow);
    reverseVec(cpyBrickList);

    int revIndex = PushAllBrickToTheHeadAndReturnLastElementStartIndex(tmpImageSingleRow, cpyBrickList, thisBrickIndexReverseLowerBound);
#if DEBUG == 3
    std::cout << "reversedVec: ";
    for (unsigned int j = 0; j < tmpImageSingleRow.size(); j++) {
        std::cout << std::setw(2) << tmpImageSingleRow[j] << " ";
    }
    std::cout << "\n";
#endif
    reverseVec(tmpImageSingleRow);
    return (tmpImageSingleRow.size() - 1 - revIndex);
}
*/

inline static void imageSingleRowToBrickIdArray(std::vector<int> & result, const std::vector<int> & tmpImageSingleRow) {
    int currentBrick = -1;
    int prevUnselected = 1;
    
    int rowLength = tmpImageSingleRow.size();
    int tmpIndex = 0;
    
    result.resize(rowLength);
    
    while (tmpIndex < rowLength) {
        if (prevUnselected) {
            // wait for select
            if (tmpImageSingleRow[tmpIndex] == NONOGRAM_IMAGE_CONST_SELECTED) {
                currentBrick++;
                prevUnselected = 0;
                result[tmpIndex] = currentBrick;
            } else {
                result[tmpIndex] = -1;
            }
        } else {
            // prev selected, wait for unselect
            if (tmpImageSingleRow[tmpIndex] == NONOGRAM_IMAGE_CONST_UNSELECTED) {
                prevUnselected = 1;
                result[tmpIndex] = -1;
            } else {
                result[tmpIndex] = currentBrick;
            }
        }
        tmpIndex++;
    }
}

inline static int getBrickStart(const std::vector<int> & tmpImageSingleRow, const unsigned int brickId) {
    int currentBrick = -1;
    int prevUnselected = 1;
    
    int rowLength = tmpImageSingleRow.size();
    int tmpIndex = 0;
    
    while (tmpIndex < rowLength) {
        if (prevUnselected) {
            // wait for select
            if (tmpImageSingleRow[tmpIndex] == NONOGRAM_IMAGE_CONST_SELECTED) {
                currentBrick++;
                prevUnselected = 0;
                if (currentBrick == (int)brickId) {
                    return tmpIndex;
                }
            } else {
                prevUnselected = 1;
            }
        } else {
            // prev selected, wait for unselect
            if (tmpImageSingleRow[tmpIndex] != NONOGRAM_IMAGE_CONST_SELECTED) {
                prevUnselected = 1;
            } else {
                prevUnselected = 0;
            }
        }
        tmpIndex++;
    }
    return tmpIndex;
}
/*
inline static int getBrickReverseStart(const std::vector<int> & tmpImageSingleRow, const unsigned int reverseBrickId) {
#if DEBUG == 3
    std::cout << "helpDetermineBoundImage: ";
    for (unsigned int j = 0; j < tmpImageSingleRow.size(); j++) {
        std::cout << std::setw(2) << tmpImageSingleRow[j] << " ";
    }
    std::cout << "\n";
#endif
    int currentBrick = -1;
    int prevUnselected = 1;
    
    int tmpIndex = (int)tmpImageSingleRow.size() - 1;
    
    while (tmpIndex >= 0) {
        if (prevUnselected) {
            // wait for select
            if (tmpImageSingleRow[tmpIndex] == NONOGRAM_IMAGE_CONST_SELECTED) {
                currentBrick++;
                prevUnselected = 0;
            } else {
                if (currentBrick == (int)reverseBrickId) {
                    return tmpIndex;
                }
                prevUnselected = 1;
            }
        } else {
            // prev selected, wait for unselect
            if (tmpImageSingleRow[tmpIndex] != NONOGRAM_IMAGE_CONST_SELECTED) {
                prevUnselected = 1;
            } else {
                prevUnselected = 0;
            }
        }
        tmpIndex--;
    }
    return tmpIndex;
}
*/

static int GetOneBrickAllPossiblePosition(std::vector<std::vector<int> > & result, const std::vector<int> & puzzleSingleRow, const std::vector<int> & tmpImageSingleRow, const unsigned int brickId) {
    // instantly used values
    int rowLength = tmpImageSingleRow.size();
    int thisBrickSize = puzzleSingleRow[brickId];
 
    std::vector<int> leftList, rightList;
    for (unsigned int i = 0; i < brickId; i++) {
        leftList.push_back(puzzleSingleRow[i]);
    }
    for (unsigned int i = brickId + 1; i < puzzleSingleRow.size(); i++) {
        rightList.push_back(puzzleSingleRow[i]);
    }
#if DEBUG == 3
    std::cout << "ThisBrick: " << puzzleSingleRow[brickId] << "\n";
    std::cout << "left list: "; for (unsigned int i = 0; i < leftList.size(); i++) {std::cout << leftList[i] << " ";} std::cout << "\n";
    std::cout << "right list: "; for (unsigned int i = 0; i < rightList.size(); i++) {std::cout << rightList[i] << " ";} std::cout << "\n";
    std::cout << "brickId: " << brickId << "\n";
#endif
#if DEBUG == 3
    std::cout << "tmpImageSingleRow: \n";
    for (unsigned int j = 0; j < tmpImageSingleRow.size(); j++) {
        switch (tmpImageSingleRow[j]) {
        case NONOGRAM_IMAGE_CONST_SELECTED:   std::cout << '#'; break;
        case NONOGRAM_IMAGE_CONST_UNSELECTED: std::cout << '.'; break;
        default:                              std::cout << '@'; break;
        }
    }
    std::cout << "\n";
#endif

    // get start upper bound and lower bound
    std::vector<int> leftListIncludeThisBrick;
    std::vector<int> rightListIncludeThisBrick;
    
    leftListIncludeThisBrick = leftList; leftListIncludeThisBrick.push_back(puzzleSingleRow[brickId]);
    rightListIncludeThisBrick = rightList; rightListIncludeThisBrick.insert(rightListIncludeThisBrick.begin(), puzzleSingleRow[brickId]);
    
    int brickStartLowerBound, brickStartUpperBound;

    std::vector<int> helpDetermineBoundImage;
    helpDetermineBoundImage = tmpImageSingleRow;
    PushAllBrickToTheHead(helpDetermineBoundImage, leftListIncludeThisBrick, 0);
#if DEBUG == 3
    std::cout << "helpDetermineBoundImage, head: ";
    for (unsigned int j = 0; j < helpDetermineBoundImage.size(); j++) {
        std::cout << std::setw(2) << helpDetermineBoundImage[j] << " ";
    }
    std::cout << "\n";
#endif

    brickStartLowerBound = getBrickStart(helpDetermineBoundImage, leftList.size());

    helpDetermineBoundImage = tmpImageSingleRow;

    PushAllBrickToTheTail(helpDetermineBoundImage, rightListIncludeThisBrick, rowLength - 1);
#if DEBUG == 3
    std::cout << "helpDetermineBoundImage, tail: ";
    for (unsigned int j = 0; j < helpDetermineBoundImage.size(); j++) {
        std::cout << std::setw(2) << helpDetermineBoundImage[j] << " ";
    }
    std::cout << "\n";
#endif
    reverseVec(helpDetermineBoundImage);

    int revBrickStartUpperBound = getBrickStart(helpDetermineBoundImage, rightList.size());
//    reverse(helpDetermineBoundImage);
    brickStartUpperBound = rowLength - revBrickStartUpperBound - thisBrickSize;
    
#if DEBUG == 3
    std::cout << "brickStartLowerBound = " << brickStartLowerBound << ", brickStartUpperBound = " << brickStartUpperBound << "\n";
#endif 
    

    std::vector<int> validBrickStart;
    validBrickStart.clear();
    validBrickStart.resize(rowLength, 1);
    
    // check validity (simple)
    for (int i = brickStartLowerBound; i <= brickStartUpperBound; i++) {
        for (int j = 0; j < thisBrickSize;j++) {
            if (tmpImageSingleRow[i + j] == NONOGRAM_IMAGE_CONST_UNSELECTED) {
                validBrickStart[i] = 0;
            }
        }
    }
/*
    if (puzzleSingleRow.size() == 1) {
        std::vector<int> helpCheckValidity;
        for (int i = brickStartLowerBound; i <= brickStartUpperBound; i++) {
            helpCheckValidity = tmpImageSingleRow;
            for (int j = 0; j < thisBrickSize;j++) {
                helpCheckValidity[i + j] = NONOGRAM_IMAGE_CONST_SELECTED;
            }
            int selectedCount = 0;
            for (unsigned int j = 0; j < helpCheckValidity.size(); j++) {
                if (helpCheckValidity[j] == NONOGRAM_IMAGE_CONST_SELECTED) {
                    selectedCount++;
                }
            }
            if (selectedCount != thisBrickSize) {
                validBrickStart[i] = 0;
            }
        }
    }
*/
    
    std::vector<int> oneResult;
    for (int i = brickStartLowerBound; i <= brickStartUpperBound; i++) {
        if (validBrickStart[i]) {
           // find one possible, write answer
           // -1 means do not put
           oneResult.clear();
           oneResult.resize(rowLength, -1);
           for (int j = 0; j < thisBrickSize;j++) {
               oneResult[i + j] = brickId;
           }
#if DEBUG == -2
           std::cout << "FindPossible: \n";
           for (unsigned int j = 0; j < oneResult.size(); j++) {
               std::cout << std::setw(2) << oneResult[j] << " ";
           }
           std::cout << "\n";
           system("pause");
#endif
           result.push_back(oneResult);
        }
    }
    

    return NONOGRAM_IMAGE_LOGIC_SOLVE_CONST_UNDETERMINED;

/*
    int thisBrickSize = puzzleSingleRow[brickId];
    int rowLength = tmpImageSingleRow.size();
    int brickStartUpperBound = rowLength - thisBrickSize;
    std::vector<int> helpPutBrickIn;
    std::vector<int> helpJudgePuzzleSingleRow;
    
    std::vector<int> validBrickStart;
    validBrickStart.clear();
    validBrickStart.resize(rowLength, 0);
    
    std::vector<int> afterHeadTail;
    for (int i = 0; i <= brickStartUpperBound; i++) {
        
        helpPutBrickIn = tmpImageSingleRow;
        // put this brick in
        for (int j = 0; j < thisBrickSize;j++) {
            helpPutBrickIn[i + j] = NONOGRAM_IMAGE_CONST_SELECTED;
        }
        afterHeadTail = helpPutBrickIn;
        
        // headTail
        PushAllBrickToTheHead(afterHeadTail, leftList, 0);
        PushAllBrickToTheTail(afterHeadTail, rightList, rowLength - 1);
        
        // fill
        for (int j = 0; j < rowLength; j++) {
            if (afterHeadTail[j] == NONOGRAM_IMAGE_CONST_UNDETERMINED) {
                afterHeadTail[j] = NONOGRAM_IMAGE_CONST_UNSELECTED;
            }
        }

#if DEBUG == 3
        std::cout << "Current: \n";
        for (unsigned int j = 0; j < afterHeadTail.size(); j++) {
            switch (afterHeadTail[j]) {
            case NONOGRAM_IMAGE_CONST_SELECTED:   std::cout << '#'; break;
            case NONOGRAM_IMAGE_CONST_UNSELECTED: std::cout << '.'; break;
            default:                              std::cout << '@'; break;
            }
        }
        std::cout << "\n";
#endif
        // check whether valid
        ImageSingleRowToPuzzleSingleRow(afterHeadTail, helpJudgePuzzleSingleRow);
        if (helpJudgePuzzleSingleRow == puzzleSingleRow) {
            int realBrickStart = 0;
            realBrickStart = getBrickStart(afterHeadTail, brickId);
            validBrickStart[realBrickStart] = 1;
#if DEBUG == 3
            std::cout << "is valid, realBrickStart = " << realBrickStart << "\n";
#endif
        }
     }
     std::vector<int> oneResult;
     for (int i = 0; i <= brickStartUpperBound; i++) {
         if (validBrickStart[i]) {
            // find one possible, write answer
            // -1 means do not put
            oneResult.clear();
            oneResult.resize(rowLength, -1);
            for (int j = 0; j < thisBrickSize;j++) {
                oneResult[i + j] = brickId;
            }
#if DEBUG == 3
            std::cout << "FindPossible: \n";
            for (unsigned int j = 0; j < oneResult.size(); j++) {
                std::cout << std::setw(2) << oneResult[j] << " ";
            }
            std::cout << "\n";
            system("pause");
#endif
            result.push_back(oneResult);
         }
     }
*/ 
}

static int LogicSolveSingleLine(const std::vector<int> & puzzleSingleRow, std::vector<int> & imageSingleRow) {

#if DEBUG == 3
    std::cout << "this line puzzle\n";
    for (unsigned int i = 0; i < puzzleSingleRow.size(); i++) {std::cout << puzzleSingleRow[i] << ' ';} std::cout << "\n";
    std::cout << "current image:\n";
    for (unsigned int i = 0; i < imageSingleRow.size(); i++) {
        switch (imageSingleRow[i]) {
        case NONOGRAM_IMAGE_CONST_SELECTED:       std::cout << '#'; break;
        case NONOGRAM_IMAGE_CONST_UNSELECTED: std::cout << '.'; break;
        default:                                          std::cout << '@'; break;
        }
    }
    std::cout << "\n";
#endif

    std::vector<int> puzzleSingleRowHelpCheckDone;
    if (ImageSingleRowToPuzzleSingleRow(imageSingleRow, puzzleSingleRowHelpCheckDone)) {
        // all determined
        if (puzzleSingleRowHelpCheckDone == puzzleSingleRow) {
            return NONOGRAM_IMAGE_LOGIC_SOLVE_SINGLE_LINE_CONST_DONE;
        } else {
            return NONOGRAM_IMAGE_LOGIC_SOLVE_SINGLE_LINE_CONST_CONTRADICT; 
        }
    }
    
    unsigned int nBrick = puzzleSingleRow.size();
    unsigned int nDotsInARow = imageSingleRow.size();
    
    int thisPassChanged = 1;
    while (thisPassChanged > 0) {
        thisPassChanged = 0;
        std::vector<std::vector<std::vector<int> > > possiblePositionList;
        possiblePositionList.resize(nBrick);
        for (unsigned int brickId = 0; brickId < nBrick; brickId++) {
//            unsigned int prevListLength = possiblePositionList.size();
            GetOneBrickAllPossiblePosition(possiblePositionList[brickId], puzzleSingleRow, imageSingleRow, brickId);
//            unsigned int currentListLength = possiblePositionList.size();
            // refresh new
            for (unsigned int iDot = 0; iDot < nDotsInARow; iDot++) {
                int canSelect = 1;
                for (unsigned int iRowInTheList = 0; iRowInTheList < possiblePositionList[brickId].size(); iRowInTheList++) {
                    if (possiblePositionList[brickId][iRowInTheList][iDot] == -1) {
                        canSelect = 0;
                    }
                }
                if (canSelect) {
                     imageSingleRow[iDot] = NONOGRAM_IMAGE_CONST_SELECTED;
                }
            }
/*
            for (unsigned int iDot = 0; iDot < nDotsInARow; iDot++) {
                int canSelect = 1;
                for (unsigned int iRowInTheList = prevListLength; iRowInTheList < currentListLength; iRowInTheList++) {
                    if (possiblePositionList[iRowInTheList][iDot] == -1) {
                        canSelect = 0;
                    }
                }
                if (canSelect) {
                     imageSingleRow[iDot] = NONOGRAM_IMAGE_CONST_SELECTED;
                }
            }
*/
        }

/*
        for (unsigned int iDot = 0; iDot < nDotsInARow; iDot++) {
            int canUnselect = 1;
            for (unsigned int iRowInTheList = 0; iRowInTheList < possiblePositionList.size(); iRowInTheList++) {
                if (possiblePositionList[iRowInTheList][iDot] != -1) {
                   canUnselect = 0;
                }
            }
            if (canUnselect) {
                imageSingleRow[iDot] = NONOGRAM_IMAGE_CONST_UNSELECTED;
            }
        }
*/

#if DEBUG == 4
        for (unsigned int brickId = 0; brickId < possiblePositionList.size(); brickId++) {
            std::cout << "brickId: " << brickId << " possible: " << possiblePositionList[brickId].size() << "\n";
            for (unsigned int i = 0; i < possiblePositionList[brickId].size(); i++) {
                for (unsigned int j = 0; j < possiblePositionList[brickId][i].size(); j++) {
                    std::cout << std::setw(2) << possiblePositionList[brickId][i][j] << " ";
                }
                std::cout << "\n";
            }
        }
#endif

        // complicated filtering
        std::vector<unsigned int> helpFilterCounter;
        helpFilterCounter.clear();
        helpFilterCounter.resize(nBrick + 1, 0);
        
        // filtering estimation
        
        const unsigned int COMPLICATED_FILTERING_THRESHOLD = 4096;
        
        unsigned int EstimatedFilteringTime = 1;
        
        for (unsigned int brickId = 0; brickId < nBrick; brickId++) {
            EstimatedFilteringTime *= possiblePositionList[brickId].size();
        }
#if DEBUG == 997
        std::cout << "EstimatedFilteringTime = " << EstimatedFilteringTime << "\n";
#endif
        if (EstimatedFilteringTime == 0) {
            // no possible solution
            return NONOGRAM_IMAGE_LOGIC_SOLVE_SINGLE_LINE_CONST_CONTRADICT;
        }

        if (EstimatedFilteringTime <= COMPLICATED_FILTERING_THRESHOLD) {
            std::vector<int> helpCheckValidityImageRow;
            std::vector<int> helpCheckValidityPuzzleRow;
            std::vector< std::vector<unsigned int> > realValidList;
            realValidList.resize(nBrick);
            for (unsigned int brickId = 0; brickId < nBrick; brickId++) {
                realValidList[brickId].clear();
                realValidList[brickId].resize(possiblePositionList[brickId].size(), 0);
            }
            
            while (!helpFilterCounter[nBrick]) {
#if DEBUG == 4
                std::cout << "helpFilterCounter: ";
                for (unsigned int brickId = 0; brickId < nBrick; brickId++) {std::cout << helpFilterCounter[brickId] << ' '; }
#endif
                // check validity
                
                // fill the row
                helpCheckValidityImageRow = imageSingleRow;
                for (unsigned int brickId = 0; brickId < nBrick; brickId++) {
                    unsigned int iPossibilityOfThisBrick = helpFilterCounter[brickId];
                    for (unsigned int iDot = 0; iDot < nDotsInARow; iDot++) {
                        if (possiblePositionList[brickId][iPossibilityOfThisBrick][iDot] != -1) {
                            helpCheckValidityImageRow[iDot] = NONOGRAM_IMAGE_CONST_SELECTED;
                        }
                    }
                }
                // convert and check
                ImageSingleRowToPuzzleSingleRow(helpCheckValidityImageRow, helpCheckValidityPuzzleRow);


                if (helpCheckValidityPuzzleRow == puzzleSingleRow) {

                    for (unsigned int brickId = 0; brickId < nBrick; brickId++) {
                        realValidList[brickId][helpFilterCounter[brickId]] = 1;
#if DEBUG == 4
                        std::cout << "(" << brickId << "," << helpFilterCounter[brickId] << ") ";
#endif
                        
                    }
#if DEBUG == 4
                     std::cout << "valid\n";
#endif
                }
#if DEBUG == 4
                else { std::cout << "invalid\n"; }
#endif
#if DEBUG == 5
            for (unsigned int brickId = 0; brickId < possiblePositionList.size(); brickId++) {
                std::cout << "brickId: " << brickId << "realValidList: ";
                for (unsigned int i = 0; i < possiblePositionList[brickId].size(); i++) {
                    std::cout << realValidList[brickId][i] << ' ';
                }
                std::cout << "\n";
            }
#endif
                
                // add 
                helpFilterCounter[0]++;
                // carry
                for (unsigned int brickId = 0; brickId < nBrick; brickId++) {
                    if (helpFilterCounter[brickId] >= possiblePositionList[brickId].size()) {
                        helpFilterCounter[brickId] = 0;
                        helpFilterCounter[brickId + 1]++;
                    }
                }
            }
#if DEBUG == 5
            for (unsigned int brickId = 0; brickId < possiblePositionList.size(); brickId++) {
                std::cout << "brickId: " << brickId << " possible:\n";
                for (unsigned int i = 0; i < possiblePositionList[brickId].size(); i++) {
                    if (realValidList[brickId][i] != 0) {
                        std::cout << i << ' ';
                    }
                }
                std::cout << "\n";
            }
#endif
            // remove impossible
            for (unsigned int brickId = 0; brickId < possiblePositionList.size(); brickId++) {
                for (unsigned int i = 0; i < possiblePositionList[brickId].size(); i++) {
                    if (realValidList[brickId][i] == 0) {
                        possiblePositionList[brickId][i].clear();
                    }
                }
            }
#if DEBUG == 4

            for (unsigned int brickId = 0; brickId < possiblePositionList.size(); brickId++) {
                std::cout << "brickId: " << brickId << " possible: " << possiblePositionList[brickId].size() << "\n";
                for (unsigned int i = 0; i < possiblePositionList[brickId].size(); i++) {
                    for (unsigned int j = 0; j < possiblePositionList[brickId][i].size(); j++) {
                        std::cout << std::setw(2) << possiblePositionList[brickId][i][j] << " ";
                    }
                    std::cout << "\n";
                }
            }

#endif
            for (unsigned int brickId = 0; brickId < possiblePositionList.size(); brickId++) {
                unsigned int i = 0;
                while(i < possiblePositionList[brickId].size()) {
                    if (possiblePositionList[brickId][i].empty()) {
                        possiblePositionList[brickId].erase(possiblePositionList[brickId].begin() + i);
                    } else {
                        i++;
                    }
                }
            }
            // if there is a brick not valid then return contradict
            for (unsigned int brickId = 0; brickId < possiblePositionList.size(); brickId++) {
                if (possiblePositionList[brickId].empty()) {
                    return NONOGRAM_IMAGE_LOGIC_SOLVE_SINGLE_LINE_CONST_CONTRADICT;
                }
            }

#if DEBUG == 4

            for (unsigned int brickId = 0; brickId < possiblePositionList.size(); brickId++) {
                std::cout << "brickId: " << brickId << " possible: " << possiblePositionList[brickId].size() << "\n";
                for (unsigned int i = 0; i < possiblePositionList[brickId].size(); i++) {
                    for (unsigned int j = 0; j < possiblePositionList[brickId][i].size(); j++) {
                        std::cout << std::setw(2) << possiblePositionList[brickId][i][j] << " ";
                    }
                    std::cout << "\n";
                }
            }

#endif
        }

        // refresh by valid list
        for (unsigned int brickId = 0; brickId < nBrick; brickId++) {
            for (unsigned int iDot = 0; iDot < nDotsInARow; iDot++) {
                int canSelect = 1;
                for (unsigned int iRowInTheList = 0; iRowInTheList < possiblePositionList[brickId].size(); iRowInTheList++) {
                    if (possiblePositionList[brickId][iRowInTheList][iDot] == -1) {
                        canSelect = 0;
                    }
                }
                if (canSelect) {
                     imageSingleRow[iDot] = NONOGRAM_IMAGE_CONST_SELECTED;
                } 
            }
        }
        for (unsigned int iDot = 0; iDot < nDotsInARow; iDot++) {
            int canUnselect = 1;
            for (unsigned int brickId = 0; brickId < nBrick; brickId++) {
                for (unsigned int iRowInTheList = 0; iRowInTheList < possiblePositionList[brickId].size(); iRowInTheList++) {
                    if (possiblePositionList[brickId][iRowInTheList][iDot] != -1) {
                        canUnselect = 0;
                    }
                }
            }
            if (canUnselect) {
                 imageSingleRow[iDot] = NONOGRAM_IMAGE_CONST_UNSELECTED;
            } 
        }


#if DEBUG == 997
        std::cout << "Refreshed imageSingleRow: \n";
        for (unsigned int j = 0; j < imageSingleRow.size(); j++) {
            switch (imageSingleRow[j]) {
            case NONOGRAM_IMAGE_CONST_SELECTED:   std::cout << '#'; break;
            case NONOGRAM_IMAGE_CONST_UNSELECTED: std::cout << '.'; break;
            default:                              std::cout << '@'; break;
            }
        }
        std::cout << "\n";
        system("pause");
#endif
    }


    return NONOGRAM_IMAGE_LOGIC_SOLVE_SINGLE_LINE_CONST_UNDETERMINED;
}

static int LogicSolveImage(const NonogramPuzzle & puzzle, NonogramImage & image) {
    std::vector<int> imageSingleRow;
    std::vector<int> imageSingleRowPrev;
    
    int nRow = puzzle.rowCount();
    int nColumn = puzzle.columnCount();
    
//  one pass method
    int thisPassChangedLine = 1;
    int currentDone;
    
    while (thisPassChangedLine > 0) {
#if DEBUG == 3
    std::cout << "This Pass image:\n";
    std::cout << image;
#endif
        int singleLineStatus;
        thisPassChangedLine = 0;
        currentDone = 0;
        
        for (int i = 0; i < nRow; i++) {
            image.read_row(i, imageSingleRow);
            imageSingleRowPrev = imageSingleRow;
            singleLineStatus = LogicSolveSingleLine(puzzle.row[i], imageSingleRow);
            image.write_row(i, imageSingleRow);
            switch (singleLineStatus) {
            case NONOGRAM_IMAGE_LOGIC_SOLVE_SINGLE_LINE_CONST_UNDETERMINED:
                break;
            case NONOGRAM_IMAGE_LOGIC_SOLVE_SINGLE_LINE_CONST_DONE:
                currentDone++;
                break;
            case NONOGRAM_IMAGE_LOGIC_SOLVE_SINGLE_LINE_CONST_CONTRADICT:
                return NONOGRAM_IMAGE_LOGIC_SOLVE_CONST_CONTRADICT;// end loop
                break;
            default:
                return NONOGRAM_IMAGE_LOGIC_SOLVE_CONST_CONTRADICT;
                break;
            }
            if (imageSingleRowPrev != imageSingleRow) {
                thisPassChangedLine++;
            }
        }
        for (int i = 0; i < nColumn; i++) {
            image.read_column(i, imageSingleRow);
            imageSingleRowPrev = imageSingleRow;
            singleLineStatus = LogicSolveSingleLine(puzzle.column[i], imageSingleRow);
            image.write_column(i, imageSingleRow);
            switch (singleLineStatus) {
            case NONOGRAM_IMAGE_LOGIC_SOLVE_SINGLE_LINE_CONST_UNDETERMINED:
                break;
            case NONOGRAM_IMAGE_LOGIC_SOLVE_SINGLE_LINE_CONST_DONE:
                currentDone++;
                break;
            case NONOGRAM_IMAGE_LOGIC_SOLVE_SINGLE_LINE_CONST_CONTRADICT:
                return NONOGRAM_IMAGE_LOGIC_SOLVE_CONST_CONTRADICT;// end loop
                break;
            default:
                return NONOGRAM_IMAGE_LOGIC_SOLVE_CONST_CONTRADICT;
                break;
            }
            if (imageSingleRowPrev != imageSingleRow) {
                thisPassChangedLine++;
            }
        }
#if DEBUG == 3
    std::cout << "End this pass, thisPassChangedLine: " << thisPassChangedLine << "\n";
#endif
    }
    
    if (currentDone == nRow + nColumn) {
        return NONOGRAM_IMAGE_LOGIC_SOLVE_CONST_DONE;
    }
    
    return NONOGRAM_IMAGE_LOGIC_SOLVE_CONST_UNDETERMINED;
}

int SolvePuzzle(const NonogramPuzzle & puzzle, NonogramImage & image) {
    
    std::stack<NonogramImage> imageStack;
    while (!imageStack.empty()) {
        imageStack.pop();
    } // clear
    
    image.clear_and_resize(puzzle.rowCount(), puzzle.columnCount());

    imageStack.push(image);
    int topImageStatus = NONOGRAM_IMAGE_LOGIC_SOLVE_CONST_UNDETERMINED;

#if DEBUG == 999
    long long int callTime = 0;
#endif
    
    while (!imageStack.empty() && topImageStatus != NONOGRAM_IMAGE_LOGIC_SOLVE_CONST_DONE) {
#if DEBUG == 999
        callTime++;
        if (callTime % 1000ULL == 0) {
            std::cout << callTime << " stackSize = " << imageStack.size() << "\n";
            std::cout << imageStack.top();
        }
#endif
        topImageStatus = LogicSolveImage(puzzle, imageStack.top());
        switch (topImageStatus) {
        case NONOGRAM_IMAGE_LOGIC_SOLVE_CONST_UNDETERMINED:
        ImageStackMakeBranch(imageStack);
        break;
        case NONOGRAM_IMAGE_LOGIC_SOLVE_CONST_CONTRADICT:
        imageStack.pop(); // remove impossible
        break;
        case NONOGRAM_IMAGE_LOGIC_SOLVE_CONST_DONE:
        break;
        default:
        // impossible, assume done
        topImageStatus = NONOGRAM_IMAGE_LOGIC_SOLVE_CONST_DONE;
        break;
        }
    } // clear

    if (imageStack.empty()) {
        image.clear_and_resize(puzzle.rowCount(), puzzle.columnCount());
#if DEBUG == 999
        std::cout << "no solution\n";
#endif
        return 0;
    } else {
        image = imageStack.top();
        return 1;
    }
    return 1;
}


