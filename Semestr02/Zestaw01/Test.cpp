#include <cassert>
#include "BinaryHeap.hpp"

int main() {
	auto heap = BinaryHeap<int>(10);
	assert(heap.empty() == true);

	heap.enqueue(5);
	heap.__log__();
	assert(heap.empty() == false);

	heap.enqueue(6);
	heap.__log__();

	heap.enqueue(8);
	heap.__log__();

	heap.enqueue(3);
	heap.__log__();

	heap.enqueue(9);
	heap.__log__();

	heap.enqueue(2);
	heap.__log__();

	heap.enqueue(1);
	heap.__log__();

	heap.dequeue_min();
	heap.__log__();

	heap.dequeue_min();
	heap.__log__();

	heap.dequeue_min();
	heap.__log__();

	heap.clear();
	assert(heap.empty() == true);
}

