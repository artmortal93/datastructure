//
// Created by steafan on 2020/4/12.
//

#ifndef DATASTRUCTURE_BINARYTRIE_H
#define DATASTRUCTURE_BINARYTRIE_H

#include <cstdlib>
#include "utils.h"

/// Binary Trie with bst+ double linked list in the bottom leaf layer
/// Noted: This data structure only affects positive integer data structure
/// SSET interface
/// ordered associative array:map.set...etc
/// \tparam N
/// \tparam T
template <class N,class T> class BinaryTrieNode{
public:
    T x;
    /// jump is the smallerst /biggest value of the subtree if this node dont have two childs
    N* jump;//subtree if do not have 2 childs (for inner childs)
    N* parent;
    //trinity three things shares same store space
    union { //for different trie node(leaf and inner node)
        struct{
            N* left;
            N* right;
        };
        struct{
            N* prev;//binary trie as double linked list in the leaf node layer
            N* next;//the binary trie is used as bottom a double linked list
        };
        N* child[2];
        //these all two means the same thing
    };
    BinaryTrieNode(){
        left=right=parent=jump=NULL;
    }
};


template <class Node,class T> class BinaryTrie{
protected:
    T null;
    enum {left,right};
    enum {prev,next};
    Node r;
    Node dummy;
    int n;
    static const int w=32;
    void clear(Node* u,int d);

public:
    BinaryTrie();
    virtual ~BinaryTrie();
    virtual bool add(T x);
    virtual bool remove(T x);
    virtual T find(T x);
    int size(){
        return n;
    }
    virtual void clear();
};

template <class Node,class T> BinaryTrie<Node,T>::BinaryTrie() {
    dummy.next=&dummy;
    dummy.prev=&dummy;
    r.jump=&dummy;//root do not have effect here
    n=0;
}

template <class Node,class T> BinaryTrie<Node,T>::~BinaryTrie(){
    clear();
}

template <class Node,class T> T BinaryTrie<Node,T>::find(T x) {
    //return the value or the smallest bigger value
    int i,c=0;
    //c=cuurrent bits
    unsigned ix=intValue(x);
    Node* u=&r;
    for(i=0;i<w;i++){
        c=(ix>>(w-i-1))& 1;//shift to least significant bit then masking with 0000001
        if(u->child[c]==NULL)
            break;
        u=u->child[c];
    }
    if(i==w)
        return u->x;
    //return sucessor
    u=(c==0)?u->jump:u->jump->next;//c=1,largest leaf smaller than x, c=0, smallest leaf larger than x
    return u==&dummy?null:u->x;
}

template <class Node,class T> void BinaryTrie<Node,T>::clear(){
    clear(&r,0);
    dummy.next=&dummy;
    dummy.prev=&dummy;
    r.jump=&dummy;
    r.left=NULL;
    r.right=NULL;
    n=0;
}

template <class Node,class T> void BinaryTrie<Node,T>::clear(Node *u, int d) {
    if(u==NULL)
        return;
    if(d<w){
        clear(u->left,d+1);
        clear(u->right,d+1);
    }
    if(d>0)
        delete u;
}

template <class Node,class T> bool BinaryTrie<Node,T>::add(T x) {
    int i,c=0;
    unsigned ix=intValue(x);
    Node* u=&r;
    for(i=0;i<w;i++){
        c=(ix>>(w-i-1))& 1;//shift to least significant bit then masking with 0000001
        if(u->child[c]==NULL)
            break;
        u=u->child[c];
    }
    if(i==w)
        return false;
    Node* pred=(c==right)?u->jump:u->jump->left;//pred leaf node
    u->jump=NULL;//u will have two child temproary
    //now currently the i has the stop node path
    for(;i<w;i++){
        c=(ix>>(w-i-1))& 1;
        u->child[c]=new Node();
        u->child[c]->parent=u;
        u=u->child[c];
    }

    //construct the missing path for new Node
    u->x=x;
    //3. add u to linked list
    u->prev=pred;
    u->next=pred->next;
    u->prev->next=u;
    u->next->prev=u;
    //4.walk up to update jump pointers
    Node* v=u->parent;
    while(v!=NULL){
        if(    //single node and corresponding node's jump need to update(both we mark as NULL to fix up and really needs to update)
               //c=1,largest leaf smaller than x, c=0, smallest leaf larger than x
                (v->left==NULL && (v->jump==NULL || intValue(v->jump->x)>ix))
                ||
                (v->right==NULL && (v->jump=NULL || intValue(v->jump->x)<ix))
                )
            v->jump=u;
        v=v->parent;
    }
    n++;
    return true;
}

template <class Node,class T> bool BinaryTrie<Node,T>::remove(T x){
    //finding like add
    int i,c=0;
    unsigned ix=intValue(x);
    Node* u=&r;
    for(i=0;i<w;i++){
        c=(ix>>(w-i-1))& 1;//shift to least significant bit then masking with 0000001
        if(u->child[c]==NULL)
            return false;
        u=u->child[c];
    }

    //remove from linked list
    u->prev->next=u->next;
    u->next->prev=u->prev;
    Node *v=u;
    //delete nodes on path to u
    for(int i=w-1;i>=0;i--){
        c=(ix>>(w-i-1))& 1;
        v=v->parent;
        delete v->child[c];
        v->child[c]=NULL;
        if(v->child[1-c]!=NULL)
            break;
    }
    //update jump pointers,go upwards
    //v is now the remain parent in the path of u,and should have one child
    c=(ix>>(w-i-1))& 1;
    v->jump=u->child[1-c];//if c=0,use right child,if c=1, use left child
    v=v->parent;
    i--;
    for(;i>=0;i--){
        c=(ix>>(w-i-1))& 1;
        if(v->jump==u){
            v->jump=u->child[1-c];
        }
        v=v->parent;
    }
    n--;
    return true;
}


template <class T> class BinaryTrieNode1 :public BinaryTrieNode<BinaryTrieNode1<T>,T>{};

template <class T> class BinaryTrie1: public BinaryTrie<BinaryTrieNode1<T>,T>{};
#endif //DATASTRUCTURE_BINARYTRIE_H
