#include <iostream>
#include <vector>
#include <functional>
#include <cmath>
#include "LinkedQueue.hpp"
// #include "ArrayQueue.hpp"

template<typename T, size_t C, int N, int S = 256>
void radix(
	std::vector<T>& v,
	std::function<int(const T&, int key)> category_fn
) {
	Queue<T, S> buckets[C];

	for (int key = 0; key < N; key++) {
		
		for (auto& item : v) {
			int i = category_fn(item, key);
			buckets[i].push(std::move(item));
		}

		int i = 0;
		for (auto& b : buckets) {
			while (b.size()) {
				v[i] = std::move(b.top());
				b.pop();
				i ++;
			}
		}
	}
}

int main() {

	std::vector<int> v = {63, 19, 10, 84, 48, 81, 29, 16, 64, 57};

	auto fn = [](const auto& element, auto key) {
		int position = std::pow(10, key);
		int category = static_cast<int>(element / position) % 10;
		return category;
	};

	radix<int, 10, 3>(v, fn);

	std::cout << "[ ";
	for(const auto& el : v) std::cout << el << " ";
	std::cout << "]" << std::endl;
}
