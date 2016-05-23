#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

int main() {


	std::ios::sync_with_stdio(false);

	unsigned int m;
	std::vector<float> pitch;
	unsigned int n;
	std::vector<float> note;

	float distance;
	std::vector<unsigned int> startingIndex;

	// input
	std::cin >> m;
	pitch.clear();
	pitch.reserve(m);
	for (unsigned int i = 0; i < m; i++) {
		float tmp;
		std::cin >> tmp;
		pitch.push_back(tmp);
	}
	std::cin >> n;
	note.clear();
	note.reserve(n);
	for (unsigned int j = 0; j < n; j++) {
		float tmp;
		std::cin >> tmp;
		note.push_back(tmp);
	}

#if DEBUG==1
	std::cout << "Print input:\n";
	std::cout << "    m: " << m << "\n";
	for (unsigned int i = 0; i < m; i++) {
		std::cout << i << ' ' << pitch[i] << "\n";
	}
	std::cout << "    n: " << n << "\n";
	for (unsigned int j = 0; j < n; j++) {
		std::cout << j << ' ' << note[j] << "\n";
	}
#endif


	// DP
	std::vector<float> distanceList;
	distanceList.resize(m * n);
	std::vector<unsigned int> prevJ;
	prevJ.reserve(m * n);

	distanceList[0] = std::abs(pitch[0] - note[0]);
	for (unsigned int i = 1; i < m; i++) {
		distanceList[i * n] = std::abs(pitch[i] - note[0]) + distanceList[(i - 1) * n];
		prevJ[i * n] = 0;
	}
	for (unsigned int j = 1; j < n; j++) {
		distanceList[j] = INFINITY;
	}
	for (unsigned int i = 1; i < m; i++) {
		for (unsigned int j = 1; j < n; j++) {
			float min;
			if (distanceList[(i - 1) * n + j] < distanceList[(i - 1) * n + (j - 1)]) {
				min = distanceList[(i - 1) * n + j];
				prevJ[i * n + j] = j;
			} else {
				min = distanceList[(i - 1) * n + (j - 1)];
				prevJ[i * n + j] = j - 1;
			}
			distanceList[i * n + j] = std::abs(pitch[i] - note[j]) + min;
		}
	}

	unsigned int startingTraceBackPoint;
	startingTraceBackPoint = 0;
	distance = startingTraceBackPoint;
	distance = distanceList[(m - 1) * n + 0];

	for (unsigned int j = 1; j < n; j++) {
		if (distanceList[(m - 1) * n + j] < distance) {
			distance = distanceList[(m - 1) * n + j];
			startingTraceBackPoint = j;
		}
	}

	std::vector<unsigned int> routeList;
	routeList.resize(m);
	unsigned int currentJ = startingTraceBackPoint;
	for (unsigned currentI = m - 1; currentI > 0; currentI--) {
		routeList[currentI] = currentJ;
		currentJ = prevJ[currentI * n + currentJ];
	}
	routeList[0] = 0;

	startingIndex.clear();
	startingIndex.push_back(0);
	for (unsigned int currentI = 1; currentI < m; currentI++) {
		if (routeList[currentI] != routeList[currentI - 1]) {
			startingIndex.push_back(currentI);
		}
	}
	
	// output
	std::cout << distance << "\n";
	unsigned int startingIndexSize = startingIndex.size();
	for (unsigned int i = 0; i < startingIndexSize; i++) {
		std::cout << startingIndex[i] << ' ';
	}
	std::cout << "\n";

	return 0;
}

