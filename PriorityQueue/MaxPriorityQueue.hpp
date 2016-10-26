//
// Created by 张师睿 on 16/9/15.
//

#ifndef DATASTRUCTURES_MAXHEAP_HPP
#define DATASTRUCTURES_MAXHEAP_HPP


#include <deque>
#include "PriorityQueue.hpp"
#include "../MyOwnException.h"

using std::copy;

template<class T>
class MaxPriorityQueue : public PriorityQueue<T> {
public:
    MaxPriorityQueue(int capacity = 10) {
        if (capacity <= 0) {
            throw IllegalParameterValue();
        }
        arrayLength = capacity;
        heap = new T[arrayLength];
        heapSize = 0;
    }

    virtual bool empty() const override {
        return heapSize == 0;
    }

    virtual int size() const override {
        return heapSize;
    }

    virtual const T &top() const override {
        return heap[1];
    }

    virtual void pop() override {
        if (heapSize == 0) {
            throw HeapEmptyException();
        }
        heap[1].~T();
        T lastElement = heap[heapSize--];
        int current = 1, child = 2;
        while (child <= heapSize) {
            if (child < heapSize && heap[child] < heap[child + 1])
                child++;
            if (lastElement >= heap[child])
                break;
            heap[current] = heap[child];
            current = child;
            child *= 2;
        }
        heap[current] = lastElement;
    }

    virtual void push(const T &element) override {
        //第一个0不能使用,涉及到乘除操作
        if (heapSize == arrayLength - 1) {
            //不可以和线性表执行相同的操作
            changeLength();
        }

        int currentNode = ++heapSize;
        while (currentNode != 1 && heap[currentNode / 2] < element) {
            heap[currentNode] = heap[currentNode / 2];
            currentNode /= 2;
        }
        heap[currentNode] = element;
    }

    void initialize(T *theHeap, int arrayLength, int heapSize) {
        delete[] heap;
        this->arrayLength = arrayLength;
        this->heapSize = heapSize;
        heap = new T[arrayLength];
        copy(theHeap + 1, theHeap + heapSize + 1, heap + 1);

        for (int i = heapSize / 2; i >= 1; i--) {
            T root = heap[i];

            int child = 2 * i;
            while (child <= heapSize) {
                if (child < heapSize && heap[child] < heap[child + 1])
                    child++;
                if (root >= heap[child])
                    break;
                heap[child / 2] = heap[child];
                child *= 2;
            }
            heap[child / 2] = root;
        }
    }

private:
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

#endif //DATASTRUCTURES_MAXHEAP_HPP
