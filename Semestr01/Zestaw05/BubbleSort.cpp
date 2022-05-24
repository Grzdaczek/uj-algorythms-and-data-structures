#include <iostream>
#include <vector>

template<class T>
void sort(std::vector<T> &v) {
	for (int k = v.size() -1; k > 0; --k) {
		for (int i = 0; i < k; ++i) {
			if (v[i] > v[i+1])
				std::swap(v[i], v[i+1]);
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