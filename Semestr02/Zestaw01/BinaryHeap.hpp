#include <vector>
#include <iostream>

class Container {
protected:
	Container() {};

public:
	virtual unsigned int size() const = 0;
	virtual bool empty() const { return size() == 0; };
	virtual bool full() const = 0;
	virtual void clear() = 0;
};

template <typename T>
class PriorityQueue : public Container {
public:
	virtual void enqueue(T element) = 0;
	virtual const T& find_min() const = 0;
	virtual T dequeue_min() = 0;
};

template <typename T>
class BinaryHeap : public PriorityQueue<T> {
protected:
	std::vector<T> data;

public:
	BinaryHeap() = default;

	BinaryHeap(std::size_t n) {
		data.reserve(n);
	}

	~BinaryHeap() = default;

	void clear() {
		data.clear();
	}

	void enqueue(T element) {
		auto get_parent = [](int i) {
			int direction = (i & 1) ? 1 : 2;
			return (i - direction) / 2;
		};

		size_t index = data.size();
		data.push_back(element);

		while (true) {
			if (index == 0) break;

			size_t parent_index = get_parent(index);
			if (data.at(index) > data.at(parent_index)) break;

			std::swap(data.at(index), data.at(parent_index));
			index = parent_index;
		}
	}

	const T& find_min() const {
		return data.at(0); // err if empty
	}

	T dequeue_min() {
		T min = std::move(data.at(0));
		data.at(0) = std::move(data.at(data.size() - 1));
		data.pop_back();
		size_t current = 0;

		while (true) {
			size_t l_child = current * 2 + 1;
			size_t r_child = current * 2 + 2;
			size_t swap = current;

			if (l_child < data.size() && data.at(l_child) < data.at(swap)) {
				swap = l_child;
			}

			if (r_child < data.size() && data.at(r_child) < data.at(swap)) {
				swap = r_child;
			}

			if (swap == current) {
				break;
			}
			else {
				std::swap(data.at(current), data.at(swap));
				current = swap;
			}
		}

		return min;
	}

	bool full() const {
		return false;
	};

	unsigned int size() const {
		return data.size();
	}

	void __log__() {
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "\tsize:" << size();
		if (!this->empty()) std::cout << "\tmin:" << find_min();
		std::cout << std::endl << "\t";
		for (const auto& it : data) {
			std::cout << it << ", ";
		}
		std::cout << std::endl;
	}
};

