#include <iostream>
#include <vector>
#include "LinkedList.hpp"

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
	List<S> a;
	// List<S> b;

	std::cout << "------------------------ create" << std::endl;
	a.push_front(1);

	std::cout << "------------------------ copy" << std::endl;
	List<S> c(a);
	// List<S> c(std::move(a));

	std::cout << "------------------------ end" << std::endl;

	// a.size();
	// b.size();
	// std::cout << "------------------------" << std::endl;
	// a = std::move(b);

	// std::cout << "------------------------" << std::endl;

	// auto it = list.begin();
	// std::cout << "it: " << *it << std::endl; ++it;
	// std::cout << "it: " << *it << std::endl; ++it;
	// std::cout << "it: " << *it << std::endl; ++it;
	// std::cout << "it: " << *it << std::endl; ++it;
	// std::cout << "it: " << *it << std::endl; ++it;
	// std::cout << "it: " << *it << std::endl; ++it;
	
	// std::cout << "--- V ---" << std::endl;
	// for (auto it : list) std::cout << "it: " << it << std::endl;

	// list.erase(list.find("42"));
	// std::cout << list.remove("111") << std::endl;
	// std::cout << "pop: " <<  << std::endl;

	// list.clear();
	// list.push_back("CC");


	// std::cout << "--- V ---" << std::endl;
	// for (auto it : list) std::cout << "it: " << it << std::endl;

	return 0;

	/*

	std::string s;
	std::getline(std::cin, s);
    int op = std::stoi(s);

	// f - usuń z listy pierwszy element i go wypisz, jeśli lista jest pusta wypisz “EMPTY”
	// b - usuń z listy ostatni element i go wypisz, jeśli lista jest pusta wypisz “EMPTY”
	// R x y - jeżeli x nie jest obecny w liście wypisz FALSE, w przeciwnym razie zastąp pierwsze
	//         wystąpienie wartości x przez y i wypisz TRUE (ang. replace)
	// S - wypisz rozmiar listy

	for(int i = 0; i < op; i++) {
		std::getline(std::cin, s);
		auto fetch_arg = [s]() { return std::stoi(s.substr(1)); };
		char c;

		if (s.size()) 
			c = s.at(0);
		else 
			break;

		switch (c) {
			case 'F':
				list.push_front(fetch_arg());
				break;
			case 'B':
				list.push_back(fetch_arg());
				break;
			case 'f':
				std::cout << list.pop_front() << std::endl;
				break;
			case 'b':
				std::cout << list.pop_back() << std::endl;
				break;
            /*
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
			*/
	//	}
	//}
	

}
