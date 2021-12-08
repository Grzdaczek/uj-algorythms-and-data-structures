#include <random>
#include <iostream>
#include <sstream>

int main(int argc, char* argv[]) {
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_real_distribution<> dist(0, 1);

	int n = 0;

	if (argc >= 2) {
		std::istringstream ss(argv[1]);
		ss >> n;
	}

	for (int i = 0; i < n; ++i)
		std::cout << dist(rng) << std::endl;
}
