#include <random>
#include <iostream>

const int n = 10;

int main() {
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> commandDist(0, 5);
	std::uniform_int_distribution<std::mt19937::result_type> itemDist(0, 100);

	std::cout << n << std::endl;
	
    for (int i = 0; i<n; i++) {
		switch (commandDist(rng)) {
			case 0:
				std::cout << 'F' << ' ' << itemDist(rng) << std::endl;
				break;
			case 1:
				std::cout << 'B' << ' ' << itemDist(rng) << std::endl;
				break;
			case 2:
				std::cout << 'f' << std::endl;
				break;
			case 3:
				std::cout << 'b' << std::endl;
				break;
			case 4:
				std::cout << 'R' << ' ' << itemDist(rng) << ' ' << itemDist(rng) << std::endl;
				break;
			case 5:
				std::cout << 'S' << std::endl;
				break;
		}
	}
}
