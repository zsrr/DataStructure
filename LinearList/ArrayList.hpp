//
// Created by 张师睿 on 2016/11/14.
//

#ifndef DATASTRUCTURES_ARRAYLIST_HPP
#define DATASTRUCTURES_ARRAYLIST_HPP

#include "LinearList.h"
#include "../MyOwnException.h"
#include "../utils.hpp"

using namespace util;

template <class T>
class ArrayList : public LinearList<T> {
public:
    ArrayList(int capacity = 10) : maxSize(capacity), size(0) {
        if (capacity <= 0)
            throw IllegalParameterValue();
        elements = new T[capacity];
    }

    virtual int getSize() const override {
        return size;
    }

    virtual const T &get(int index) const override {
        check(index);
        return elements[index];
    }

    virtual int indexOf(const T &element) const override {
        for (int i = 0; i < size; i++)
            if (elements[i] == element)
                return i;
        return CANNOT_BE_FOUND;
    }

    virtual void erase(int index) override {
        check(index);
        elements[index].~T();
        copy(elements + index + 1, elements + size, elements + index);
        size--;
    }

    virtual void insert(int index, const T &element) override {
        if (index < 0 || index > size)
            throw IllegalParameterValue();
        if (size == maxSize) {
            changeArrayLength(elements, maxSize, maxSize * 2);
            maxSize *= 2;
        }
        copy(elements + index, elements + size, elements + index + 1);
        elements[index] = element;
        size++;
    }

    virtual void push_back(const T &element) override {
        insert(size, element);
    }

    ~ArrayList() {
        delete[](elements);
    }

    virtual bool empty() const override {
        return size == 0;
    }

protected:
    int size;
    int maxSize;
    T *elements;

    void check(int index) const {
        if (index < 0 || index >= size) {
            throw IllegalParameterValue();
        }
    }
};

#endif //DATASTRUCTURES_ARRAYLIST_HPP
