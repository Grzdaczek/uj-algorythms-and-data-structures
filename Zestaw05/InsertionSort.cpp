#include <iostream>
#include <vector>

template<class T>
void sort(std::vector<T> &v) {
	for (int k = 0; k < (int)v.size() - 1; ++k) {
		int i = k + 1;

		while (i > 0 && v[i-1] > v[i]) {
			std::swap(v[i-1], v[i]);
			i--;
		}
	}
}

int main() {
	float x;
	std::vector<float> v;

	while(std::cin >> x)
		v.push_back(x);

	sort(v);

	for(const auto& i : v)
		std::cout << i << std::endl;

}