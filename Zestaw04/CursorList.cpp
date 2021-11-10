#include <iostream>
#include <sstream> 
#include "CursorList.hpp"

int main() {
	CursorList<int> list;
	auto l = list.create();

	for (auto n : list.__emptyList()) {
		std::cout << n << std::endl;
	}
	
}
