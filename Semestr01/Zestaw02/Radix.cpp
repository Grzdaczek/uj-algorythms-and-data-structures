#include <iostream>
#include <sstream>
#include <vector>
#include <functional>
#include <cmath>
#include "LinkedQueue.hpp"
// #include "ArrayQueue.hpp"

template<typename T, size_t C, int S = 256>
void radix(
	std::vector<T>& v,
	std::function<int(const T&, int key)> value_fn,
	std::function<int(const T&)> keys_fn
) {
	Queue<T, S> buckets[C];

	auto max_keys = 0;
	for (const auto& item : v) {
		int x = keys_fn(item);
		if (x > max_keys) max_keys = x;
	}

	for (int key = 0; key < max_keys; key++) {
		
		for (auto& item : v) {
			int i = value_fn(item, key);
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

	int n;
	int max = 0;
	std::vector<int> v;
	while (std::cin >> n) {
		v.push_back(n);
		if (max > n) max = n;
	}

	auto value_fn = [](const auto& element, auto key) {
		int position = std::pow(10, key);
		int category = static_cast<int>(element / position) % 10;
		return category;
	};

	auto keys_fn = [](const auto& element) {
		int keys = 1;
		int el = element;
		while ((el /= 10) > 0) keys ++;
		return keys;
	};

	radix<int, 10>(v, value_fn, keys_fn);
	
	for(const auto& i : v)
		std::cout << i << std::endl;
}
