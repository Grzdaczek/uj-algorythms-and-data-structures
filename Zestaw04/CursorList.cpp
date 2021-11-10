#include <iostream>
#include <sstream> 
#include "CursorList.hpp"

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
	CursorList<S> list;
	auto l = list.create();
	// list.__emptyList().__print();
	l.__print();

	std::cout << "------------- 1" << std::endl;
	l.insert(l.begin(), 14);
	l.insert(l.begin(), 32);
	l.insert(l.end(), -9);
	l.insert(l.last(), 888);
	// list.__emptyList().__print();
	l.__print();

	std::cout << "------------- 2" << std::endl;
	std::cout << "------------- 3" << std::endl;
}
