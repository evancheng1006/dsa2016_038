#ifndef MINHEAP_H
#define MINHEAP_H

#include <vector>

template <class type>
class MinHeap {
private:

public:
	std::vector<type> data;
	MinHeap();
	~MinHeap();
	unsigned int size();
	bool empty();
	void insert(const type & obj);
	type min();
	void removeMin();
};

template <class type>
MinHeap<type>::MinHeap() {
	data.resize(1);
}

template <class type>
MinHeap<type>::~MinHeap() {
	// do nothing
}

template <class type>
unsigned int MinHeap<type>::size() {
	return (data.size() - 1);
}
template <class type>
bool MinHeap<type>::empty() {
	if (data.size() <= 1) {
		return true;
	}
	return false;
}

template <class type>
void MinHeap<type>::insert(const type & obj) {
	unsigned int curr = data.size();
	data.push_back(obj);
	while (curr > 1) {
		if (data[curr] < data[curr/2]) {
			type tmp = data[curr/2];
			data[curr/2] = data[curr];
			data[curr] = tmp;
			curr /= 2;
		} else {
			curr = 1;
		}
	}
	return;
}

template <class type>
type MinHeap<type>::min() {
	if (data.size() > 1) {
		return data[1];
	}
	return data[0];
}

template <class type>
void MinHeap<type>::removeMin() {
	if (data.size() == 1) {
		return;
	}
	data[1] = data.back();
	data.pop_back();

	unsigned int curr = 1;
	while (curr < data.size()) {
		unsigned int smaller = curr;
		if (curr * 2 < data.size()) {
			smaller = curr * 2;
		}
		if (curr * 2 + 1 < data.size()) {
			if (data[curr * 2 + 1] < data[curr * 2]) {
				smaller = curr * 2 + 1;
			}
		}
		if (data[smaller] < data[curr]) {
			type tmp = data[curr];
			data[curr] = data[smaller];
			data[smaller] = tmp;
			curr = smaller;
		} else {
			curr = data.size();
		}
	}
	return;
}

#endif
