//
// Created by 张师睿 on 16/9/9.
//

#ifndef DATASTRUCTURES_ARRAYSTACK_HPP
#define DATASTRUCTURES_ARRAYSTACK_HPP

#include "Stack.hpp"
#include <algorithm>
#include "../MyOwnException.h"

using std::copy;

//只用数组实现
template<class T>
class ArrayStack : public Stack<T> {
public:
    ArrayStack(int capability = 10) {
        if (capability <= 0) {
            throw IllegalParameterValue();
        }
        arraySize = capability;
        elements = new T[arraySize];
    }

    ArrayStack(const ArrayStack<T> &arrayStack) {
        if (this != &arrayStack) {
            cur = arrayStack.cur;
            arraySize = arrayStack.arraySize;

            if (arraySize != 0) {
                elements = new T[arraySize];
            }
            for (int i = 0; i < cur + 1; i++) {
                elements[i] = arrayStack.elements[i];
            }
        }
    }

    virtual bool isEmpty() const override {
        return cur == -1;
    }

    virtual T &top() const override {
        if (isEmpty()) {
            throw StackEmptyException();
        }
        return elements[cur];
    }

    virtual void pop() override {
        if (isEmpty()) {
            throw StackEmptyException();
        }
        //直接调用析构函数
        elements[cur--].~T();
    }

    virtual void push(const T &element) override {
        if (!hasEnoughRoom()) {
            reallocate();
        }
        elements[++cur] = element;
    }

    virtual int size() override {
        return cur + 1;
    }

    ~ArrayStack() { delete[] elements; }

private:
    int cur = -1;
    T *elements = nullptr;
    int arraySize = 0;

    bool hasEnoughRoom() {
        return arraySize > (cur + 1);
    }

    void reallocate() {
        int newSize = arraySize * 2;
        T *newArray = new T[newSize];
        copy(elements, elements + arraySize, newArray);
        delete[] elements;
        elements = newArray;
    }
};


#endif //DATASTRUCTURES_ARRAYSTACK_HPP
