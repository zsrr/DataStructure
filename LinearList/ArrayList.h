#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H
#define CANNOT_BE_FOUND -1

#include "LinearList.h"
#include "../MyOwnException.h"
#include "../utils.hpp"

using std::swap;

template<class T>
class ArrayList : public LinearList<T> {
public:

    ArrayList();

    ArrayList(int theSize);

    ArrayList(int theSize, T element);

    ArrayList(const ArrayList<T> &theArray);

    ~ArrayList() { delete[] elements; }

    int getSize() const override { return size; }

    T &get(int index) const override;

    int indexOf(const T &element) const override;

    void erase(int index) override;

    void insert(int index, const T &element) override;

    void sort(int(*func)(T, T) = nullptr) override;

    void push_back(const T &element) override;

protected:
    T *elements = nullptr;
    int size = 0;
    int maxSize = 0;

    void checkParameter(int theSize) const throw(IllegalParameterValue);

    void check(int index) const throw(IndexOutOfBounds);

    bool hasEnoughRoom() const;
};

#endif // !ARRAY_LIST_H

template<class T>
int partition(T elements[], int start, int end) {
    T x = elements[end];
    int i = start - 1;
    for (int j = start; j <= end - 1; j++) {
        if (elements[j] <= x) {
            i++;
            swap(elements[i], elements[j]);
        }
    }
    swap(elements[i + 1], elements[end]);
    return i + 1;
}

template<class T>
int partition(T elements[], int start, int end, int(*func)(T, T)) {
    T x = elements[end];
    int i = start - 1;
    for (int j = start; j <= end - 1; j++) {
        if (func(elements[j], x) <= 0) {
            i++;
            swap(elements[i], elements[j]);
        }
    }
    swap(elements[i + 1], elements[end]);
    return i + 1;
}

template<class T>
void qsort(T elements[], int start, int end) {
    if (start < end) {
        int i = partition(elements, start, end);
        qsort(elements, start, i - 1);
        qsort(elements, i + 1, end);
    }
}

template<class T>
void qsort(T elements[], int start, int end, int(*func)(T, T)) {
    if (start < end) {
        int i = partition(elements, start, end, func);
        qsort(elements, start, i - 1, func);
        qsort(elements, i + 1, end, func);
    }
}

template<class T>
inline bool ArrayList<T>::hasEnoughRoom() const {
    return size < maxSize;
}

template<class T>
inline void ArrayList<T>::checkParameter(int theSize) const throw(IllegalParameterValue) {
    if (theSize < 0) {
        throw IllegalParameterValue();
    }
}

template<class T>
inline void ArrayList<T>::check(int index) const throw(IndexOutOfBounds) {
    if (index < 0 || index >= size) {
        throw IndexOutOfBounds();
    }
}

template<class T>
inline ArrayList<T>::ArrayList() {
    size = 0;
    maxSize = 10;
    elements = new T[maxSize];
}

template<class T>
inline ArrayList<T>::ArrayList(int theSize) {
    checkParameter(theSize);
    size = theSize;
    maxSize = size * 2;
    elements = new T[maxSize];
}

template<class T>
inline ArrayList<T>::ArrayList(int theSize, T element) {
    checkParameter(theSize);
    elements = new T[2 * theSize];
    for (int i = 0; i < theSize; i++) {
        elements[i] = element;
    }
    size = theSize;
    maxSize = size * 2;
}

template<class T>
inline ArrayList<T>::ArrayList(const ArrayList<T> &theArray) {
    if (this != &theArray) {
        size = theArray.size;
        maxSize = theArray.maxSize;
        elements = new T[maxSize];
        for (int i = 0; i < size; i++) {
            elements[i] = theArray.elements[i];
        }
    }
}

template<class T>
inline T &ArrayList<T>::get(int index) const {
    check(index);
    return elements[index];
}

template<class T>
inline int ArrayList<T>::indexOf(const T &element) const {
    for (int i = 0; i < size; i++) {
        if (elements[i] == element) {
            return i;
        }
    }
    return CANNOT_BE_FOUND;
}

template<class T>
inline void ArrayList<T>::erase(int index) {
    check(index);
    copy(elements + index + 1, elements + size, elements + index);
    size--;
}

template<class T>
inline void ArrayList<T>::insert(int index, const T &element) {
    check(index);
    if (!hasEnoughRoom()) {
        changeArrayLength(elements, maxSize, 2 * maxSize);
    }
    copy(elements + index, elements + size, elements + index + 1);
    elements[index] = element;
    size++;
}

template<class T>
inline void ArrayList<T>::sort(int(*func)(T, T)) {
    if (!func) {
        qsort(elements, 0, size - 1);
    } else {
        qsort(elements, 0, size - 1, func);
    }
}

template<class T>
inline void ArrayList<T>::push_back(const T &element) {
    if (!hasEnoughRoom()) {
        changeArrayLength(elements, maxSize, 2 * maxSize);
        maxSize *= 2;
    }
    elements[size] = element;
    size++;
}
