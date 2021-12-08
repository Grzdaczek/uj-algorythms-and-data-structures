#include <iostream>
#include <vector>

template<class T>
void sort(std::vector<T> &v) {
	for (int k = 0; k < (int)v.size(); ++k) {
		int min = k;
		
		for (int i = k + 1; i < (int)v.size(); ++i)
			if (v[min] > v[i])
				min = i;

		std::swap(v[k], v[min]);
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