#include <iostream>
#include <sstream> 
#include "CursorList.hpp"

int main() {
	CursorList<int> list;
	auto l = list.create();
	list.__emptyList().__print();
	l.__print();

	std::cout << "------------- 1" << std::endl;
	l.insert(l.begin(), 14);
	l.insert(l.begin(), 32);
	l.insert(l.end(), -9);
	l.insert(l.last(), 888);
	list.__emptyList().__print();
	l.__print();

	std::cout << "------------- 2" << std::endl;
	std::cout << "------------- 3" << std::endl;
}
