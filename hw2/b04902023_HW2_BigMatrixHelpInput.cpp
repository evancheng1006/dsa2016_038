#include <cstdio>
#include <cctype>
#include "b04902023_HW2_BigMatrix.h"

void inputWithoutConstructedStructure(FILE * fp, BigMatrix & data) {
	char lineBuffer[128];
	BigMatrixSingleRow tmp;
	fseek(fp, 0, SEEK_SET);
//	while(fscanf(fp, "%d%d%d%d", &(tmp.UserId), &(tmp.ItemId), &(tmp.Result), &(tmp.UnixTimeStamp)) == 4) {	
	int UserId;
	int ItemId;
	int Result;
	int UnixTimeStamp;
	char * currentChar;
	while(fgets(lineBuffer, 128, fp) != NULL) {
		currentChar = lineBuffer;
		UserId = 0;
		ItemId = 0;
		Result = 0;
		UnixTimeStamp = 0;
		while (isdigit(*currentChar)) {
			UserId *= 10;
			UserId += *currentChar - '0';
			currentChar++;
		}
		while (!isdigit(*currentChar)) {
			currentChar++;
		}
		while (isdigit(*currentChar)) {
			ItemId *= 10;
			ItemId += *currentChar - '0';
			currentChar++;
		}
		while (*currentChar != '-' & *currentChar != '1') {
			currentChar++;
		}
		if (*currentChar == '-') {
			Result = -1;
			currentChar++;
			currentChar++;
		} else {
			Result = 1;
			currentChar++;
		}
		while (!isdigit(*currentChar)) {
			currentChar++;
		}
		while (isdigit(*currentChar)) {
			UnixTimeStamp *= 10;
			UnixTimeStamp += *currentChar - '0';
			currentChar++;
		}
		tmp.UserId = UserId;
		tmp.ItemId = ItemId;
		tmp.Result = Result;
		tmp.UnixTimeStamp = UnixTimeStamp;
		if (tmp != *(data.sortByItemIdUserIdUnixTimeStamp.end()-1)) {
			data.sortByItemIdUserIdUnixTimeStamp.push_back(tmp);
		}
	}
}
