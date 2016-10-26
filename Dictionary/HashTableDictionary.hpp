//
// Created by 张师睿 on 16/9/12.
//

#ifndef DATASTRUCTURES_HASHTABLE_HPP
#define DATASTRUCTURES_HASHTABLE_HPP

#include <map>
#include "AbsDictionary.hpp"
#include "../MyOwnException.h"

using std::pair;
using std::hash;

template<class K, class E>
class HashTableDictionary : public AbsDictionary<K, E> {
public:
    HashTableDictionary(int divisor = 21) {
        if (divisor <= 0) {
            throw IllegalDivisorException();
        }
        this->divisor = divisor;
        this->dSize = 0;
        table = new pair<const K, E> *[divisor];
        for (int i = 0; i < divisor; i++) {
            table[i] = nullptr;
        }
    }

    virtual bool empty() const override {
        return dSize == 0;
    }

    virtual int size() const override {
        return dSize;
    }

    virtual pair<const K, E> *find(const K &key) const override {
        int b = search(key);
        //还没有插入以及表已经满的情况
        if (table[b] == nullptr || table[b]->first != key)
            return nullptr;
        return table[b];
    }

    virtual void erase(const K &key) override {
        if (empty()) {
            throw HashTableEmptyException();
        }
        int b = search(key);

        if (table[b]->first == key) {
            delete table[b];
            table[b] = nullptr;
        }
        dSize--;
    }

    virtual void insert(const pair<const K, E> &element) override {
        int b = search(element.first);
        if (table[b] == nullptr) {
            table[b] = new pair<const K, E>(element);
        } else if (table[b]->first == element.first) {
            table[b]->second = element.second;
        } else {
            throw HashTableFullException();
        }
        dSize++;
    }
private:
    int dSize;
    int divisor;
    hash<K> hash;
    pair<const K, E> **table;

    int search(const K &key) const {
        int i = (int) hash(key) % divisor;
        int j = i;

        do {
            if (table[j] == nullptr || table[j]->first == key)
                return j;
            j = (j + 1) % divisor;
        } while (j != i);

        return j;
    }
};

#endif //DATASTRUCTURES_HASHTABLE_HPP
