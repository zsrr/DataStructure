//
// Created by 张师睿 on 2016/10/21.
// 字符串操作
// 总之这个能用string代替的时候就代替掉好了

#ifndef DATASTRUCTURES_CHARSEQUENCE_HPP
#define DATASTRUCTURES_CHARSEQUENCE_HPP

#include <algorithm>
#include <ostream>
#include "../LinearList/ArrayList.h"
#include "../MyOwnException.h"

using std::ostream;

class CharSequence : private ArrayList<char> {
    friend ostream &operator<<(ostream &out, CharSequence str);

public:
    CharSequence(const char *str) {
        size = (int) strlen(str) + 1;
        maxSize = 2 * size;
        elements = new char[maxSize];
        copy(str, str + size, elements);
    }

    void append(const char *str) {
        int len = (int) strlen(str);
        if (!checkRoom(len)) {
            changeArrayLength(elements, maxSize, maxSize * 2);
            maxSize *= 2;
        }

        copy(str, str + len + 1, elements + size - 1);
        size += len;
    }

    CharSequence subsequence(int start, int length) {
        if (start + length >= size) {
            throw IllegalParameterValue();
        }

        char *str = new char[length + 1];
        for (int i = start; i < start + length; i++) {
            str[i - start] = elements[i];
        }

        str[length] = '\0';
        return CharSequence(str);
    }

    int getLength() const {
        return size - 1;
    }

    int find(const char &c, int start = 0) const {
        if (start == 0) {
            return indexOf(c);
        }

        for (int i = start; i < size - 1; i++)
            if (elements[i] == c)
                return i;
        return CANNOT_BE_FOUND;
    }

    void replace(const char &old, const char &new_one) {
        if (old == new_one)
            return;

        int loc = find(old, 0);
        while (loc != CANNOT_BE_FOUND) {
            elements[loc] = new_one;
            loc = find(old, loc);
        }
    }

    int find(const char *str, int start = 0) {
        const char *temp_str = elements + start;
        int loc = static_kmp_find(temp_str, str);
        return loc == CANNOT_BE_FOUND ? CANNOT_BE_FOUND : loc + start;
    }

   void replace(const char *old, const char *new_one) {
       int len_old = (int) strlen(old);
       int len_new = (int) strlen(new_one);

       if (len_old != len_new)
           throw IllegalParameterValue();

       int loc = find(old);

       while (loc != CANNOT_BE_FOUND) {
           for (int i = loc; i < loc + len_old; i++) {
               elements[i] = new_one[i - loc];
           }

           loc = find(old, loc + len_old);
       }
   }

private:
    static int static_kmp_find(const char *str, const char *pattern) {
        int length_str = (int) strlen(str);
        int length_pattern = (int) strlen(pattern);
        if (length_pattern > length_str)
//            throw IllegalParameterValue();
            return CANNOT_BE_FOUND;

        int *next = new int[strlen(pattern)];
        static_get_next(pattern, next);

        int i = 0, j = 0;

        while (i < length_str && j < length_pattern) {
            if (j == -1 || str[i] == pattern[j]) {
                i++;
                j++;
            } else {
                j = next[j];
            }
        }

        delete(next);
        if (j == length_pattern)
            return i - j;
        return CANNOT_BE_FOUND;
    }

    static int * static_get_next(const char *str, int *next) {
        int length = (int) strlen(str);

        next[0] = -1;
        int k = -1, j = 0;

        while (j < length - 1) {
            if (k == -1 || str[j] == str[k]) {
                j++;
                k++;
                next[j] = k;
            } else {
                k = next[k];
            }
        }

        return next;
    }

    bool checkRoom(int new_length) {
        return maxSize - size > new_length;
    }
};

ostream &operator<<(ostream &out, CharSequence str) {
    out << str.elements;
    return out;
}

#endif //DATASTRUCTURES_CHARSEQUENCE_HPP
