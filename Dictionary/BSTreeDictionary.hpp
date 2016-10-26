//
// Created by 张师睿 on 16/9/19.
//

#ifndef DATASTRUCTURES_BSTREE_HPP
#define DATASTRUCTURES_BSTREE_HPP

#include "../MyOwnException.h"
#include "AbsDictionary.hpp"
#include "../Tree/LinkedBinaryTree.hpp"


template<class K, class E>
class BSTreeDictionary : public AbsDictionary<K, E> {
public:
    typedef BinaryTreeNode<pair<const K, E>> *TreeNode;

    BSTreeDictionary() : treeSize(0), root() {}

    ~BSTreeDictionary() {
        if (root == nullptr || treeSize == 0)
            return;
        LinkedBinaryTree<pair<const K, E>> lbt(root, treeSize);
        lbt.~LinkedBinaryTree();
    }

    virtual bool empty() const override {
        return treeSize == 0;
    }

    virtual int size() const override {
        return treeSize;
    }

    virtual pair<const K, E> *find(const K &key) const override {
        TreeNode p = root;

        while (p != nullptr) {
            if (p->element.first < key)
                p = p->rightChild;
            else if (p->element.first > key)
                p = p->leftChild;
            else
                return &p->element;
        }

        return nullptr;
    }

    virtual void erase(const K &key) override {
        TreeNode p = root, pp = nullptr;
        while (p != nullptr && p->element.first != key) {
            pp = p;
            if (p->element.first < key)
                p = p->rightChild;
            else if (p->element.first > key)
                p = p->leftChild;
        }
        if (p == nullptr)
            return;
        if (p->leftChild != nullptr && p->rightChild != nullptr) {
            TreeNode s = p->leftChild, ps = p;
            while (s->leftChild != nullptr) {
                ps = s;
                s = s->leftChild;
            }
            TreeNode newNode = new BinaryTreeNode<pair<const K, E>>(s->element, p->leftChild, p->rightChild);
            if (pp == nullptr)
                root = newNode;
            else if (p == pp->leftChild)
                pp->leftChild = newNode;
            else
                pp->rightChild = newNode;

            //以下代码保证了pp是p的父节点，妙啊……
            if (ps == p)
                pp = newNode;
            else
                pp = ps;
            delete p;
            p = s;
        }

        //两个的情况是删除掉那个重复的部分
        TreeNode c = nullptr;
        if (p->leftChild != nullptr)
            c = p->leftChild;
        else
            c = p->rightChild;
        if (pp == nullptr)
            root = c;
        else if (p == pp->leftChild)
            pp->leftChild = c;
        else
            pp->rightChild = c;

        delete p;
        treeSize--;
    }

    virtual void insert(const pair<const K, E> &element) override {
        TreeNode p = root, pp = nullptr;
        while (p != nullptr && p->element.first != element.first) {
            pp = p;
            if (p->element.first < element.first)
                p = p->rightChild;
            else
                p = p->leftChild;
        }
        if (p != nullptr) {
            p->element.second = element.second;
            return;
        }

        TreeNode newNode = new BinaryTreeNode<pair<const K, E>>(element);
        if (pp == nullptr) {
            root = newNode;
        } else {
            if (pp->element.first < element.first)
                pp->rightChild = newNode;
            else
                pp->leftChild = newNode;
        }
        treeSize++;
    }

private:
    int treeSize = 0;
    BinaryTreeNode<pair<const K, E>> *root = nullptr;
};

#endif //DATASTRUCTURES_BSTREE_HPP
