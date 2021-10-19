#include <iostream>
#include "LinkedStack.hpp"
// #include "ArrayStack.hpp"

bool isnumber(std::string& s) {
	for (auto&& c : s)
		if (!std::isdigit(c)) return false;
	return true;
}

int main(int argc, char* argv[]) {
	Stack<char, 512> opstack;

	for (int i=1; i<argc; i++) {
		std::string symbol = argv[i];
		
		if (isnumber(symbol)) {
			std::cout << symbol << " ";
		}
		else if (symbol != "(" && symbol != ")") {
			opstack.push(symbol.at(0));
		}
		else if (symbol == ")") {
			std::cout << opstack.pop();
			if (!opstack.empty()) std::cout << " ";
		}
	}
}
