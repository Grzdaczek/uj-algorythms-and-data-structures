#include <iostream>
#include <sstream>
#include <vector>
#include <functional>
#include <cmath>
#include "LinkedQueue.hpp"
// #include "ArrayQueue.hpp"

template<typename T, size_t C, int N, int S = 256>
void radix(
	std::vector<T>& v,
	std::function<int(const T&, int key)> value_fn
) {
	Queue<T, S> buckets[C];

	for (int key = 0; key < N; key++) {
		
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
	std::vector<int> v;
	while (std::cin >> n)
		v.push_back(n);

	auto value_fn = [](const auto& element, auto key) {
		int position = std::pow(10, key);
		int category = static_cast<int>(element / position) % 10;
		return category;
	};

	radix<int, 10, 9>(v, value_fn);
	
	for(const auto& i : v)
		std::cout << i << std::endl;
}
