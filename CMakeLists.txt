cmake_minimum_required(VERSION 3.6)
project(DataStructures)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES MyOwnException.h LinearList/LinearList.h Stack/Stack.hpp Stack/ArrayStack.hpp Queue/AbsQueue.hpp Queue/ArrayQueue.hpp Queue/ListQueue.hpp Dictionary/AbsDictionary.hpp Dictionary/HashTableDictionary.hpp Dictionary/SortedChainDictionary.hpp Dictionary/HashChainsDictionary.hpp PriorityQueue/PriorityQueue.hpp PriorityQueue/MaxPriorityQueue.hpp Tree/AbsBinaryTree.hpp  Tree/LinkedBinaryTree.hpp  Tree/WinnerTree.hpp Tree/MaxWinnerTree.hpp Dictionary/BSTreeDictionary.hpp Dictionary/RedBlackTreeDictionary.hpp CharSequence/CharSequence.hpp Graphics/AbsGraph.hpp Tree/ArrayBinaryTree.hpp Graphics/AdjacencyWDiGraph.hpp utils.hpp LinearList/ArrayList.hpp LinearList/LinkedList.hpp main.cpp PriorityQueue/MinPriorityQueue.hpp Tree/HuffmanTree.hpp)
add_executable(DataStructures ${SOURCE_FILES})