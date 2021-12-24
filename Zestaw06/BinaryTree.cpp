#include <iostream>
#include "BinaryTree.hpp"

int main() {
	int x;
	int len = 0;
	auto tree = BinaryTree<int>();

	std::cin >> len;

	for (int i = 0; i < len; ++i) {
		std::cin >> x;
		tree.insert(x);
	}

	std::cout
		<< tree.size() << " "
		<< tree.depth() << " "
		<< tree.minimum() << " "
		<< tree.maximum() << std::endl;
	
	tree.preorder();

	for (int i = 1; i < 10; i++)
		std::cout << (tree.search(i) ? "Yes" : "No") << std::endl;
}