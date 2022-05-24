#include "Dict.hpp"
#include <iostream>
#include <utility>
#include <fstream>

int main(int argc, char* argv[]) {
	auto dict = Dictionary<std::string, std::string>();

	if (argc < 2)
		throw std::invalid_argument("File path not provided");

	auto f = std::ifstream(argv[1]);

	std::string key, value;
	while (f >> key >> value)
		dict.set(key, value);

	while (std::cin >> key)
		std::cout << (dict.has(key) ? dict.get(key) : "-") << std::endl;
}