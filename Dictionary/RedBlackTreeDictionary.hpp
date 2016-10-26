//
// Created by 张师睿 on 16/9/21.
//

#ifndef DATASTRUCTURES_REDBLACKTREE_HPP
#define DATASTRUCTURES_REDBLACKTREE_HPP

#include "AbsDictionary.hpp"
#include "../MyOwnException.h"

enum Color {
    RED, BLACK, NONE
};

template<class T>
struct RBTreeNode {
    T element;
    Color color;
    RBTreeNode<T> *leftChild;
    RBTreeNode<T> *rightChild;
    RBTreeNode<T> *parent;

    RBTreeNode() : element(), leftChild(), rightChild(), parent() {
        color = BLACK;
    }

    RBTreeNode(const T &element) : element(element), leftChild(), rightChild(), parent() {
        color = NONE;
    }

    RBTreeNode(const T &element, RBTreeNode<T> *left,
               RBTreeNode<T> *right, RBTreeNode<T> *parent) : element(element), leftChild(left),
                                                              rightChild(right), parent(parent) {
        color = NONE;
    }

    RBTreeNode(const T &element, RBTreeNode<T> *left,
               RBTreeNode<T> *right, RBTreeNode<T> *parent, Color color) :
            RBTreeNode(element, left, right, parent) {
        this->color = color;
    }
};

template<class K, class E>
class RedBlackTreeDictionary : public AbsDictionary<K, E> {
public:
    RedBlackTreeDictionary() = default;

    ~RedBlackTreeDictionary() {
        dispose(root);
        delete tab;
    }

    virtual bool empty() const override {
        return treeSize == 0;
    }

    virtual int size() const override {
        return treeSize;
    }

    virtual pair<const K, E> *find(const K &key) const override {
        TreeNodePtr p = root;
        while (p != tab) {
            if (p->element.first == key)
                return &p->element;
            else if (p->element.first < key)
                p = p->rightChild;
            else
                p = p->leftChild;
        }
        return nullptr;
    }

    virtual void erase(const K &key) override {
        if (empty())
            throw DictionaryEmptyException();

        TreeNodePtr p = root;
        while (p != tab) {
            if (p->element.first == key)
                break;
            else if (p->element.first < key)
                p = p->rightChild;
            else
                p = p->leftChild;
        }
        if (p == tab)
            return;

        TreeNodePtr y = p;
        Color original_color = y->color;
        TreeNodePtr x = tab;

        if (p->leftChild == tab) {
            x = p->rightChild;
            transplant(p, p->rightChild);
        } else if (p->rightChild == tab) {
            x = p->leftChild;
            transplant(p, p->leftChild);
        } else {
            y = tree_minimum(p->rightChild);
            x = y->rightChild;
            original_color = y->color;

            if (y->parent == p)
                x->parent = y;
            else {
                transplant(y, y->rightChild);
                y->rightChild = p->rightChild;
                y->rightChild->parent = y;
            }
            transplant(p, y);
            y->leftChild = p->leftChild;
            y->leftChild->parent = y;
            y->color = p->color;
        }

        if (original_color == BLACK)
            erase_fixup(x);
        treeSize--;
    }

    virtual void insert(const pair<const K, E> &element) override {
        TreeNodePtr y = tab;
        TreeNodePtr x = root;

        while (x != tab) {
            y = x;
            if (x->element.first == element.first) {
                x->element.second = element.second;
                return;
            } else if (x->element.first > element.first)
                x = x->leftChild;
            else
                x = x->rightChild;
        }

        TreeNodePtr newNode = new TreeNode(element);
        newNode->parent = y;
        if (y == tab) {
            root = newNode;
            root->leftChild = tab;
            root->rightChild = tab;
            root->color = BLACK;
            treeSize++;
            return;
        }
        else if (element.first > y->element.first)
            y->rightChild = newNode;
        else
            y->leftChild = newNode;
        treeSize++;
        newNode->leftChild = tab;
        newNode->rightChild = tab;
        newNode->color = RED;
        insert_fixup(newNode);
    }

private:
    typedef RBTreeNode<pair<const K, E>> *TreeNodePtr;

    typedef RBTreeNode<pair<const K, E>> TreeNode;
    int treeSize = 0;
    TreeNodePtr tab = new TreeNode();
    TreeNodePtr root = tab;

