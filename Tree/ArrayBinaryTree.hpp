//
// Created by 张师睿 on 2016/10/26.
// 不应该有析构函数，因为它持有比他生命周期长的指针

#ifndef DATASTRUCTURES_ARRAYBINARYTREE_HPP
#define DATASTRUCTURES_ARRAYBINARYTREE_HPP

#include "AbsBinaryTree.hpp"
#include "../Queue/ListQueue.hpp"

template <class T>
class ArrayBinaryTree : public AbsBinaryTree<T> {
public:
    typedef void (*VISIT_FUNC)(T *);

    ArrayBinaryTree(const T *elements, int size) {
        this->elements = const_cast<T *> (elements);
        this->size = size;
    }

    virtual int height() const override {
        return static_height(1, size, elements);
    }

    virtual void preOrder(VISIT_FUNC visit) override {
        static_pre(1, size, visit, elements);
    }

    virtual void inOrder(VISIT_FUNC visit) override {
        static_in(1, size, visit, elements);
    }

    virtual void postOrder(VISIT_FUNC visit) override {
        static_post(1, size, visit, elements);
    }

    virtual void levelOrder(VISIT_FUNC visit) override {
        ListQueue<int> lq;
        int index = 1;

        while (index <= size) {
            visit(elements + index);

            if (index * 2 <= size) {
                lq.push(index * 2);
            }
            if (index * 2 + 1 <= size) {
                lq.push(index * 2 + 1);
            }

            try {
                index = lq.front();
            } catch (QueueEmptyException e) {
                return;
            }
            lq.pop();
        }
    }



private:
    int size;
    T *elements;

    static void static_pre(int index, int max_size, VISIT_FUNC visit, const T *elements) {
        if (index <= max_size) {
            visit(const_cast<T *> (elements + index));
            static_pre(2 * index, max_size, visit, elements);
            static_pre(2 * index + 1, max_size, visit, elements);
        }
    }

    static void static_in(int index, int max_size, VISIT_FUNC visit, const T *elements) {
        if (index <= max_size) {
            static_in(2 * index, max_size, visit, elements);
            visit(const_cast<T *> (elements + index));
            static_in(2 * index + 1, max_size, visit, elements);
        }
    }

    static void static_post(int index, int max_size, VISIT_FUNC visit, const T *elements) {
        if (index <= max_size) {
            static_post(2 * index, max_size, visit, elements);
            static_post(2 * index + 1, max_size, visit, elements);
            visit(const_cast<T *> (elements + index));
        }
    }

    static int static_height(int index, int max_size, const T *elements) {
        if (index >= max_size)
            return 0;

        int hl = static_height(2 * index, max_size, elements);
        int hr = static_height(2 * index + 1, max_size, elements);

        return hl > hr ? ++hl : ++hr;
    }
};

#endif //DATASTRUCTURES_ARRAYBINARYTREE_HPP
