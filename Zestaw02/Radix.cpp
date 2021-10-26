#include <iostream>
#include <vector>
#include <functional>
#include <cmath>
#include "ArrayQueue.hpp"
// #include "LinkedQueue.hpp"

template<typename T, int C, int N, int S = 256>
void radix(
	std::vector<T>& v, 
	std::function<int(const T&, int key)> category_fn
) {
	Queue<T, S> buckets[C];
	Queue<T, S> tmp;
	for (auto el : v) tmp.push(el);
	
	for (int key = 0; key < N; key++) {

		while (tmp.size() != 0) {
			const T& el = tmp.top();
			int category = category_fn(el, key);
			buckets[category].push(el);
			tmp.pop();
		}
		
		for (auto& bucket : buckets) {
			while (bucket.size()) {
				tmp.push(bucket.top());
				bucket.pop();
			}
		}
	}

	for (auto& el : v) {
		el = tmp.top();
		tmp.pop();
	}
}

int main() {

	std::vector<int> v = {63, 19, 10, 84, 48, 81, 29, 16, 64, 57};

	std::cout << "[";
	for(const auto& el : v) std::cout << el << ",";
	std::cout << "]" << std::endl;

	auto fn = [](auto element, auto key) {
		int position = std::pow(10, key);
		int category = static_cast<int>(element / position) % 10;
		return category;
	};

	radix<int, 10, 3>(v, fn);

	std::cout << "[";
	for(const auto& el : v) std::cout << el << ",";
	std::cout << "]" << std::endl;
}
