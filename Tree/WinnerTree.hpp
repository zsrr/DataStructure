//
// Created by 张师睿 on 16/9/18.
//

#ifndef DATASTRUCTURES_WINNERTREE_HPP
#define DATASTRUCTURES_WINNERTREE_HPP

template<class T>
class WinnerTree {
public:
    virtual ~WinnerTree() {}

    virtual void initialize(T *players, int numberOfPlayers) = 0;

    virtual int winner() const = 0;

    virtual void replay(int player) = 0;
};

#endif //DATASTRUCTURES_WINNERTREE_HPP
