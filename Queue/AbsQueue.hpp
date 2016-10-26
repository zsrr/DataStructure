//
// Created by 张师睿 on 16/9/11.
//

#ifndef DATASTRUCTURES_ABSQUEUE_HPP
#define DATASTRUCTURES_ABSQUEUE_HPP

template<class T>
class AbsQueue {
public:
    virtual ~AbsQueue() {}

    virtual bool empty() const = 0;

    virtual int size() const = 0;

    virtual T &front() const = 0;

    virtual T &back() const = 0;

    //在尾部插入
    virtual void push(const T &element) = 0;

    //在头部删除
    virtual void pop() = 0;
};


#endif //DATASTRUCTURES_ABSQUEUE_HPP
