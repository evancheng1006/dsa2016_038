// File name : b04902023_HW2.cpp

#include <iostream>
#include <cstdio>
#include <fstream>
#include <vector>

#include "b04902023_HW2_BigMatrix.h"

#define LINES (73209277)

extern void QueryProcess(std::istream & input, BigMatrix & matrix ,std::ostream & output);
extern void inputWithoutConstructedStructure(FILE * fp, BigMatrix & data);

int main() {
	BigMatrix data;
	char inputFileName[2][256] = {
		"/tmp2/KDDCUP2012/track1/rec_log_train.txt",
		"smalltestfile.txt"};
	
	FILE* fp;
	fp = fopen(inputFileName[0],"r");
	inputWithoutConstructedStructure(fp, data);
	fclose(fp);
//	std::cout << data;
	data.ConstructDataStructure();

//	std::ifstream fin;
//	fin.open(inputFileName[0]);
//	fin >> data;
//	fin.close();
	
	QueryProcess(std::cin, data, std::cout);

/*
	data.select_display_array("raw");
//	std::cout << data << std::endl << std::endl;
	data.select_display_array("sortByItemIdUserIdUnixTimeStamp");
//	std::cout << data << std::endl << std::endl;
	data.select_display_array("sortByUserIdItemIdUnixTimeStamp");
//	std::cout << data << std::endl << std::endl;
	data.select_display_array("sortByUnixTimeStampItemIdUserId");
*/
//	std::cout << data << std::endl << std::endl;
//	std::cout << "fuck" << std::endl;
//	std::cin >> data;
//	std::cout << data;
//	std::cout << data.get_size() << std::endl;
/*
	std::cout << data.accept(2202935, 1774595, 1318348789) << std::endl; // -1
	std::cout << data.accept(633246 , 731434 , 1318348793) << std::endl; // 1
	std::cout << data.accept(1507848, 1928655, 1318348798) << std::endl; // -1
	std::cout << data.accept(1331696, 472999 , 1318348798) << std::endl; // -1
	std::cout << data.accept(1463875, 727324 , 1318348797) << std::endl; // 1
	std::cout << data.accept(249130 , 687441 , 1318348792) << std::endl; // -1
	std::cout << data.accept(2384384, 1774963, 1318348794) << std::endl; // 1
	std::cout << data.accept(2307074, 2393452, 1318348793) << std::endl; // -1
	std::cout << data.accept(999261 , 2393452, 1318348796) << std::endl; // 1
	std::cout << data.accept(2319049, 218438 , 1318348796) << std::endl; // 1
	std::cout << data.accept(0      , 1774595, 1318348789) << std::endl; // 0
	std::cout << data.accept(2202935, 0      , 1318348789) << std::endl; // 0
	std::cout << data.accept(2202935, 1774595, 0         ) << std::endl; // 0
	std::cout << data.accept(2202935, 1774595, 1318348789) << std::endl; // -1
*/
	std::vector<int> tmp;
/*
	tmp = data.items(1130508, 633246);
//	for (int i = 0; i < tmp.size(); i++) { std::cout << tmp[i] << ' '; } std::cout << std::endl;
	tmp = data.items(633246, 1130508);
//	for (int i = 0; i < tmp.size(); i++) { std::cout << tmp[i] << ' '; } std::cout << std::endl;
	tmp = data.items(2384384, 249130);
//	for (int i = 0; i < tmp.size(); i++) { std::cout << tmp[i] << ' '; } std::cout << std::endl;
	tmp = data.items(421723, 2319049);
//	for (int i = 0; i < tmp.size(); i++) { std::cout << tmp[i] << ' '; } std::cout << std::endl;
	tmp = data.items(570974, 451392);
//	for (int i = 0; i < tmp.size(); i++) { std::cout << tmp[i] << ' '; } std::cout << std::endl;
	tmp = data.items(570974, 0);
//	for (int i = 0; i < tmp.size(); i++) { std::cout << tmp[i] << ' '; } std::cout << std::endl;
	tmp = data.items(0, 30000000);
//	for (int i = 0; i < tmp.size(); i++) { std::cout << tmp[i] << ' '; } std::cout << std::endl;
*/
/*	
	tmp = data.users(218438, 458026, 0, 1499999999);
	for (int i = 0; i < tmp.size(); i++) { std::cout << tmp[i] << ' '; } std::cout << std::endl;
	tmp = data.users(441554, 2393452, 0, 1499999999);
	for (int i = 0; i < tmp.size(); i++) { std::cout << tmp[i] << ' '; } std::cout << std::endl;
	tmp = data.users(721665, 458026, 1318348794, 1318348796);
	for (int i = 0; i < tmp.size(); i++) { std::cout << tmp[i] << ' '; } std::cout << std::endl;
	tmp = data.users(721665, 458026, 1318348795, 1318348797);
	for (int i = 0; i < tmp.size(); i++) { std::cout << tmp[i] << ' '; } std::cout << std::endl;
	tmp = data.users(721665, 458026, 1318348796, 1318348794);
	for (int i = 0; i < tmp.size(); i++) { std::cout << tmp[i] << ' '; } std::cout << std::endl;
	tmp = data.users(1760353, 908591, 1318348793, 1318348796);
	for (int i = 0; i < tmp.size(); i++) { std::cout << tmp[i] << ' '; } std::cout << std::endl;	
	tmp = data.users(1760353, 908591, 1318348794, 1318348796);
	for (int i = 0; i < tmp.size(); i++) { std::cout << tmp[i] << ' '; } std::cout << std::endl;
*/
/*
	tmp = data.ratio(1774452, 0);
	for (int i = 0; i < tmp.size(); i++) { std::cout << tmp[i] << ' '; } std::cout << std::endl;
	tmp = data.ratio(731434, 0);
	for (int i = 0; i < tmp.size(); i++) { std::cout << tmp[i] << ' '; } std::cout << std::endl;
	tmp = data.ratio(731434, 4);
	for (int i = 0; i < tmp.size(); i++) { std::cout << tmp[i] << ' '; } std::cout << std::endl;
	tmp = data.ratio(218438, 0);
	for (int i = 0; i < tmp.size(); i++) { std::cout << tmp[i] << ' '; } std::cout << std::endl;
	tmp = data.ratio(218438, 4);
	for (int i = 0; i < tmp.size(); i++) { std::cout << tmp[i] << ' '; } std::cout << std::endl;
*/
/*
	tmp = data.ratio(713310, 10000); // ans: 1/4
	for (int i = 0; i < tmp.size(); i++) { std::cout << tmp[i] << ' '; } std::cout << std::endl;
	tmp = data.ratio(627961, 10000); // ans: 2/4
	for (int i = 0; i < tmp.size(); i++) { std::cout << tmp[i] << ' '; } std::cout << std::endl;
	tmp = data.ratio(0, 10000); // ans: 0/4
	for (int i = 0; i < tmp.size(); i++) { std::cout << tmp[i] << ' '; } std::cout << std::endl;
*/
/*
	std::set<int> Us;

	Us.clear(); Us.insert(1608137); Us.insert(451392); Us.insert(1991609); Us.insert(570974);
	tmp = data.findtime_item(1774509, Us);
	for (int i = 0; i < tmp.size(); i++) { std::cout << tmp[i] << ' '; } std::cout << std::endl;
*/


	return 0;
}

