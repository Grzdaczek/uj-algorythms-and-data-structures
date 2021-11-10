#include <iostream>
#include <sstream> 
#include "CursorList.hpp"

int main() {
	CursorList<int> list;
	auto l = list.create();
	list.__emptyList().__print();
}
