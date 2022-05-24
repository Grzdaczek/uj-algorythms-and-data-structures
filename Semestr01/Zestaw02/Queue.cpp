#include <iostream>
#include <cmath>
#include "LinkedQueue.hpp"
// #include "ArrayQueue.hpp"

int main() {
	Queue<int, 1000000> queue;
	std::string s;
	std::getline(std::cin, s);
    int op = std::stoi(s);

	for(int i = 0; i < op; i++) {
		std::getline(std::cin, s);
		char c;

		if (s.size()) 
			c = s.at(0);
		else 
			break;

		switch (c) {
			case 'A':
				queue.push(std::stoi(s.substr(1)));
				break;
			case 'D':
				try {
					std::cout << queue.top() << std::endl;
					queue.pop();
				}
				catch (std::exception const& e) {
					std::cout << "EMPTY" << std::endl;
				}
				break;
			case 'S':
				std::cout << queue.size() << std::endl;
				break;
			default:
				throw std::invalid_argument("no match for command");
				break;
		}
	}

}
