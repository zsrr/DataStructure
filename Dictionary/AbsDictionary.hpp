//
// Created by 张师睿 on 16/9/12.
//

#ifndef DATASTRUCTURES_DICTIONARY_HPP
#define DATASTRUCTURES_DICTIONARY_HPP

#include <utility>

using std::pair;

template<class K, class E>
class AbsDictionary {
public:
    virtual ~AbsDictionary() {}

    virtual bool empty() const = 0;

    virtual int size() const = 0;

    virtual pair<const K, E> *find(const K &key) const = 0;

    virtual void erase(const K &key) = 0;

    virtual void insert(const pair<const K, E> &element) = 0;

    virtual void put(const K &key, const E &value) {
        insert(pair<const K, E>(key, value));
    }

    virtual const E &get(const K &key) const {
        return find(key)->second;
    }
};

#endif //DATASTRUCTURES_DICTIONARY_HPP
