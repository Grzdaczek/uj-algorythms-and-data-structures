#include <iostream>
#include "LinkedStack.hpp"
// #include "ArrayStack.hpp"

int main() {

	Stack<int, 10> stack;
	
	while(true) {
		std::string s;
		std::getline(std::cin, s);
		char c;
		if(s.size()) c = s.at(0);
		else break;

		switch (c) {
			case 'A':
				stack.push(std::stoi(s.substr(1)));
				break;
			case 'D':
				try {
					std::cout << stack.pop() << std::endl;
				}
				catch(std::exception const& e) {
					std::cout << "EMPTY" << std::endl;
				}
				break;
			case 'S':
				std::cout << stack.size() << std::endl;
				break;
			default:
				throw std::invalid_argument("no match for command");
				break;
		}
	}

}
