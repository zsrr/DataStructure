//
// Created by 张师睿 on 2016/11/14.
//

#ifndef DATASTRUCTURES_LINKEDLIST_HPP
#define DATASTRUCTURES_LINKEDLIST_HPP

#include "LinearList.h"
#include "../MyOwnException.h"

template <class T>
struct ChainNode {
    T element;
    ChainNode<T> *next;
    ChainNode<T> *pre;

    ChainNode<T>(const T &element, ChainNode<T> *next = nullptr,
                 ChainNode *pre = nullptr) : element(element), next(next), pre(pre) {}
};

template <class T>
class LinkedList : public LinearList<T> {
public:
    LinkedList() : size(0), front(), back() {}

    ~LinkedList() {
        while (front != nullptr) {
            ChainNode<T> *temp = front->next;
            delete front;
            front = temp;
        }
    }

    virtual int getSize() const override {
        return size;
    }

    virtual const T &get(int index) const override {
        check_index(index);
        if (index < size / 2)
            return get_from_front(index);
        return get_from_back(index);
    }

    virtual int indexOf(const T &element) const override {
        ChainNode<T> *temp = front;
        int index = 0;
        while (temp != nullptr) {
            if (temp->element == element)
                return index;
            index++;
            temp = temp->next;
        }
        return CANNOT_BE_FOUND;
    }

    virtual void erase(int index) override {
        check_index(index);
        if (size == 1) {
            delete front;
            back = front = nullptr;
            size--;
            return;
        }
        if (index < size / 2)
            erase_from_front(index);
        else
            erase_from_back(index);
    }

    virtual void insert(int index, const T &element) override {
        if (index < 0 || index > size)
            throw IllegalParameterValue();
        if (size == 0) {
            front = new ChainNode<T>(element, nullptr, nullptr);
            back = front;
            size++;
            return;
        }
        if (index < size / 2 || index == 0)
            insert_from_front(index, element);
        else
            insert_from_back(index, element);
    }

    virtual void push_back(const T &element) override {
        insert(size, element);
    }

    void push_front(const T &element) {
        insert(0, element);
    }

    virtual bool empty() const override {
        return size == 0;
    }

private:
    ChainNode<T> *front;
    ChainNode<T> *back;
    int size;

    void check_index(int index) const {
        if (index < 0 || index >= size) {
            throw IllegalParameterValue();
        }
    }

    const T &get_from_front(int index) const {
        ChainNode<T> *temp = front;
        for (int i = 0; i < index; i++)
            temp = temp->next;
        return temp->element;
    }

    const T &get_from_back(int index) const {
        ChainNode<T> *temp = back;
        for (int i = 0; i < size - index - 1; i++)
            temp = temp->pre;
        return temp->element;
    }

    void erase_from_front(int index) {
        ChainNode<T> *temp = front;
        if (index == 0) {
            front = front->next;
            if (front != nullptr)
                front->pre = nullptr;
            delete temp;
            size--;
            return;
        }
        for (int i = 0; i < index; i++)
            temp = temp->next;
        ChainNode<T> *temp_pre = temp->pre;
        ChainNode<T> *temp_next = temp->next;
        delete temp;
        temp_pre->next = temp_next;
        temp_next->pre = temp_pre;
        size--;
    }

    void erase_from_back(int index) {
        ChainNode<T> *temp = back;
        if (index == size - 1) {
            back = back->pre;
            if (back != nullptr)
                back->next = nullptr;
            delete temp;
            size--;
            return;
        }
        for (int i = 0; i < size - index - 1; i++)
            temp = temp->pre;
        ChainNode<T> *temp_pre = temp->pre;
        ChainNode<T> *temp_next = temp->next;
        delete temp;
        temp_pre->next = temp_next;
        temp_next->pre = temp_pre;
        size--;
    }

    void insert_from_front(int index, const T &element) {
        if (index == 0) {
            front->pre = new ChainNode<T>(element, front, nullptr);
            front = front->pre;
            size++;
            return;
        }
        ChainNode<T> *temp = front;
        for (int i = 0; i < index; i++)
            temp = temp->next;
        temp->pre = new ChainNode<T>(element, temp->pre, temp);
        size++;
    }

    void insert_from_back(int index, const T &element) {
        if (index == size) {
            back->next = new ChainNode<T>(element, nullptr, back);
            back = back->next;
            size++;
            return;
        }
        ChainNode<T> *temp = back;
        for (int i = 0; i < size - index - 1; i++)
            temp = temp->pre;
        temp->pre = new ChainNode<T>(element, temp->pre, temp);
        size++;
    }
};

#endif //DATASTRUCTURES_LINKEDLIST_HPP
