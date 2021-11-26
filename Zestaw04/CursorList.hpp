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
		mValueNode asValue;
		mEmptyNode asEmpty;
		mNode() : asEmpty(mEmptyNode()) {}
	};

	struct mIterator {
		int mIndex;

		mIterator() : mIndex(0) {}
		mIterator(int index) : mIndex(index) {}

		T& operator*() const {
			return CursorList::sData[mIndex].asValue.value;
		}

		bool operator==(const mIterator& other) const {
			return mIndex == other.mIndex;
		}

		mIterator& operator++() {
			mIndex = CursorList::sData[mIndex].asValue.next;
			return *this;
		}

		mIterator& operator--() {
			for (int i = 0; i < sCapacity; ++i) {
				if (sData[i].asEmpty.next == mIndex) {
					mIndex = i;
					return *this;
				}
			}

			mIndex = -1;
			return *this;
		}
	};

	inline static mNode* sData = nullptr;
	inline static int sCapacity;
	inline static int sSize;
	inline static int sEmpty;

	int mSize;
	int mHead;
	int mTail;

	static mEmptyNode& emptyAt(int i) {
		return sData[i].asEmpty;
	}

	static mValueNode& valueAt(int i) {
		return sData[i].asValue;
	}

public:
	using Iterator = nsd::Iterator<mIterator, T>;
	using ConstIterator = nsd::ConstIterator<mIterator, T>;

	static void alloc(int size) {
		sCapacity = size;
		sEmpty = 0;
		sSize = 0;
		sData = new mNode[sCapacity];

		for (int i = 0; i < sCapacity - 1; ++i)
			sData[i].asEmpty.next = i + 1;
	}

	static void free(int size) {
		delete[] sData;
		sData = nullptr;
		sCapacity = 0;
		sSize = 0;
	}

	static void grow(int size) {
		// TODO: implement
		throw new std::out_of_range("Well.. it seems grow is not yet implemented");
	}

	static void shrink(int size) {
		// TODO: implement
	}

	static int totalSize() {
		return sSize;
	}

	static int capacity() {
		return sCapacity;
	}

	static bool full() {
		return sSize == sCapacity;
	}

	static bool totalEmpty() {
		return sSize = 0;
	}

	#if !NDEBUG
	std::string __to_string__() {
		std::basic_stringstream<char> s;
		s << "mHead:\t" << mHead << std::endl;
		s << "mTail:\t" << mTail << std::endl;
		s << "sCapac:\t" << sCapacity << std::endl;
		s << "sSize:\t" << sSize << std::endl;
		s << "sEmpty:\t" << sEmpty << std::endl;
		s << "sData:\t[" << std::endl;

		for (int i = 0; i < sCapacity; i++)
			s << "\t" << i << " > "
				<< valueAt(i).next << ": "
				<< valueAt(i).value << std::endl;

		s << "]" <<std::endl;

		return s.str();
	}
	#endif

	CursorList()
		: mSize(0)
		, mHead(-1)
		, mTail(-1)
	{
		if (!sData)
			throw new std::out_of_range("");
	}

	CursorList(const CursorList& other)
		: mSize(0)
		, mHead(-1)
		, mTail(-1)
	{
		for (auto el : other)
			push_back(el);
	}

	CursorList(CursorList&& other)
		: mSize(other.mSize)
		, mHead(other.mHead)
		, mTail(other.mTail)
	{
		other.mSize = 0;
		other.mHead = -1;
		other.mTail = -1;
	}

	CursorList& operator=(const CursorList& other) {
		clear();

		for (auto el : other)
			push_back(el);
	}

	CursorList& operator=(CursorList&& other) {
		clear();

		mSize = other.mSize;
		mHead = other.mHead;
		mTail = other.mTail;

		other.mSize = 0;
		other.mHead = -1;
		other.mTail = -1;
	}

	~CursorList() {
		clear();
	}

	Iterator begin() {
		return Iterator(mIterator(mHead));
	}

	ConstIterator begin() const {
		return ConstIterator(mIterator(mHead));
	}

	Iterator last() {
		return Iterator(mIterator(mTail));
	}

	ConstIterator last() const {
		return ConstIterator(mIterator(mTail));
	}

	Iterator end() {
		return Iterator(mIterator(-1));
	}

	ConstIterator end() const {
		return ConstIterator(mIterator(-1));
	}

	template<class U>
	void push_front(U&& x) {
		auto it = begin();
		insert(it, std::forward<U>(x));
	}

	template<class U>
	void push_back(U&& x) {
		auto it = end();
		insert(it, std::forward<U>(x));
	}

	T pop_front() {
		auto it = begin();
		T element = *it;
		erase(it);
		return element;
	}

	T pop_back() {
		auto it = last();
		T element = *it;
		erase(it);
		return element;
	}

	Iterator find(const T& x) {
		for (auto it = begin(); it != end(); ++it) {
			if (*it == x)
				return it;
		}

		return end();
	}

	ConstIterator find(const T& x) const {
		for (auto it = begin(); it != end(); ++it) {
			if (*it == x)
				return it;
		}

		return end();
	}

	int remove(const T& x) {
		if (empty())
			return 0;

		int n = 0;
		auto it = end();
		do {
			--it;
			if (*it == x) {
				erase(it);
				n++;
			}
		} while (it != begin());

		return n;
	}

	template<typename U>
	Iterator insert(Iterator it, U&& x) {
		if (full()) grow(sSize * 2);

		// pop from stack of empty nodes, create new node
		int i = sEmpty;
		sEmpty = sData[i].asEmpty.next;
		new (&sData[i]) mValueNode(std::forward<U>(x));

		if (mSize == 0) {
			mHead = i;
			mTail = i;
		}
		else if (it == end()) {
			sData[mTail].asValue.next = i;
			mTail = i;
		}
		else if (it == begin()) {
			sData[i].asValue.next = mHead;
			mHead = i;
		}
		else {
			int j = (--it).unwrap().mIndex;
			sData[i].asValue.next = sData[j].asValue.next;
			sData[j].asValue.next = i;
		}

		++mSize;
		++sSize;
		return Iterator(mIterator(i));
	}

	Iterator erase(Iterator it) {
		int i = it.unwrap().mIndex;
		sData[i].asValue.value.~T();
		Iterator next = it;
		++next;

		if (mSize == 1) {
			mHead = -1;
			mTail = -1;
		}
		else if (it == begin()) {
			mHead = sData[i].asEmpty.next;
		}
		else if(it == last()) {
			int j = (--it).unwrap().mIndex;
			sData[j].asEmpty.next = -1;
			mTail = j;
		}
		else {
			int j = (--it).unwrap().mIndex;
			sData[j].asEmpty.next = sData[i].asEmpty.next;
		}

		sData[i].asEmpty.next = sEmpty;
		sEmpty = i;

		--mSize;
		--sSize;
		return next;
	}

	int size() const {
		return mSize;
	}

	bool empty() const {
		return size() == 0;
	}

	void clear() {
		while (!empty())
			erase(--end());

		assert(mSize == 0);
	}
};
