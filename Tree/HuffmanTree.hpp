//
// Created by 张师睿 on 2016/11/15.
//

#ifndef DATASTRUCTURES_HUFFMANTREE_HPP
#define DATASTRUCTURES_HUFFMANTREE_HPP

#include "LinkedBinaryTree.hpp"
#include "../PriorityQueue/MinPriorityQueue.hpp"

template<class T>
struct HuffNode {
    T weight;
    LinkedBinaryTree<int> *tree;

    HuffNode() : weight(), tree() {}

    HuffNode(T weight, LinkedBinaryTree<T> *tree) : weight(weight), tree(tree) {}

    bool operator<(const HuffNode<T> &other) {
        return weight < other.weight;
    }

    bool operator>(const HuffNode<T> &other) {
        return weight > other.weight;
    }

    bool operator>=(const HuffNode<T> &other) {
        return !(*this < other);
    }

    bool operator<=(const HuffNode<T> &other) {
        return !(*this > other);
    }
};

template<class T>
LinkedBinaryTree<int> * createHuffmanTree(T weight[], int n) {
    HuffNode<T> *huff_node_array = new HuffNode<T>[n + 1];
    LinkedBinaryTree<int> empty_tree;

    for (int i = 1; i <= n; i++) {
        HuffNode<T> new_node;
        new_node.weight = weight[i];
        new_node.tree = new LinkedBinaryTree<int>();
        new_node.tree->makeTree(i, empty_tree, empty_tree);
        huff_node_array[i] = new_node;
    }

    MinPriorityQueue<HuffNode<T>> heap(n);
    heap.initialize(huff_node_array, n + 1, n);
    HuffNode<T> w, x, y;

    for (int i = 1; i < n; i++) {
        x = heap.top(); heap.pop();
        y = heap.top(); heap.pop();
        w.tree = new LinkedBinaryTree<int>();
        w.tree->makeTree(0, *x.tree, *y.tree);
        w.weight = x.weight + y.weight;
        heap.push(w);
    }

    delete[](huff_node_array);
    return heap.top().tree;
}

#endif //DATASTRUCTURES_HUFFMANTREE_HPP
