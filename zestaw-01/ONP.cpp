#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

#include "LinkedStack.hpp"
// #include "ArrayStack.hpp"

bool isnumber(std::string& s) {
	for (auto&& c : s)
		if (!std::isdigit(c)) return false;
	return true;
}

int main() {
	Stack<char, 512> opstack;
	std::vector<std::string> symbols;

	std::copy(
		std::istream_iterator<std::string>(std::cin),
		std::istream_iterator<std::string>(),
		std::back_inserter(symbols)
	);

	for (std::string symbol : symbols) {
		if (isnumber(symbol)) {
			std::cout << symbol << " ";
		}
		else if (symbol != "(" && symbol != ")") {
			opstack.push(symbol.at(0));
		}
		else if (symbol == ")") {
			std::cout << opstack.pop() << (opstack.empty() ? "\n" : " ");
		}
	}
}
