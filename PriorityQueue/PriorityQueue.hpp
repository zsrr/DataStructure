//
// Created by 张师睿 on 16/9/15.
//

#ifndef DATASTRUCTURES_MAXPRIORITYQUEUE_HPP
#define DATASTRUCTURES_MAXPRIORITYQUEUE_HPP

#include <algorithm>

using std::copy;

template<class T>
class PriorityQueue {
public:
    virtual ~PriorityQueue() {
        delete[](heap);
    }

    virtual bool empty() const = 0;

    virtual int size() const = 0;

    virtual const T &top() const = 0;

    virtual void pop() = 0;

    virtual void push(const T &element) = 0;

protected:
    T *heap;
    int arrayLength;
    int heapSize;

    void changeLength() {
        T *newArray = new T[arrayLength * 2];
        copy(heap + 1, heap + arrayLength, newArray + 1);
        arrayLength *= 2;
        delete[] heap;
        heap = newArray;
    }
};

#endif //DATASTRUCTURES_MAXPRIORITYQUEUE_HPP
