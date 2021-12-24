#include <iostream>
#include <stack>
#include <functional>

template<typename T>
class BinaryIterator;

template<typename T>
class BinaryTree;

template<typename T>
class BinaryNode {
private:
	friend BinaryTree<T>;
	using Node = BinaryNode<T>;
	T mValue;
	Node* mLeft;
	Node* mRight;

public:
	BinaryNode(const T& x)
		: mValue(x)
		, mLeft(nullptr)
		, mRight(nullptr)
	{}

	BinaryNode(T&& x)
		: mValue(std::move(x))
		, mLeft(nullptr)
		, mRight(nullptr)
	{}
	
	BinaryNode(const BinaryNode& other)
		: mValue(other.mValue)
		, mLeft(nullptr)
		, mRight(nullptr)
	{
		if (other.mLeft != nullptr) mLeft = new Node(*other.mLeft);
		if (other.mRight != nullptr) mRight = new Node(*other.mRight);
	}

	BinaryNode(BinaryNode&& other)
		: mValue(std::move(other.mValue))
		, mLeft(other.mLeft)
		, mRight(other.mRight)
	{
		other.mLeft = nullptr;
		other.mRight = nullptr;
	}

	~BinaryNode() {
		delete mLeft;
		delete mRight;
	}

	const BinaryNode* left() const {
		return mLeft;
	}

	const BinaryNode* right() const {
		return mRight;
	}

	const T& value() const {
		return mValue;
	}
};

template<typename T>
class BinaryIterator {
private:
// 	using Node = BinaryNode<T>;

// 	std::vector<Node*> mStack;

// public:
// 	BinaryIterator(const BinaryTree<T>& tree) {
// 		if (tree.mRoot == nullptr)
// 			return;

// 		Node* node = tree.mRoot;

// 		do {
// 			mStack.push(node);
// 			node = node->mLeft;
// 		} while (node);

// 	}
};

template<typename T>
class BinaryTree {
private:
	using Node = BinaryNode<T>;
	friend BinaryIterator<T>;

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

		while (*node) {
			depth += 1;

			if ((*node)->mValue > x)
				node = &(*node)->mLeft;
			else
				node = &(*node)->mRight;
		}

		*node = new Node(std::forward<R>(x));
		mSize += 1;
		mDepth = std::max(mDepth, depth + 1);
	}

	Node* search(T& a) {
		return nullptr;
	};

	Node* searchRecursive(T& a);

	int size() {
		return mSize;

	};

	using __GoToNext = std::function<void(const Node*)>;

	void traverse(std::function<void(const Node*, __GoToNext)> handler) {
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
			go(node->left());
		});

		return min->value();
	};

	const T& maximum() {
		const Node* max = mRoot;

		traverse([&max](auto node, auto go) {
			max = node;
			go(node->right());
		});

		return max->value();
	};

	int depth() {
		return mDepth;
	};
	
	void inorder() {
		traverse([](auto node, auto go) {
			go(node->left());
			std::cout << node->value() << std::endl;
			go(node->right());
		});
	};
	
	void preorder() {
		traverse([](auto node, auto go) {
			std::cout << node->value() << std::endl;
			go(node->left());
			go(node->right());
		});
	};
	
	void postorder() {
		traverse([](auto node, auto go) {
			go(node->left());
			go(node->right());
			std::cout << node->value() << std::endl;
		});
	};
};