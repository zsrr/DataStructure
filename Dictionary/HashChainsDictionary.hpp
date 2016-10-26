//
// Created by 张师睿 on 16/9/13.
//

#ifndef DATASTRUCTURES_HASHCHAINS_HPP
#define DATASTRUCTURES_HASHCHAINS_HPP

#include <map>
#include "SortedChainDictionary.hpp"
#include "AbsDictionary.hpp"
#include "../MyOwnException.h"

using std::hash;

template <class K, class E>
class HashChainsDictionary : public AbsDictionary<K, E> {
public:
    HashChainsDictionary(int theDivisor = 21) {
        if (theDivisor <= 0) {
            throw IllegalDivisorException();
        }
        table = new SortedChainDictionary<K, E>[theDivisor];
        divisor = theDivisor;
        dSize = 0;
    }

    virtual bool empty() const override {
        return dSize == 0;
    }

    virtual int size() const override {
        return dSize;
    }

    virtual pair<const K, E> *find(const K &key) const override {
        return table[hash(key) % divisor].find(key);
    }

    virtual void erase(const K &key) override {
        int homeBucket = hash(key) % divisor;
        int preSize = table[homeBucket].size();
        table[hash(key) % divisor].erase(key);
        if (preSize > table[homeBucket].size())
            dSize--;
    }

    virtual void insert(const pair<const K, E> &element) override {
        int homeBucket = hash(element.first) % divisor;
        int preSize = table[homeBucket].size();
        table[homeBucket].insert(element);
        if (preSize < table[homeBucket].size())
            dSize++;
    }

    ~HashChainsDictionary() {
        delete[] table;
    }
private:
    SortedChainDictionary<K, E> *table;
    int dSize;
    int divisor;
    hash<K> hash;
};

#endif //DATASTRUCTURES_HASHCHAINS_HPP
