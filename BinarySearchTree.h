//
// Created by steaphan on 29/2/2020.
//

#ifndef DATASTRUCTURE_BINARYSEARCHTREE_H
#define DATASTRUCTURE_BINARYSEARCHTREE_H

#include <climits>
#include <cmath>
#include "utils.h"
#include "BinaryTree.h"

template <class Node,class T> class BSTNode:public BTNode<Node>{
    //with left,right and parent
public:
    T x;
};

//THe Node parameter should be subclass of BSTNode<T>
//example
//template class BTNode2<BTNode2,int>
template <class Node,class T> class BinarySearchTree:public BinaryTree<Node>{
protected:
    using BinaryTree<Node>::r;
    using BinaryTree<Node>::nil;//null node
    int n;
    T null;
    virtual Node* findLast(T x);
    virtual bool addChild(Node* p,Node* u);
    virtual void splice(Node* u);//splice the node(stick them together
    virtual void remove(Node* u);
    virtual void rotateRight(Node* u);
    virtual void rotateLeft(Node* u);
    virtual bool add(Node* u);

public:
    BinarySearchTree();
    explicit BinarySearchTree(T null);
    virtual ~BinarySearchTree();
    virtual bool add(T x);
    virtual bool remove(T x);
    virtual T find(T x);
    virtual T findEQ(T x);
    virtual int size(){return n;};
    virtual void clear();
};
//usable node
template <class T> class BSTNode1:public BSTNode<BSTNode1<T>,T>{};

template <class T> class BinarySearchTree1:public BinarySearchTree<BSTNode1<T>,T>{
public:
    BinarySearchTree1();
};

template <class Node,class T>
BinarySearchTree<Node,T>::BinarySearchTree() {
    this->null=(T)NULL;//wont work for non-pimitive types
    n=0;
}

template<class Node, class T>
BinarySearchTree<Node,T>::BinarySearchTree(T null) {
    this->null = null;
    n = 0;
}

template<class Node, class T>
BinarySearchTree<Node,T>::~BinarySearchTree() {
    // nothing to do - BinaryTree destructor does cleanup
}

template <class Node,class T> T BinarySearchTree<Node,T>::findEQ(T x) {
    Node *w=r;
    while(w!=nil){
        int comp=compare(x,w->x);
        if(comp<0){
            w=w->left;
        }
        else if(comp>0){
            w=w->right;
        }
        else{
            return w->x;
        }
    }
    return null;
}

template <class Node,class T> T BinarySearchTree<Node,T>::find(T x) {
    //find the smallest value greater than x
    Node *w=r,*z=nil;//keep the last node
    while (w!=nil){
        int comp=compare(x,w->x);
        if(comp<0){
            z=w;
            w=w->left;
        }
        else if(comp>0){
            w=w->right;
        }
        else{
            return w->x;
        }
    }
    return z==nil?null:z->x;
}
//find the node that equal the value x or should be the father of this value x
template <class Node,class T> Node* BinarySearchTree<Node,T>::findLast(T x) {
    Node* w=r,*prev=nil;
    while(w!=nil){
        //in case a non-parent node type BST
        //should not be here should in the 3-branch prediction to produce correct w
        //prev=w;//record w
        int comp=compare(x,w->x);
        if(comp<0){
            prev=w;
            w=w->left;
        }
        else if(comp>0){
            prev=w;
            w=w->right;
        }
        else{
            return w;
        }
    }
    return prev;//return nil means the tree is empty
}


template <class Node,class T> bool BinarySearchTree<Node,T>::addChild(Node *p, Node *u) {
    if(p==nil){
        r=u;//empty tree
    }
    else{
        int comp=compare(u->x,p->x);
        if(comp<0){
            p->left=u;
        }
        else if(comp>0){
            p->right=u;
        }
        else{
            return false;
        }
        u->parent=p;
    }
    n++;
    return true;
}


template <class Node,class T> bool BinarySearchTree<Node,T>::add(T x) {
    Node* p=findLast(x);
    Node* u=new Node;
    u->x=x;
    return addChild(p,u);
}

template <class Node,class T> bool BinarySearchTree<Node,T>::add(Node *u){
    Node *p=findLast(u->x);
    return addChild(p,u);
}

template<class T>
BinarySearchTree1<T>::BinarySearchTree1()  {
}

template<class Node, class T> inline
void BinarySearchTree<Node, T>::clear() {
    BinaryTree<Node>::clear();
    n = 0;
}

template <class Node,class T> void BinarySearchTree<Node,T>::splice(Node *u) {
    //process case that node has 0-1 child to remove
    Node *s,*p;
    if(u->left != nil){
        s=u->left;
    }
    else{
        s=u->right;//s=son
    }
    if(u==r){
        r=s;
        p=nil;
    }
    else{
        p=u->parent;
        if(p->left==u){
            p->left=s;
        }
        else{
            p->right=s;
        }
    }
    if(s!=nil)
        s->parent=p;
    n--;
}

template <class Node,class T> void BinarySearchTree<Node,T>::remove(Node *u) {
    if(u->left==nil || u->right==nil){
        splice(u);
        delete u;//delete u in 0 sprout and 1 sprout case
    }
    else{
        Node* w=u->right;
        while(w->left!=nil)//find the closest bigger value and replace u with that
            w=w->left;//gauranted to has almost 1 node child to use splice
        u->x=w->x;
        splice(w);
        delete w;
    }
}

template <class Node,class T> bool BinarySearchTree<Node,T>::remove(T x) {
    Node* u=findLast(x);
    if(u!=nil && compare(x,u->x)==0){
        remove(u);
        return true;
    }
    //for tree that dont have a parent pointer,need to expand the findLast and
    //retireve the u,p pointer and based on the condition
    return false;//could not find the node
}
///
///   u
///  a  w
///    b  c  left
///     w
///    u   c  right
///  a   b
//must have parents
template <class Node,class T> void BinarySearchTree<Node,T>::rotateLeft(Node *u) {
    Node *w=u->right;  //node c
    w->parnet=u->parent;//change position
    //determine the left or right subtree for the parent node
    if(w->parent!=nil){
        if(w->parent->left==u)
            w->parent->left=w;
        else{
            w->parent->right=w;
        }
    }
    u->right=w->left;//node b change owner
    if(u->right!=nil)
        u->right->parent=u;
    //node a,c has no effect
    u->parent=w;
    w->left=u;
    //processing node cases
    if(u==r)
    {
        r=w;
        r->parent=nil;//seems redundant
    }
}

template <class Node,class T> void BinarySearchTree<Node,T>::rotateRight(Node *u) {
    //mirror implementation
    Node *w = u->left;
    w->parent = u->parent;
    if (w->parent != nil) {
        if (w->parent->left == u) {
            w->parent->left = w;
        } else {
            w->parent->right = w;
        }
    }
    u->left = w->right;
    if (u->left != nil) {
        u->left->parent = u;
    }
    u->parent = w;
    w->right = u;
    if (u == r) { r = w; r->parent = nil; }
}


#endif //DATASTRUCTURE_BINARYSEARCHTREE_H
