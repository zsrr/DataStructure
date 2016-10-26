//
// Created by 张师睿 on 16/9/11.
//

#ifndef DATASTRUCTURES_ARRAYQUEUE_HPP
#define DATASTRUCTURES_ARRAYQUEUE_HPP

#include "AbsQueue.hpp"
#include "../MyOwnException.h"
#include <algorithm>

using std::copy;

template<class T>
class ArrayQueue : public AbsQueue<T> {
public:
    ArrayQueue(int capacity = 10) {
        if (capacity <= 0) {
            throw IllegalParameterValue();
        }
        arraySize = capacity;
        queueFront = queueBack = elementsSize = 0;
        elements = new T[arraySize];
    }

    virtual bool empty() const override {
        return queueBack == queueFront;
    }

    virtual int size() const override {
        return elementsSize;
    }

    virtual T &front() const override {
        check();
        return elements[(queueFront + 1) % arraySize];
    }

    virtual T &back() const override {
        check();
        return elements[queueBack];
    }

    virtual void push(const T &element) override {
        if ((queueBack + 1) % arraySize == queueFront) {
            create_new_array();
        }
        queueBack = (queueBack + 1) % arraySize;
        elements[queueBack] = element;
        elementsSize++;
    }

    virtual void pop() override {
        check();
        queueFront = (queueFront + 1) % arraySize;
        elements[queueFront].~T();
        elementsSize--;
    }

    ~ArrayQueue() {
        delete[] elements;
    }

private:
    int arraySize;
    int elementsSize;
    int queueFront;
    int queueBack;
    T *elements;

    void create_new_array() {
        T *newArray = new T[arraySize * 2];
        int start = (queueFront + 1) % arraySize;
        //分成没有成环以及成环的情况
        if (start < 2) {
            copy(elements + start, elements + start + arraySize - 1, newArray);
        } else {
            copy(elements + start, elements + arraySize, newArray);
            copy(elements, elements + queueBack + 1, newArray + arraySize - start);
        }

        queueFront = arraySize * 2 - 1;
        queueBack = arraySize - 2;
        arraySize *= 2;
        delete[] elements;
        elements = newArray;
    }

    void check() const throw(QueueEmptyException) {
        if (elementsSize == 0) {
            throw QueueEmptyException();
        }
    }
};


#endif //DATASTRUCTURES_ARRAYQUEUE_HPP
