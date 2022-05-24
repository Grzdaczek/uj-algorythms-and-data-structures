#include <iostream>
#include <stack>
#include <functional>

template<typename T>
class BinaryTree;

template<typename T>
class BinaryNode {
public:
	friend BinaryTree<T>;
	using Node = BinaryNode<T>;

	T value;
	Node* left;
	Node* right;

	BinaryNode(const T& x)
		: value(x)
		, left(nullptr)
		, right(nullptr)
	{}

	BinaryNode(T&& x)
		: value(std::move(x))
		, left(nullptr)
		, right(nullptr)
	{}
	
	BinaryNode(const BinaryNode& other)
		: value(other.value)
		, left(nullptr)
		, right(nullptr)
	{
		if (other.left != nullptr) left = new Node(*other.left);
		if (other.right != nullptr) right = new Node(*other.right);
	}

	BinaryNode(BinaryNode&& other)
		: value(std::move(other.value))
		, left(other.left)
		, right(other.right)
	{
		other.left = nullptr;
		other.right = nullptr;
	}

	~BinaryNode() {
		delete left;
		delete right;
	}
};

template<typename T>
class BinaryTree {
private:
	using Node = BinaryNode<T>;

	Node* mRoot = nullptr;
	int mSize = 0;
	int mDepth = 0;

public:
	BinaryTree() = default;
	
	~BinaryTree() {
		delete mRoot;
	}

	template<typename R>
	void insert(R&& x) {
		Node** node = &mRoot;
		int depth = 0;

		while (*node != nullptr) {
			depth += 1;

			if ((*node)->value > x)
				node = &(*node)->left;
			else
				node = &(*node)->right;
		}

		*node = new Node(std::forward<R>(x));
		mSize += 1;
		mDepth = std::max(mDepth, depth + 1);
	}

	Node* search(T& x) {
		Node *n = mRoot;
		auto s = std::stack<Node*>();
		s.push(n);

		while(!s.empty()) {
			while (n) {
				s.push(n);
				n = n->left;
			}
			
			if (!n) {
				n = s.top();

				if (n->value == x)
					return n;
				
				n = n->right;
				s.pop();
			}
		}

		return nullptr;
	}

	Node* searchRecursive(T& x) {
		std::function<Node*(Node*)> s;
		s = [&s, &x](Node* node) {
			if (!node || node->value == x) return node;

			Node * n;

			n = s(node->left);
			if (n) return n;

			n = s(node->right);
			if (n) return n;

			return (Node*) nullptr;
		};

		return s(mRoot);
	}

	int size() {
		return mSize;
	}

	using __GoToNext = std::function<void(Node*)>;
	void traverse(std::function<void(Node*, __GoToNext)> handler) {
		__GoToNext go;

		go = [&handler, &go](auto node) {
			if (node) handler(node, go);
		};

		go(mRoot);
	}

	const T& minimum() {
		const Node* min = mRoot;

		traverse([&min](auto node, auto go) {
			min = node;
			go(node->left);
		});

		return min->value;
	}

	const T& maximum() {
		const Node* max = mRoot;

		traverse([&max](auto node, auto go) {
			max = node;
			go(node->right);
		});

		return max->value;
	}

	int depth() {
		return mDepth;
	}
	
	void inorder() {
		traverse([](auto node, auto go) {
			go(node->left);
			std::cout << node->value << std::endl;
			go(node->right);
		});
	}
	
	void preorder() {
		traverse([](auto node, auto go) {
			std::cout << node->value << std::endl;
			go(node->left);
			go(node->right);
		});
	}
	
	void postorder() {
		traverse([](auto node, auto go) {
			go(node->left);
			go(node->right);
			std::cout << node->value << std::endl;
		});
	}
};