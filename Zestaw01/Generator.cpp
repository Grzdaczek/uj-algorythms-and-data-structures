#include <random>
#include <iostream>

const int n = 10;

int main() {
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> commandDist(0, 2);
	std::uniform_int_distribution<std::mt19937::result_type> itemDist(0, 100);

	for (int i = 0; i<n; i++) {
		switch (commandDist(rng)) {
			case 0:
				std::cout << 'A' << ' ' << itemDist(rng) << std::endl;
				break;
			case 1:
				std::cout << 'D' << std::endl;
				break;
			case 2:
				std::cout << 'S' << std::endl;
				break;
		}
	}
}