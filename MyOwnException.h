#ifndef MY_OWN_EXCEPTION_H
#define MY_OWN_EXCEPTION_H

#include <stdexcept>

using std::runtime_error;

class IndexOutOfBounds : public runtime_error {
public:
    IndexOutOfBounds() : runtime_error("越界访问") {}
};

class IllegalParameterValue : public runtime_error {
public:
    IllegalParameterValue() : runtime_error("非法参数") {}
};

class StackEmptyException : public runtime_error {
public:
    StackEmptyException() : runtime_error("栈是空的!") {}
};

class QueueEmptyException : public runtime_error {
public:
    QueueEmptyException() : runtime_error("队列是空的!") {}
};

class IllegalDivisorException : public runtime_error {
public:
    IllegalDivisorException() : runtime_error("非法除数!") {}
};

class HashTableFullException : public runtime_error {
public:
    HashTableFullException() : runtime_error("表已满!") {}
};

class HashTableEmptyException : public runtime_error {
public:
    HashTableEmptyException() : runtime_error("表是空的!") {}
};

class HeapEmptyException : public runtime_error {
public:
    HeapEmptyException() : runtime_error("堆是空的") {}
};

class DictionaryEmptyException : public runtime_error {
public:
    DictionaryEmptyException() : runtime_error("字典是空的") {}
};

class UnsupportedOperation : public runtime_error {
public:
    UnsupportedOperation() : runtime_error("不支持此操作"){}
};

class ListEmptyException : public runtime_error {
public:
    ListEmptyException() : runtime_error("表是空的") {}
};

#endif // !MY_OWN_EXCEPTION_H
