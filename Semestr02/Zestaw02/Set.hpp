#include <vector>
#include <iostream>

class Container {
public:
	virtual size_t size() const = 0;
	virtual bool empty() const { return size() == 0; };
	virtual bool full() const = 0;
	virtual void clear() = 0;
};

template <typename T>
class Set : public Container {

};

template <typename T>
class Visitor {
public:
  virtual void visit(T& element) = 0;
  virtual bool isDone() const { return false; }
};

template <typename T>
class printVisitor: public Visitor<T> {
public:
  void visit(T& element) {
    std::cout << element << std::endl;
  }
};

template <typename T>
class sumVisitor: public Visitor<T> {
  T sum;
public:
  void visit(T& element) {
    sum = sum + element;
  }

  T& unwrap() {
    return sum;
  }
};

class ArraySet : public Set<int> {
private:
	int m_universe;
	int m_count;
	std::vector<bool> m_data;

public:
	ArraySet (int universe)
		: m_universe(universe)
		, m_count(0)
	{
		for (int i = 0; i < m_universe; ++i) m_data.push_back(false);
	}

	void insert(int el) {
		if (!m_data[el]) {
			m_count += 1;
			m_data[el] = true;
		}
	}

	void remove(int el) {
		if (m_data[el]) {
			m_count -= 1;
			m_data[el] = false;
		}
	}

	bool has (int el) const {
		return m_data[el];
	}

	void clear () {
		for (int i = 0; i < m_universe; ++i) m_data[i] = false;
	}

	size_t size() const {
		return m_count;
	}

	bool full() const {
		return m_count == m_universe;
	}

	bool empty() const {
		return m_count == 0;
	}

  void accept(Visitor<int>& visitor) const {
    for (int i = 0; i < (int)m_data.size(); ++i) {
      if (m_data[i]) visitor.visit(i);
      if (visitor.isDone()) break;
    }
  }

	void __log__() const {
		std::cout << "----------------------------------------" << std::endl;
		std::cout << "\tsize:" << size();
		std::cout << std::endl << "\t";
		for (const auto& it : m_data) {
			std::cout << it << ", ";
		}
		std::cout << std::endl;
	}

	friend ArraySet operator+(const ArraySet& a, const ArraySet& b);
	friend ArraySet operator-(const ArraySet& a, const ArraySet& b);
	friend ArraySet operator*(const ArraySet& a, const ArraySet& b);
	friend bool operator==(const ArraySet& a, const ArraySet& b);
	friend bool operator<=(const ArraySet& a, const ArraySet& b);

};

ArraySet operator+(const ArraySet& a, const ArraySet& b) {
	ArraySet c = ArraySet(a.m_universe);
	for(int i = 0; i < c.m_universe; ++i) {
		if (a.has(i) || b.has(i)) c.insert(i);
	}

	return c;
}

ArraySet operator-(const ArraySet& a, const ArraySet& b) {
	ArraySet c = ArraySet(a.m_universe);
	for(int i = 0; i < c.m_universe; ++i) {
		if (a.has(i) && !b.has(i)) c.insert(i);
	}

	return c;
}

ArraySet operator*(const ArraySet& a, const ArraySet& b) {
	ArraySet c = ArraySet(a.m_universe);
	for(int i = 0; i < c.m_universe; ++i) {
		if (a.has(i) && b.has(i)) c.insert(i);
	}

	return c;
}

bool operator==(const ArraySet& a, const ArraySet& b) {
	for(int i = 0; i < a.m_universe; ++i) {
		if (a.has(i) != b.has(i)) return false;
	}

	return true;
}

bool operator<=(const ArraySet& a, const ArraySet& b) {
	for(int i = 0; i < a.m_universe; ++i) {
		if (a.has(i) && !b.has(i)) return false;
	}

	return true;
}

