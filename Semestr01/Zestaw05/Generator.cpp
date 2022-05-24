#include <random>
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
	int n = std::stoi(argv[1]);
	int max = std::stoi(argv[2]);

	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<> dist(0, max);

	for (int i = 0; i < n; ++i)
		std::cout << dist(rng) << std::endl;
}
