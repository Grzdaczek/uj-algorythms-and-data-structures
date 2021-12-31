#include <utility>
#include <vector>

// template<typename K, typename V>
// class Dictionary;

// template<typename K, typename V>
// class EntryProxy {
// public:
//     using Entry = std::pair<K, V>;

// private:
//     Dictionary* mDict;
// };

template<typename K, typename V>
class Dictionary {
public:
    using Entry = std::pair<K, V>;
    using Bucket = std::vector<Entry>;

private:
    Bucket* mBuckets;
    size_t mSize;
    size_t mBitCapacity;
    size_t mRawCapacity;

    void mGrow(size_t newCapacity);
    void mShrink(size_t newCapacity);
    size_t hash(char[sizeof(V)]);

public:
    Dictionary();
    Dictionary(const Dictionary& other);
    Dictionary(Dictionary&& other);
    
    void clear();                    // Czyści słownik
    void set(const Entry& p);        // Dodaje parę klucz-wartość do słownika
    void set(Entry&& p);             // Dodaje parę klucz-wartość do słownika
    V& get(const K& k);              // Zwraca wartość dla klucza
    V& operator[](const K& k);       // Zwraca wartość dla klucza
    bool has(const K& k);            // Sprawdza czy słownik zawiera klucz
    bool erase(const K& k);          // Usuwa parę od danym kluczu
    size_t size();                   // Zwraca liczbę par
    bool empty();                    // Sprawdza czy słownik jest pusty
    
    void buckets();
};