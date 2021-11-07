#include <iostream>
#include <sstream> 
#include "ArrayList.hpp"

class S {
public:
	int m_value = 0;

	S() {
		std::cout << "\t--created" << std::endl;
	}
	
	S(int v) : m_value(v) {
		std::cout << "\t--created" << std::endl;
	}

	S(const S& other) : m_value(other.m_value) {
		std::cout << "\t--copied con" << std::endl;
	}
	
	S(S&& other) : m_value(other.m_value) {
		other.m_value = 0;
		std::cout << "\t--moved con" << std::endl;
	}

	~S() {
		std::cout << "\t--destroyed" << std::endl;
	}

	S operator=(const S& other) {
		this->m_value = other.m_value;
		std::cout << "\t--copied op" << std::endl;
		return *this;
	}

	S operator=(S&& other) {
		this->m_value = other.m_value;
		other.m_value = 0;
		std::cout << "--moved op" << std::endl;
		return *this;
	}
};

int main() {
	List<int> list;

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
					list.erase(it);
					list.insert(it, y);
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
