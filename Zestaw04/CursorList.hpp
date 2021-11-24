#include "iterator.hpp"

#include <stdexcept>
#include <cassert>

template<typename T>
class CursorList {
private:
	struct mEmptyNode {
		int next;
		mEmptyNode() : next(-1) {}
	};

	struct mValueNode {
		int next;
		T value;
		mValueNode() = delete;
		mValueNode(const T& v) : next(-1), value(v) {}
		mValueNode(T&& v) : next(-1), value(std::move(v)) {}
	};

	union mNode {
		mValueNode as_value;
		mEmptyNode as_empty;
		mNode() : as_empty(mEmptyNode()) {}
	};

	class mIterator {
		int m_index;

		mIterator() : m_index(0) {}
		mIterator(int index) : m_index(index) {}

		T& operator*() const {
			return CursorList::sData[m_index].as_value.value;
		}

		bool operator==(const mIterator& other) const {
			return m_index == other.m_index;
		}

		mIterator& operator++() {
			m_index = CursorList::sData[m_index].as_value.next;
			return *this;
		}
	};

	inline static mNode* sData = nullptr;
	inline static int sCapacity;
	inline static int sSize;
	inline static int sEmpty;

	int mHead;
	int mTail;
	int mSize;

public:
	using Iterator = nsd::Iterator<mIterator, T>;
	using ConstIterator = nsd::ConstIterator<mIterator, T>;

	static void alloc(int size) {
		sCapacity = size;
		sEmpty = 0;
		sSize = 0;
		sData = new mNode[sCapacity];

		for (int i = 0; i < sCapacity - 1; ++i)
			sData[i].as_empty.next = i + 1;
	}

	static void free(int size) {
		delete[] sData;
		sData = nullptr;
		sCapacity = 0;
		sSize = 0;
	}

	static void grow(int size) {
		// TODO: implement
	}

	static void shrink(int size) {
		// TODO: implement
	}

	static int size() {
		return sSize;
	}

	static int capacity() {
		return sCapacity;
	}

	static bool full() {
		return sSize == sCapacity;
	}

	static bool empty() {
		return sSize = 0;
	}

	#if !NDEBUG
	static std::string __to_string__() {
		std::basic_stringstream<char> s;
		s << "capac.:\t" << sCapacity << std::endl;
		s << "size:\t" << sSize << std::endl;
		s << "empty:\t" << sEmpty << std::endl;
		s << "data: [" << std::endl;

		for (int i = 0; i < sCapacity; i++)
			s << "\t" << i << ": " << sData[i].as_empty.next << std::endl;

		s << "]" <<std::endl;

		return s.str();
	}
	#endif

	CursorList() {
		if (!sData)
			throw new std::out_of_range("");

		mHead = -1;
		mTail = -1;
	}

	~CursorList() {
		// TODO: implement
	}

	Iterator begin() {
		return Iterator(mIterator(mHead));
	}
	
	ConstIterator begin() const {
		return ConstIterator(mIterator(mHead));
	}

	Iterator end() {
		return Iterator(mIterator(-1));
	}
	
	ConstIterator end() const {
		return ConstIterator(mIterator(-1));
	}

	template<typename U>
	Iterator insert(U&& x) {
		// TODO: implement
	}

};
