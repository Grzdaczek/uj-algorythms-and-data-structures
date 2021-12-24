#include <iostream>
#include "BinaryTree.hpp"

int main() {
	int x;
	auto tree = BinaryTree<int>();

	while(std::cin >> x)
		tree.insert(x);

	std::cout
		<< tree.size() << " "
		<< tree.depth() << " "
		<< tree.minimum() << " "
		<< tree.maximum() << std::endl;
	
	tree.inorder();

	for (int i = 1; i < 10; i++)
		std::cout << (tree.search(i) ? "Yes" : "No") << std::endl;
}