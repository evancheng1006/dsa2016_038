#include<bits/stdc++.h>
using namespace std;

int n;

void re(int i, stack<int> st, vector<int> out) {
	if (i > n) {
		return;
	}	
	if (i == n) {
		while(!st.empty()) {
			out.push_back(st.top());
		}
			for (unsigned int i = 0; i < out.size(); i++) {
				cout << out[i] << ' ';
			}
		return;
	}
	
	st.push(i);
	re(i+1, st, out);
	st.pop();


	if (!st.empty()) {
		out.push_back(st.top());
		st.pop();
		st.push(i);
		re(i+1, st, out);
	}
}

int main() {
	cin >> n;
	stack<int> st;
	vector<int> out;
	re(1, st, out);
	
	return 0;
}
