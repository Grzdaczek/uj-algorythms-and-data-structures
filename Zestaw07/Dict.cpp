#include "Dict.hpp"
#include <iostream>
#include <utility>

int main(int argc, char* argv[]) {
	auto dict = Dictionary<int, int>();

	dict.set(0, 42);
	dict.set(0, 20);
	dict.set(1024, 11);

	std::cout << dict.get(0) << std::endl;
	std::cout << dict.get(1024) << std::endl;
}