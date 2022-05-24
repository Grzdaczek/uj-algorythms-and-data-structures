#include <iostream>
#include <sstream> 
#include "CursorList.hpp"

int main() {
	CursorList<int>::alloc(64);
	CursorList<int> list;

	std::string line;
	std::getline(std::cin, line);
    int op = std::stoi(line);


	for(int i = 0; i < op; i++) {
		std::getline(std::cin, line);
		std::stringstream line_stream(line); 
		
		std::string arg; 

		#define fetch_arg(x) std::getline(line_stream, x, ' ');
		fetch_arg(arg);
		
		char command = arg.at(0);

		switch (command) {
			// 
			case 'F': {
				fetch_arg(arg);
				int value = std::stoi(arg);
				list.push_front(value);
				break;
			}
			//
			case 'B': {
				fetch_arg(arg);
				int value = std::stoi(arg);
				list.push_back(value);
				break;
			}
			// f - usuń z listy pierwszy element i go wypisz, jeśli lista jest pusta wypisz “EMPTY”
			case 'f': {
				if (list.empty()) {
					std::cout << "EMPTY" << std::endl;
				}
				else {
					std::cout << list.pop_front() << std::endl;
				}
				
				break;
			}
			// b - usuń z listy ostatni element i go wypisz, jeśli lista jest pusta wypisz “EMPTY”
			case 'b': {
				if (list.empty()) {
					std::cout << "EMPTY" << std::endl;
				}
				else {
					std::cout << list.pop_back() << std::endl;
				}

				break;
			}
			// R x y - jeżeli x nie jest obecny w liście wypisz FALSE, w przeciwnym razie zastąp pierwsze
			// wystąpienie wartości x przez y i wypisz TRUE (ang. replace)
			case 'R': {
				fetch_arg(arg);
				int x = std::stoi(arg);

				fetch_arg(arg);
				int y = std::stoi(arg);

				auto it = list.find(x); 
				if (it != list.end()) {
					list.insert(it, y);
					list.erase(it);
					std::cout << "TRUE" << std::endl;
				}
				else {
					std::cout << "FALSE" << std::endl;
				}
				
				break;
			}
			// S - wypisz rozmiar listy
			case 'S': {
				std::cout << list.size() << std::endl;
				break;
			}

			default: {
				throw std::invalid_argument("no match for command");
				break;
			}
		}
	}
}
