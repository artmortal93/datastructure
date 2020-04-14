#cmake_minimum_required(VERSION 3.15)
project(datastructure)

set(CMAKE_CXX_STANDARD 14)

add_executable(datastructure main.cpp
        array.hpp array.cpp ArrayStack.cpp
        ArrayStack.hpp FastArrayStack.cpp
        FastArrayStack.hpp utils.h
        ArrayQueue.cpp ArrayQueue.h ArrayDeque.cpp
        ArrayDeque.h DualArrayDeque.cpp DualArrayDeque.h RootishArrayStack.cpp
        RootishArrayStack.h SLList.cpp SLList.h DLList.cpp DLList.h
        SEList.cpp SEList.h SkipListSSet.cpp SkipListSSet.h
        SkiplistLIst.cpp SkiplistLIst.h
        ChainedHashTable.hpp ChainedHashTable.cpp
        LinearHashTable.cpp LinearHashTable.hpp
        GeomVector.h BinaryTree.cpp BinaryTree.h
        BinarySearchTree.cpp BinarySearchTree.h Treap.cpp Treap.h ScapegoatTree.cpp ScapegoatTree.h
        RedBlackTree.cpp RedBlackTree.h
        AVLTree.h AVLTree.cpp
        BinaryHeap.h BinaryHeap.cpp
        MeldableHeap.cpp MeldableHeap.h
        algorthim.h StringAlgorthim.h GraphAlgorthim.h AdjacencyMatrix.cpp AdjacencyMatrix.h AdjacencyList.cpp AdjacencyList.h BinaryTrie.cpp BinaryTrie.h XFastTrie.cpp XFastTrie.h YFastTrie.cpp YFastTrie.h BlockStore.cpp BlockStore.h BTree.cpp BTree.h)
