//
// Created by 张师睿 on 16/9/13.
//

#ifndef DATASTRUCTURES_SORTEDCHAIN_HPP
#define DATASTRUCTURES_SORTEDCHAIN_HPP

#include "AbsDictionary.hpp"

using std::pair;

template <class K, class E>
struct PairNode {
    pair<const K, E> element;
    PairNode<K, E>* next;

    //注意初始化和赋值的区别!
    PairNode(const pair<const K, E>& theElement) : element(theElement) {
        next = nullptr;
    }

    PairNode(const pair<const K, E>& theElement, PairNode<K, E>* theNext) : element(theElement){
        next = theNext;
    }
};

template <class K, class E>
class SortedChainDictionary : public AbsDictionary<K, E> {
public:
    SortedChainDictionary() = default;

    virtual bool empty() const override {
        return dSize == 0;
    }

    virtual int size() const override {
        return dSize;
    }

    virtual pair<const K, E> *find(const K &key) const override {
        PairNode<K, E>* cur = firstNode;
        while (cur != nullptr && cur->element.first < key) {
            cur = cur->next;
        }

        if (cur != nullptr && cur->element.first == key) {
            return &cur->element;
        }

        return nullptr;
    }

    virtual void erase(const K &key) override {
        PairNode<K, E> *p = firstNode, *tp = nullptr;
        while (p != nullptr && p->element.first < key) {
            tp = p;
            p = p->next;
        }

        if (p != nullptr && p->element.first == key) {
            if (tp == nullptr) {
                firstNode = firstNode->next;
            } else {
                tp->next = p->next;
            }
            delete p;
            dSize--;
        }
    }

    virtual void insert(const pair<const K, E> &element) override {
        PairNode<K, E> *p = firstNode, *tp = nullptr;
        while (p != nullptr && p->element.first < element.first) {
            tp = p;
            p = p->next;
        }

        if (p != nullptr && p->element.first == element.first) {
            p->element.second = element.second;
            return;
        }

        if (tp == nullptr) {
            firstNode = new PairNode<K, E>(element);
        } else {
            tp->next = new PairNode<K, E>(element, p);
        }
        dSize++;
    }

    ~SortedChainDictionary() {
        PairNode<K, E>* cur = nullptr;
        while (firstNode != nullptr) {
            cur = firstNode->next;
            delete firstNode;
            firstNode = cur;
        }
    }

private:
    int dSize = 0;
    PairNode<K, E>* firstNode = nullptr;
};

#endif //DATASTRUCTURES_SORTEDCHAIN_HPP
