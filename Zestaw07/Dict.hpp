#include <utility>
#include <vector>
#include <algorithm>
#include <cstring>
#include <iostream>

template<typename K, typename V>
class Dictionary {
public:
	using Entry = std::pair<K, V>;
	using Bucket = std::vector<Entry>;

private:
	size_t mSize;
	size_t mBitCapacity;
	Bucket* mBuckets;

	static const size_t DEFAULT_BIT_CAPACITY = 6;

	void mGrow(size_t newBitCapacity);

	void mShrink(size_t newBitCapacity);

	size_t mHash(const K& k) const {
		const size_t BLOCK_SIZE = 32;
		uint8_t data[BLOCK_SIZE]; 
		std::memcpy(data, &k, std::min(sizeof(K), BLOCK_SIZE));

		// TODO: hash data
		return 0;
	}

	constexpr size_t mCapacity() const {
		return 1 << mBitCapacity;
	}

	constexpr float mLoadFactor() const {
		return (float) mSize / (float) mCapacity();
	};

public:
	Dictionary()
		: mSize(0)
		, mBitCapacity(DEFAULT_BIT_CAPACITY)
		, mBuckets(new Bucket[mCapacity()])
	{}

	Dictionary(const Dictionary& other)
		: mSize(other.mSize)
		, mBitCapacity(other.mBitCapacity)
		, mBuckets(new Bucket[mCapacity()])
	{
		for (int i = 0; i < mCapacity(); ++i)
			mBuckets[i] = other.mBuckets[i];
	}

	Dictionary(Dictionary&& other)
		: mSize(other.mSize)
		, mBitCapacity(other.mBitCapacity)
		, mBuckets(other.mBuckets)
	{
		other.mBuckets = nullptr;
	}

	~Dictionary() {
		delete[] mBuckets;
	}
	
	void clear() {
		for (int i = 0; i < mCapacity(); ++i)
			mBuckets[i].clear();
		
		mSize = 0;
	}

	template<typename P, typename Q>
	void set(P&& k, Q&& v) {
		int index = mHash(k) & (mBitCapacity - 1);
		Bucket& b = mBuckets[index];
		
		if(has(k))
			erase(k);

		b.push_back(Entry(std::forward<P>(k), std::forward<Q>(v)));
		// TODO: implement
	}

	const V& get(const K& k) const {
		int index = mHash(k) & (mBitCapacity - 1);
		Bucket& b = mBuckets[index];
		
		for (auto it = b.begin(); it != b.end(); ++it)
			if (it->first == k)
				return it->second;
		
		throw std::out_of_range("No entry for given key");
	}

	// V& operator[](const K& k);    // Zwraca wartość dla klucza

	bool has(const K& k) const {
		int index = mHash(k) & (mBitCapacity - 1);

		for (const Entry e : mBuckets[index])
			if (e.first == k)
				return true;

		return false;
	};

	bool erase(const K& k) {
		int index = mHash(k) & (mBitCapacity - 1);
		Bucket& b = mBuckets[index];

		for (auto it = b.begin(); it != b.end(); ++it)
			if (it->first == k) {
				b.erase(it);
				mSize -= 1;
				return true;
			}

		return false;
	};

	size_t size() const;             // Zwraca liczbę par
	bool empty() const;              // Sprawdza czy słownik jest pusty
	
	void buckets() const;
};