//
// Created by steaphan on 14/4/2020.
//

#ifndef DATASTRUCTURE_XFASTTRIE_H
#define DATASTRUCTURE_XFASTTRIE_H

/// x-fast trie =binary trie+ hast table with size w+1


#include "BinaryTrie.h"
#include "LinearHashTable.hpp"
#include <climits>

template<class Node, class T>
class XFastTrieNode : public BinaryTrieNode<Node,T> {
public:
};

template <class Node> class XPair{
public:
    unsigned prefix;
    Node* u;
    XPair(int prefix0){
        prefix=prefix0;
        u=NULL;
    }
    XPair(int prefix0,Node *u0){
        prefix=prefix0;
        u=u0;
    }
    bool operator==(XPair &p){
        return prefix==p.prefix;
    }
    bool operator!=(XPair &p){
        return prefix!= p.prefix;
    }
};

template <class Node> int hashCode(XPair<Node> &p){
    return p.prefix;
}

template<class Node, class T>
class XFastTrie : public BinaryTrie<Node,T> {
protected:
    T nullt;
    using BinaryTrie<Node,T>::w;
    using BinaryTrie<Node,T>::n;
    using BinaryTrie<Node,T>::r;
    using BinaryTrie<Node,T>::right;
    using BinaryTrie<Node,T>::left;
    using BinaryTrie<Node,T>::dummy;
    XPair<Node> null;
    LinearHashTable<XPair<Node> > t[w+1];
public:
    XFastTrie();
    virtual ~XFastTrie();
    T find(T x);
    bool add(T x);
    bool remove(T x);
    void clear();
    Node* findNode(unsigned ix); // FIXME: should be protected
};




template<class T>
class XFastTrieNode1 : public XFastTrieNode<XFastTrieNode1<T>, T> { };


#endif //DATASTRUCTURE_XFASTTRIE_H
