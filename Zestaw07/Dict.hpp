#include <utility>
#include <vector>
#include <algorithm>
#include <cstring>
#include <climits>
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

	void mResize(size_t newBitCapacity) {
		auto dict = Dictionary(newBitCapacity);

		// std::cerr << "resized to " << newBitCapacity << std::endl;
		// std::cerr << "	bitCapacity: " << mBitCapacity << std::endl;
		// std::cerr << "	size: " << mSize << std::endl;
		// std::cerr << "	capacity: " << (1 << mBitCapacity) << std::endl;

		for (size_t i = 0; i < mCapacity(); ++i)
			for (Entry& b : mBuckets[i])
				dict.set(std::move(b.first), std::move(b.second));

		*this = std::move(dict);
	}

	size_t mHash(const K& k) const;

	constexpr const Bucket& mBucketByKey(const K& k) const {
		return mBuckets[mHash(k) & (mCapacity() - 1)];
	}

	constexpr Bucket& mBucketByKey(const K& k) {
		return mBuckets[mHash(k) & (mCapacity() - 1)];
	}

	constexpr size_t mCapacity() const {
		return (1 << mBitCapacity);
	}

	constexpr float mLoadFactor() const {
		return ((float) mSize) / mCapacity();
	}

public:
	Dictionary(size_t bitCapacity = 8)
		: mSize(0)
		, mBitCapacity(bitCapacity)
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

	Dictionary& operator=(const Dictionary& other) {
		delete[] mBuckets;

		mSize = other.mSize;
		mBitCapacity = other.mBitCapacity;
		mBuckets = new Bucket[mCapacity()];

		for (int i = 0; i < mCapacity(); ++i)
			mBuckets[i] = other.mBuckets[i];
		
		return *this;
	}

	Dictionary& operator=(Dictionary && other) {
		delete[] mBuckets;

		mSize = other.mSize;
		mBitCapacity = other.mBitCapacity;
		mBuckets = other.mBuckets;

		other.mBuckets = nullptr;
		return *this;
	}

	void clear() {
		for (int i = 0; i < mCapacity(); ++i)
			mBuckets[i].clear();
		
		mSize = 0;
	}

	template<typename P, typename Q>
	void set(P&& k, Q&& v) {
		if (mLoadFactor() > 0.75)
			mResize(mBitCapacity + 1);

		for (Entry& e : mBucketByKey(k))
			if (e.first == k) {
				e.second = std::forward<Q>(v);
				return;
			}

		mBucketByKey(k).push_back(
			Entry(std::forward<P>(k), std::forward<Q>(v))
		);
	
		mSize += 1;
	}

	const V& get(const K& k) const {
		for (const Entry& e : mBucketByKey(k))
			if (e.first == k)
				return e.second;
		
		throw std::out_of_range("No entry for given key");
	}

	// V& operator[](const K& k);    // Zwraca wartość dla klucza

	bool has(const K& k) const {
		for (const Entry& e : mBucketByKey(k))
			if (e.first == k)
				return true;

		return false;
	};

	bool erase(const K& k) {
		// if (mLoadFactor() < 0.25)
		// 	mResize(mBitCapacity >> 1);
		
		Bucket& b = mBucketByKey(k);

		for (auto it = b.begin(); it != b.end(); ++it)
			if (it->first == k) {
				b.erase(it);
				mSize -= 1;
				return true;
			}

		return false;
	};

	size_t size() const {
		return mSize;
	};

	bool empty() const {
		return size() == 0;
	}
	
	void buckets() const {
		size_t max = 0;
		size_t min = SIZE_MAX;

		for (size_t i = 0; i < mCapacity(); ++i) {
			if (mBuckets[i].size() > max) max = mBuckets[i].size();
			if (mBuckets[i].size() < min) min = mBuckets[i].size();
		}

		std::cerr << "# "
			<< mSize << " "
			<< mCapacity() << " "
			<< min << " "
			<< max << std::endl;
	};
};

template<typename K, typename V>
size_t Dictionary<K, V>::mHash(const K& k) const {
	// const size_t BLOCK_SIZE = 32;
	// uint8_t data[BLOCK_SIZE]; 
	// std::memcpy(data, &k, std::min(sizeof(K), BLOCK_SIZE));
	// TODO: hash data
	return 0;
}

// faild attempt of member template partial specialization

// template<typename V>
// size_t Dictionary<std::string, V>::mHash(const std::string& k) const {

// }

template<>
size_t Dictionary<std::string, std::string>::mHash(const std::string& k) const {
	size_t h = 0;
	
	for(const char& c : k) {
		h = (h << 5) | (h >> (sizeof(h) * 8 - 5));
		h = h ^ c;
	}

	return h;
}
