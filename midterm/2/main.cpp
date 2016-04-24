#include <bits/stdc++.h>

using namespace std;

std::vector<int> input;

void pre(unsigned int i) {
	cout << input[i] << ' ';
	if (i * 2 < input.size()) {
		if (input[i*2] != -1) {
			pre(i*2);
		}
	}
	if (i * 2 + 1< input.size()) {
		if (input[i*2+1] != -1) {
			pre(i*2+1);
		}
	}
	return;
}

void in(unsigned int i) {
	if (i * 2 < input.size()) {
		if (input[i*2] != -1) {
			in(i*2);
		}
	}
	cout << input[i] << ' ';
	if (i * 2 + 1< input.size()) {
		if (input[i*2+1] != -1) {
			in(i*2+1);
		}
	}
	return;
}
void post(unsigned int i) {

	if (i * 2 < input.size()) {
		if (input[i*2] != -1) {
			post(i*2);
		}
	}
	if (i * 2 + 1< input.size()) {
		if (input[i*2+1] != -1) {
			post(i*2+1);
		}
	}
	cout << input[i] << ' ';
	return;
}

int main() {
	int tmp;
	
	while(cin >> tmp) {
		input.push_back(tmp);
	}
	
	pre(1); cout << "\n";
	in(1); cout << "\n";
	post(1); cout << "\n";
	
	return 0;
}
