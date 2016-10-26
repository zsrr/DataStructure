//
// Created by 张师睿 on 16/9/9.
//

#ifndef DATASTRUCTURES_STACK_HPP
#define DATASTRUCTURES_STACK_HPP

template<class T>
class Stack {
public:
    Stack() = default;

    virtual bool isEmpty() const = 0;

    virtual T &top() const = 0;

    virtual void pop() = 0;

    virtual void push(const T &element) = 0;

    virtual int size() = 0;

    virtual ~Stack() = default;
};


#endif //DATASTRUCTURES_STACK_HPP
