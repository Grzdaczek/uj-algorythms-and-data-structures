class Container {
public:
	virtual size_t size() const = 0;
	virtual bool empty() const { return size() == 0; };
	virtual bool full() const = 0;
	virtual void clear() = 0;
};

template <typename T>
class Set : public Container {};

template <typename T>
class Visitor {
public:
  virtual void visit(T& element) = 0;
  virtual bool isDone() const {
    return false;
  }
};

template <typename T>
class Iterator {
public:
  virtual bool isDone() { return false; }
  virtual T operator*() = 0;
  virtual void operator++() = 0;
};

