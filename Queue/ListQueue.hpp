//
// Created by 张师睿 on 16/9/12.
//

#ifndef DATASTRUCTURES_LISTQUEUE_HPP
#define DATASTRUCTURES_LISTQUEUE_HPP

#include "AbsQueue.hpp"
#include "../LinearList/LinkedList.h"
#include "../MyOwnException.h"

template <class T>
class ListQueue : public AbsQueue<T> {
public:
    ListQueue() = default;

    virtual bool empty() const override {
        return queueSize == 0;
    }

    virtual int size() const override {
        return queueSize;
    }

    virtual T &front() const override {
        if (queueSize == 0) {
            throw QueueEmptyException();
        }
        return firstNode->element;
    }

    virtual T &back() const override {
        if (queueSize == 0) {
            throw QueueEmptyException();
        }
        return backNode->element;
    }

    virtual void push(const T &element) override {
        ChainNode<T>* newNode = new ChainNode<T>(element);
        if(queueSize == 0) {
            firstNode = backNode = newNode;
        } else {
            backNode->next = newNode;
            backNode = newNode;
        }
        queueSize++;
    }

    virtual void pop() override {
        if (queueSize == 0) {
            throw QueueEmptyException();
        }
        ChainNode<T>* next = firstNode->next;
        delete firstNode;
        firstNode = next;
        queueSize--;
    }

    ~ListQueue() {
        while (firstNode != nullptr) {
            ChainNode<T>* next = firstNode->next;
            delete firstNode;
            firstNode = next;
        }
    }

private:
    ChainNode<T>* firstNode = nullptr;
    ChainNode<T>* backNode = nullptr;
    int queueSize = 0;
};


#endif //DATASTRUCTURES_LISTQUEUE_HPP
