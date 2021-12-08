#include <iostream>
#include <vector>

template<class T>
void sort(std::vector<T> &v) {
	// TODO: implement
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