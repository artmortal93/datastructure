//
// Created by steafan on 2020/4/9.
//

#ifndef DATASTRUCTURE_MELDABLEHEAP_H
#define DATASTRUCTURE_MELDABLEHEAP_H


#include "BinaryTree.h"
//meldable heap== fbiohnacci heap
template <class Node,class T> class MedlableHeap;

template <class Node,class T> class MHeapNode:public BTNode<Node>{
public:
    T x;
};

template <class Node,class T> class MeldableHeap:public BinaryTree<Node>{
protected:
    using BinaryTree<Node>::r;
    using BinaryTree<Node>::nil;
    int n;
    Node* merge(Node *h1,Node* h2);
public:
    MeldableHeap();
    virtual ~MeldableHeap();
    bool add(T x);
    T findMin();
    T remove();
    void remove(Node *u);
    int size() {
        return n;
    }
};

template<class T>
class MHeapNode1 : public MHeapNode<MHeapNode1<T>, T> { };

template<class T>
class MeldableHeap1 : public MeldableHeap<MHeapNode1<T>, T> { };

template<class Node, class T>
MeldableHeap<Node,T>::MeldableHeap() {
    n = 0;
}

template<class Node, class T>
MeldableHeap<Node,T>::~MeldableHeap() {
    // nothing to do
}

//merge two nodes,
//return node that contain all the node in this two subtrees
//recursively do so
template <class Node,class T> Node* MeldableHeap<Node,T>::merge(Node *h1, Node *h2) {
    if(h1==nil)
        return h2;
    if(h2==nil)
        return h1;
    if(compare(h1->x,h2->x)>0)
        return merge(h2,h1);
    ///h1 always <h2
    if(rand()%2){
        h1->left=merge(h1->left,h2);
        if(h1->left!=nil)
            h1->left->parent=h1;
    }
    else{
        //merge two larger nodes, and make h1's new child
        h1->right =merge(h1->right,h2);
        if(h1->right!=nil)
            h1->right->parent=h1;
    }
    return h1;
}

template <class Node,class T> T MeldableHeap<Node,T>::findMin() {
    return r->x;
}

template <class Node,class T> bool MeldableHeap<Node,T>::add(T x) {
    Node *u=new Node();
    u->left=u->parent=u->right=nil;
    u->x=x;
    r=merge(u,r);
    r->parent=nil;
    n++;
    return true;
}

//remove in a priority
template <class Node,class T> T MeldableHeap<Node,T>::remove() {
    T x=r->x;
    Node *tmp=r;
    r=merge(r->left,r->right);
    delete tmp;
    if(r!=nil)
        r->parent=nil;
    n--;
    return x;
}

template <class Node,class T> void MeldableHeap<Node,T>::remove(Node *u) {
    if(u==r)
        remove();
    else{
        if(u==u->parent->left){
            u->parent->left=nil;
        }
        else{
            u->parent->right=nil;
        }
        u->parent=nil;
        ///merge two subtrees
        r=merge(r,u->left);
        r=merge(r,u->right);
        r->parent=nil;
        n--;
    }
}
                                                    \
#endif //DATASTRUCTURE_MELDABLEHEAP_H
