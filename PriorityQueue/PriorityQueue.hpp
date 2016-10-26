//
// Created by 张师睿 on 16/9/15.
//

#ifndef DATASTRUCTURES_MAXPRIORITYQUEUE_HPP
#define DATASTRUCTURES_MAXPRIORITYQUEUE_HPP

template<class T>
class PriorityQueue {
public:
    virtual ~PriorityQueue() {}

    virtual bool empty() const = 0;

    virtual int size() const = 0;

    virtual const T &top() const = 0;

    virtual void pop() = 0;

    virtual void push(const T &element) = 0;
};

#endif //DATASTRUCTURES_MAXPRIORITYQUEUE_HPP
