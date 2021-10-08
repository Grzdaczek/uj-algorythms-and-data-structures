#include <iostream>
#include "ArrayStack.hpp"

int main() {

    Stack stack(10);
    stack.push(3);
    stack.push(2);

    std::cout << stack.pop() << ", " << stack.pop() << std::endl;

}
