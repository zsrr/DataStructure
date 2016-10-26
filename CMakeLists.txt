cmake_minimum_required(VERSION 3.6)
project(DataStructures)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp LinearList/ArrayList.h LinearList/ArrayList.h MyOwnException.h LinearList/LinearList.h LinearList/LinkedList.h Stack/Stack.hpp Stack/ArrayStack.hpp Queue/AbsQueue.hpp Queue/ArrayQueue.hpp Queue/ListQueue.hpp Dictionary/AbsDictionary.hpp Dictionary/HashTableDictionary.hpp Dictionary/SortedChainDictionary.hpp Dictionary/HashChainsDictionary.hpp PriorityQueue/PriorityQueue.hpp PriorityQueue/MaxPriorityQueue.hpp Tree/AbsBinaryTree.hpp  Tree/LinkedBinaryTree.hpp  Tree/WinnerTree.hpp Tree/MaxWinnerTree.hpp Dictionary/BSTreeDictionary.hpp Dictionary/RedBlackTreeDictionary.hpp CharSequence/CharSequence.hpp Graphics/AbsGraph.hpp Tree/ArrayBinaryTree.hpp Graphics/AdjacencyWDiGraph.hpp utils.hpp)
add_executable(DataStructures ${SOURCE_FILES})