#include <vector>
#include <iostream>
#include <optional>
#include <stdexcept>

#include "lib.hpp"

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

template <typename T>
class FirstOddVisitor: public Visitor<T> {
  std::optional<T> m_first_odd = std::nullopt;
public:
  void visit(T& element) {
    if (!m_first_odd && element % 2 != 0) {
      m_first_odd = std::optional { element };
    }
  }

  bool isDone() const {
    return m_first_odd == true;
  }

  std::optional<T>& unwrap() {
    return m_first_odd;
  }
};

class ArraySet : public Set<int> {
private:
	int m_universe;
	int m_count;
	std::vector<bool> m_data;

  class Iter : public Iterator<int> {
    ArraySet* m_subject;
    size_t m_index;
  public:
    Iter(ArraySet* subject, int index)
      : m_subject(subject)
      , m_index(index)
    {
      while (!isDone() && m_subject->m_data[m_index] == false) m_index += 1;
    }

    bool isDone() {
      return m_index >= m_subject->m_data.size();
    }

    int operator*() {
      // Error on attempt of dereferencing done iterator
      if (isDone()) { throw std::out_of_range ("dereferencing of done iterator"); }

      return (int) m_index;
    }

    void operator++() {
      do {
        m_index += 1;
      }
      while (!isDone() && m_subject->m_data[m_index] == false);
    }

    bool operator!=(const Iter& it) {
      return it.m_subject != m_subject || it.m_index != m_index;
    }
  };

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
      if (visitor.isDone()) {
        std::cout << "Done!: " << i << std::endl;
        break;
      }
    }
  }

  Iter begin() {
    Iter it(this, 0);
    return it;
  }

  Iter end() {
    Iter it(this, m_data.size());
    return it;
  }

	void __log__() const {
		std::cout << "-----------------------------------" << std::endl;
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

