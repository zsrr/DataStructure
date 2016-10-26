//
// Created by 张师睿 on 16/9/18.
// 最大赢者树
//

#ifndef DATASTRUCTURES_MAXWINNERTREE_HPP
#define DATASTRUCTURES_MAXWINNERTREE_HPP

#include "WinnerTree.hpp"
#include "../MyOwnException.h"
#include "../Queue/ListQueue.hpp"
#include <ostream>

using std::ostream;

template<class T>
class MaxWinnerTree : public WinnerTree<T> {
    friend ostream &operator<<(ostream &out, const MaxWinnerTree<T> &maxWinnerTree) {
        if (maxWinnerTree.players == nullptr || maxWinnerTree.numberOfPlayers < 2) {
            throw IllegalParameterValue();
        }

        const int max = maxWinnerTree.numberOfPlayers;
        ListQueue<int> lq;
        int i = 1;

        while (i < max) {
            out << maxWinnerTree.players[maxWinnerTree.tree[i]] << " ";
            if (2 * i < max)
                lq.push(2 * i);
            if (2 * i + 1 < max)
                lq.push(2 * i + 1);
            try {
                i = lq.front();
                lq.pop();
            } catch (QueueEmptyException e) {
                return out;
            }
        }

        return out;
    }

public:
    MaxWinnerTree() = default;

    ~MaxWinnerTree() { delete[] tree; }

    virtual void initialize(T *players, int numberOfPlayers) override {
        if (numberOfPlayers < 2) {
            throw IllegalParameterValue();
        }
        //注意players的下标，最后一个元素不用，第一个元素不用
        this->players = players;
        this->numberOfPlayers = numberOfPlayers;
        const int n = numberOfPlayers;
        //第一个节点不要
        tree = new int[n];

        int i, s;
        //这个循环最大能让s到达n - 1
        for (s = 1; 2 * s <= (n - 1); s *= 2);

        lowExt = 2 * (n - s);
        offset = 2 * s - 1;

        for (i = 2; i <= lowExt; i += 2) {
            play((i + offset) / 2, i - 1, i);
        }
        if (n % 2) {
            play(n / 2, tree[n - 1], lowExt + 1);
            i = lowExt + 3;
        } else i = lowExt + 2;

        for (; i <= n; i += 2) {
            play((i - lowExt + n - 1) / 2, i - 1, i);
        }
    }

    virtual int winner() const override {
        return tree[1];
    }

    virtual void replay(int player) override {
        const int n = numberOfPlayers;
        if (player <= 0 || player > n) {
            throw IllegalParameterValue();
        }

        int matchNode, leftChild, rightChild;
        if (player <= lowExt) {
            matchNode = (player + offset) / 2;
            leftChild = 2 * matchNode - offset;
            rightChild = leftChild + 1;
        } else {
            matchNode = (player - lowExt + n - 1) / 2;
            //这个是基数的特殊情况
            if (2 * matchNode == n - 1) {
                leftChild = tree[n - 1];
                rightChild = player;
            } else {
                leftChild = 2 * matchNode + lowExt - n + 1;
                rightChild = leftChild + 1;
            }
        }

        tree[matchNode] = (players[leftChild] > players[rightChild])
                          ? leftChild : rightChild;
        if (matchNode == n - 1 && n % 2) {
            matchNode /= 2;
            tree[matchNode] = (players[tree[n - 1]] > players[lowExt + 1])
                              ? tree[n - 1] : lowExt + 1;
        }

        matchNode /= 2;
        for (; matchNode >= 1; matchNode /= 2) {
            tree[matchNode] = (players[tree[2 * matchNode]] > players[tree[2 * matchNode + 1]])
                              ? tree[2 * matchNode] : tree[2 * matchNode + 1];
        }
    }

private:
    int lowExt = 0;
    int offset = 0;
    int *tree = nullptr;
    int numberOfPlayers = 0;
    T *players = nullptr;

    void play(int p, int leftChild, int rightChild) {
        tree[p] = (players[leftChild] >= players[rightChild])
                  ? leftChild : rightChild;
        while (p % 2 && p > 1) {
            tree[p / 2] = (players[tree[p - 1]] > players[tree[p]])
                          ? tree[p - 1] : tree[p];
            p /= 2;
        }
    }
};

template<class T>
ostream &operator<<(ostream &out, const MaxWinnerTree<T> &maxWinnerTree);

#endif //DATASTRUCTURES_MAXWINNERTREE_HPP
