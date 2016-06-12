#include "database.h"
#include "databaseio.h"
#include "queryprocess.h"

#include <iostream>
#include <fstream>

int main()
{
 // file list
 ///tmp2/dsa2016_project/2gm.small.txt
 ///tmp2/dsa2016_project/3gm.small.txt
 ///tmp2/dsa2016_project/4gm.small.txt
 ///tmp2/dsa2016_project/5gm.small.txt
 
	
	char fileName[][256] = {
		"/tmp2/dsa2016_project/2gm.small.txt",
		"/tmp2/dsa2016_project/3gm.small.txt",
		"/tmp2/dsa2016_project/4gm.small.txt",
		"/tmp2/dsa2016_project/5gm.small.txt",
		"fuckingsmall.txt"
	};
 	DATABASE db;
/*
	FILE *fp;

	fp = fopen(fileName[0], "r");
#if DEBUG==1
	if (fp == NULL) {
		std::cout << fileName[0] << "\n";
		std::cout << "wtf""\n";
		return 0;
	}
#endif
	fclose(fp);
*/

	std::ifstream fin;

	for (int i = 0; i < 5; i++) {
		fin.open(fileName[i]);
		fin >> db;
		fin.close();
	}

	QueryProcess(std::cin, std::cout, db);
 	
	return 0;
}
