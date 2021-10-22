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

    std::string o = "";

	for (std::string symbol : symbols) {
		if (isnumber(symbol)) {
            o.append(symbol + " ");
		}
		else if (symbol != "(" && symbol != ")") {
			opstack.push(symbol.at(0));
		}
		else if (symbol == ")") {
            o.append(1, opstack.pop());
            o.append(" ");
		}
	}

    o.pop_back();
    std::cout << o << std::endl;
}
