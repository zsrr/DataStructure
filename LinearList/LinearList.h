#ifndef LINEAR_LIST_H
#define LINEAR_LIST_H

template<class T>
class LinearList {
public:
	virtual ~LinearList() = default;
	LinearList() = default;
	virtual int getSize() const = 0;
	virtual T& get(int index) const = 0;
	virtual int indexOf(const T& element) const = 0;
	virtual void erase(int index) = 0;
	virtual void insert(int index, const T& element) = 0;
	virtual void sort(int(*func)(T, T) = nullptr) = 0;
	virtual void push_back(const T& element) = 0;
};

#endif // !LINEAR_LIST_H
