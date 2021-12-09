#include <iostream>
#include <vector>

template<class T>
int sort(std::vector<T> &v) {
	int counter = 0;

	for (int k = 0; k < (int)v.size(); ++k) {
		int min = k;
		
		for (int i = k + 1; i < (int)v.size(); ++i) {
			if (v[min] > v[i])
				min = i;

			++counter;
		}

		std::swap(v[k], v[min]);
	}

	return counter;
}

int main() {
	float x;
	std::vector<float> v;

	while (std::cin >> x)
		v.push_back(x);

	std::cout << sort(v);
}