    void left_rotate(TreeNodePtr p) {
        TreeNodePtr x = p->rightChild;
        p->rightChild = x->leftChild;
        if (x->leftChild != tab)
            x->leftChild->parent = p;
        x->parent = p->parent;
        if (p->parent == tab)
            root = x;
        else if (p == p->parent->leftChild)
            p->parent->leftChild = x;
        else
            p->parent->rightChild = x;
        x->leftChild = p;
        p->parent = x;
    }

    void right_rotate(TreeNodePtr p) {
        TreeNodePtr x = p->leftChild;
        p->leftChild = x->rightChild;
        if (x->rightChild != tab)
            x->rightChild->parent = p;

        x->parent = p->parent;
        if (p->parent == tab)
            root = x;
        else if (p->parent->leftChild == p)
            p->parent->leftChild = x;
        else
            p->parent->rightChild = x;

        x->rightChild = p;
        p->parent = x;
    }

    void transplant(TreeNodePtr lh, TreeNodePtr rh) {
        if (lh->parent == tab)
            root = rh;
        else if (lh == lh->parent->leftChild)
            lh->parent->leftChild = rh;
        else
            lh->parent->rightChild = rh;
        rh->parent = lh->parent;
    }

    TreeNodePtr tree_minimum(TreeNodePtr nodePtr) {
        while (nodePtr->leftChild != tab)
            nodePtr = nodePtr->leftChild;
        return nodePtr;
    }

    void insert_fixup(TreeNodePtr node) {
        while (node->parent->color == RED) {
            TreeNodePtr parent = node->parent;
            TreeNodePtr y = nullptr;
            TreeNodePtr node_grand_parent = parent->parent;

            if (parent == node_grand_parent->leftChild) {
                y = node_grand_parent->rightChild;
                if (y->color == RED) {
                    node_grand_parent->color = RED;
                    y->color = BLACK;
                    parent->color = BLACK;
                    node = node_grand_parent;
                    continue;
                } else if (node == parent->rightChild) {
                    node = parent;
                    left_rotate(node);
                }
                parent->color = BLACK;
                node_grand_parent->color = RED;
                right_rotate(node_grand_parent);
            } else {
                y = node_grand_parent->leftChild;
                if (y->color == RED) {
                    node_grand_parent->color = RED;
                    y->color = BLACK;
                    parent->color = BLACK;
                    node = node_grand_parent;
                    continue;
                } else if (node == parent->leftChild) {
                    node = parent;
                    right_rotate(node);
                }
                parent->color = BLACK;
                node_grand_parent->color = RED;
                left_rotate(node_grand_parent);
            }
        }
        root->color = BLACK;
    }

    void erase_fixup(TreeNodePtr node) {
        while (node != root && node->color == BLACK) {
            TreeNodePtr node_parent = node->parent;
            if (node == node_parent->leftChild) {
                TreeNodePtr bro = node_parent->rightChild;
                if (bro->color == RED) {
                    bro->color = BLACK;
                    node_parent->color = RED;
                    left_rotate(node_parent);
                    bro = node_parent->rightChild;
                }
                if (bro->leftChild->color == BLACK && bro->rightChild->color == BLACK) {
                    bro->color = RED;
                    node = node_parent;
                } else {
                    if (bro->rightChild->color == BLACK) {
                        bro->leftChild->color = BLACK;
                        bro->color = RED;
                        right_rotate(bro);
                        bro = node_parent->rightChild;
                    }
                    bro->color = node_parent->color;
                    node_parent->color = BLACK;
                    bro->rightChild->color = BLACK;
                    left_rotate(node_parent);
                    node = root;
                }
            } else {
                TreeNodePtr bro = node_parent->leftChild;
                if (bro->color == RED) {
                    bro->color = BLACK;
                    node_parent->color = RED;
                    right_rotate(node_parent);
                    bro = node_parent->leftChild;
                }
                if (bro->rightChild->color == BLACK && bro->leftChild->color == BLACK) {
                    bro->color = RED;
                    node = node_parent;
                } else {
                    if (bro->leftChild->color == BLACK) {
                        bro->rightChild->color = BLACK;
                        bro->color = RED;
                        left_rotate(bro);
                        bro = node_parent->leftChild;
                    }
                    bro->color = node_parent->color;
                    node_parent->color = BLACK;
                    bro->leftChild->color = BLACK;
                    right_rotate(node_parent);
                    node = root;
                }
            }
        }
        node->color = BLACK;
    }

    void dispose(TreeNodePtr root) {
        if (root != tab) {
            dispose(root->leftChild);
            dispose(root->rightChild);
            delete root;
        }
    }
};

#endif //DATASTRUCTURES_REDBLACKTREE_HPP
