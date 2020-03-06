//
// Created by steaphan on 5/3/2020.
//
#ifndef DATASTRUCTURE_SCAPEGOATTREE_H
#define DATASTRUCTURE_SCAPEGOATTREE_H

#include <cmath>
#include "BinarySearchTree.h"
//partial rebuild balance tree
//the poor scapegoat are responsible to rebuild
//the balance of the tree
//when d>log32q,find the scape goat that imblance the time and call him to
//fix it into a perfect balanced tree

template <class Node,class T> class ScapegoatTree
:public BinarySearchTree<Node,T> {
protected:
    using BinaryTree<Node>::nil;
    using BinaryTree<Node>::r;
    using BinarySearchTree<Node,T>::n; //number
    int q;//upper bound of the node q/2<=n<=q
    static int log32(int q);
    int addWithDepth(Node *u);
    void rebuild(Node *u);
    int packIntoArray(Node *u,Node** a,int i);
    Node* buildBalanced(Node **a,int i,int ns);

public:
    ScapegoatTree();
    virtual ~ScapegoatTree();
    virtual bool add(T x);
    virtual bool remove(T x);
};

//actual using class
template <class T> class ScapegoatTree1:public ScapegoatTree<BSTNode1<T>,T>{

};;

template<class Node, class T> inline
ScapegoatTree<Node,T>::ScapegoatTree() {
    // nothing to do
}



template<class Node, class T> inline
ScapegoatTree<Node,T>::~ScapegoatTree() {
    // nothing to do
}

template<class Node, class T>
inline int ScapegoatTree<Node,T>::log32(int q) {
    static double log23 = 2.4663034623764317;
    return (int)ceil(log23*log(q));
}


template <class Node,class T> inline void ScapegoatTree<Node,T>::rebuild(Node *u) {
    int ns=BinaryTree<Node>::size(u);
    Node *p=u->parent;
    Node **a=new Node*[ns];//store in increasing order
    packIntoArray(u,a,0);
    if(p==nil){
        r=buildBalanced(a,0,ns);
        r->parent=nil;
    }
    else if(p->right==u){
        p->right=buildBalanced(a,0,ns);
        p->right->parent=p;
    }
    else{
        p->left=buildBalanced(a,0,ns);
        p->left->parent=p;
    }
    delete[] a; //? release these pointer?
}

template <class Node,class T> inline int ScapegoatTree<Node,T>::packIntoArray(Node *u, Node **a, int i) {
    if(u==nil){
        return i;
    }
    //in order traversal example + divide and conqueuer example
    i=packIntoArray(u->left,a,i);
    a[i++]=u;
    return packIntoArray(u->right,a,i);
}


//like a quicksort!
//build a balanced tree using divide and conqueuer example
template <class Node,class T>  inline Node* ScapegoatTree<Node,T>::buildBalanced(Node **a, int i, int ns) {
    if(ns==0)
        return nil;
    int m=ns/2;//middle node
    a[i+m]->left=buildBalanced(a,i,m);
    if(a[i+m]->left!=nil)
        a[i+m]->left->parent=a[i+m];
    a[i+m]->right=buildBalanced(a,i+m+1,ns-m-1);
    if(a[i+m]->right!=nil)
        a[i+m]->right->parent=a[i+m];
    return a[i+m];
}
//add a Node with return depth of this node
template <class Node,class T> inline int ScapegoatTree<Node,T>::addWithDepth(Node *u) {
    Node *w=r;
    if(w==nil){
        r=u;
        n++;
        q++;
        return 0; //depth is 0
    }

    bool done=false;
    int d=0;//depth indicator
    do {
        int res = compare(u->x, w->x);
        if (res < 0) {
           if(w->left==nil){
               w->left=u;
               u->paremt=w;
               done=true;
        } else {
            w = w->left;
        }
        }else if(res>0){
            if (w->right == nil) {
                w->right = u;
                u->parent = w;
                done = true;
            }
            w = w->right;
        }
        else{
            return -1;
        }
        d++;
    }
    while(!done);
    n++;
    q++;
    return d;
}


template <class Node,class T> inline
bool ScapegoatTree<Node,T>::add(T x) {
    // first do basic insertion keeping track of depth
    Node *u = new Node;
    u->x = x;
    u->left = u->right = u->parent = nil;
    int d = addWithDepth(u);
    if(d>log32(q)){
        // depth exceeded, find scapegoat
        Node *w=u->parent;
        int a=BinaryTree<Node>::size(w);
        int b=BinaryTree<Node>::size(w->parent);
        while(3*a<=2*b){
            //while a<=2/3b,which mean we are quite good at a only have little part of thenode
            w=w->parent;
            a=BinaryTree<Node>::size(w);
            b=BinaryTree<Node>::size(w->parent);
        }
        rebuild(w->parent);//rebalance scape goat
    }
    else if(d<0){
        delete u;
        return false;
    }
    return true;
}


template <class Node,class T> bool ScapegoatTree<Node,T>::remove(T x) {
    if(BinarySearchTree<Node,T>::remove(x)){
        if(2*n<q){
            rebuild(r); //imediately rebuild all,very unifficent
            q=n;
        }
        return true;
    }
    return false;
}
#endif //DATASTRUCTURE_SCAPEGOATTREE_H
