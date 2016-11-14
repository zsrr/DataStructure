//
// Created by 张师睿 on 2016/10/26.
//

#ifndef DATASTRUCTURES_UTILS_HPP
#define DATASTRUCTURES_UTILS_HPP

#include <algorithm>

using std::copy;

namespace util {
    template<class T>
    void make2dArray(T **&a, int n, int m) {
        a = new T*[n];
        for (int i = 0; i < n; i++) {
            a[i] = new T[m];
        }
    }

    template<class T>
    void dispose2dArray(T **&a, int n) {
        for (int i = 0; i < n; i++) {
            delete[](a[i]);
        }

        delete[](a);
    }

    template<class T>
    void changeArrayLength(T *&target, int oldLength, int newLength) {
        T *newArray = new T[newLength];
        copy(target, target + oldLength, newArray);
        delete[] target;
        target = newArray;
    }
}

#endif //DATASTRUCTURES_UTILS_HPP
