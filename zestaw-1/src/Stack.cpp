#include <iostream>
#include "ArrayStack.hpp"
// #include "LinkedStack.hpp"

int main() {

	Stack stack(10);
	
	std::cout << "size: " << stack.size() << std::endl;
	
	std::cout << "push: 2, 3" << std::endl;
	stack.push(2);
	stack.push(3);

	std::cout << "size: " << stack.size() << std::endl;
	
	std::cout << "empty: " << stack.empty() << std::endl;
	
	std::cout << "pop: " << stack.pop() << ", " << stack.pop() << std::endl;
	std::cout << "size: " << stack.size() << std::endl;
	std::cout << "empty: " << stack.empty() << std::endl;

}
