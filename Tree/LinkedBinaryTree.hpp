//
// Created by 张师睿 on 16/9/16.
//

#ifndef DATASTRUCTURES_LINKEDBINARYTREE_HPP
#define DATASTRUCTURES_LINKEDBINARYTREE_HPP

#include "AbsBinaryTree.hpp"
#include "../Queue/ListQueue.hpp"
#include "../MyOwnException.h"

template<class T>
struct BinaryTreeNode {
    T element;
    BinaryTreeNode<T> *leftChild;
    BinaryTreeNode<T> *rightChild;

    BinaryTreeNode(const T &theElement) : element(theElement) {
        leftChild = rightChild = nullptr;
    }

    BinaryTreeNode(const T &theElement, BinaryTreeNode<T> *const left,
                   BinaryTreeNode<T> *const right) : element(theElement), leftChild(left), rightChild(right) {}

    BinaryTreeNode() : element(), leftChild(), rightChild() {}
};

template<class E>
class LinkedBinaryTree : public AbsBinaryTree<BinaryTreeNode<E>> {
public:

    typedef void (*VISIT_FUNC)(BinaryTreeNode<E> *);

    LinkedBinaryTree(BinaryTreeNode<E> *const theRoot) {
        //指向了同一块内存！
        root = theRoot;
    }

    LinkedBinaryTree() : root() {}

    void makeTree(E element, const LinkedBinaryTree<E> &leftChild,
                  const LinkedBinaryTree<E> &rightChild) {
        if (root != nullptr) {
            delete root;
        }
        root = new BinaryTreeNode<E>(element, &leftChild, &rightChild);
    }

    virtual int height() const override {
        return static_height(root);
    }

    virtual void preOrder(VISIT_FUNC visit) override {
        static_pre(root, visit);
    }

    virtual void inOrder(VISIT_FUNC visit) override {
        static_in(root, visit);
    }

    virtual void postOrder(VISIT_FUNC visit) override {
        static_post(root, visit);
    }

    virtual void levelOrder(VISIT_FUNC visit) override {
        ListQueue<BinaryTreeNode<E> *> queue;
        BinaryTreeNode<E> *temp = root;

        while (temp != nullptr) {
            visit(temp);

            if (temp->leftChild != nullptr)
                queue.push(temp->leftChild);
            if (temp->rightChild != nullptr)
                queue.push(temp->rightChild);

            try {
                temp = queue.front();
            } catch (QueueEmptyException e) {
                return;
            }
            queue.pop();
        }
    }

    ~LinkedBinaryTree() {
        postOrder(dispose);
    }

private:
    BinaryTreeNode<E> *root;

    static void static_pre(BinaryTreeNode<E> *root, VISIT_FUNC visit) {
        if (root != nullptr) {
            visit(root);
            static_pre(root->leftChild, visit);
            static_pre(root->rightChild, visit);
        }
    }

    static void static_in(BinaryTreeNode<E> *root, VISIT_FUNC visit) {
        if (root != nullptr) {
            static_in(root->leftChild, visit);
            visit(root);
            static_in(root->rightChild, visit);
        }
    }

    static void static_post(BinaryTreeNode<E> *root, VISIT_FUNC visit) {
        if (root != nullptr) {
            static_post(root->leftChild, visit);
            static_post(root->rightChild, visit);
            visit(root);
        }
    }

    static void dispose(BinaryTreeNode<E> *root) {
        delete root;
    }

    static int static_height(BinaryTreeNode<E> *root) {
        if (root == nullptr)
            return 0;

        int hl = static_height(root->leftChild);
        int hr = static_height(root->rightChild);

        return hl > hr ? ++hl : ++hr;
    }
};

#endif //DATASTRUCTURES_LINKEDBINARYTREE_HPP
