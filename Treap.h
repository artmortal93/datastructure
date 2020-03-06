//
// Created by steaphan on 29/2/2020.
//

#ifndef DATASTRUCTURE_TREAP_H
#define DATASTRUCTURE_TREAP_H


#include <climits>

#include "BinarySearchTree.h"
template<class Node, class T> class Treap;
//THe Node parameter should be subclass of BSTNode<T>
//example
//template class BTNode2<BTNode2,int>
template<class Node, class T>
class TreapNode : public BSTNode<Node, T> {
protected:
    friend class Treap<Node,T>;
    int p;//?
};

template<class Node, class T>
class Treap : public BinarySearchTree<Node, T> {
protected:
    using BinaryTree<Node>::r;
    using BinaryTree<Node>::nil;
    using BinarySearchTree<Node,T>::null;
    using BinarySearchTree<Node,T>::n;
    using BinarySearchTree<Node,T>::findLast;
    using BinarySearchTree<Node,T>::rotateLeft;
    using BinarySearchTree<Node,T>::rotateRight;
    using BinarySearchTree<Node,T>::splice;

    void bubbleUp(Node *u);
    void trickleDown(Node *u);
public:
    Treap();
    explicit Treap(T null);
    virtual ~Treap();
    virtual bool add(T x);
    virtual bool remove(T x);
    virtual Treap<Node,T>* split(T x);//?
    virtual void absorb(Treap<Node,T> &t);//?
};

template<class T>
class TreapNode1 : public TreapNode<TreapNode1, T> { };

template<class T>
class Treap1 : public Treap<TreapNode1<T>, T> { };

template<class Node, class T>
Treap<Node, T>::Treap() {
    // nothing to do
}

template<class Node, class T>
Treap<Node, T>::Treap(T null) : BinarySearchTree<Node,T>(null) {
    // nothing to do
}

template<class Node, class T>
Treap<Node, T>::~Treap() {
    // nothing to do
}

template <class Node,class T> bool Treap<Node,T>::add(T x){
    Node*u=new Node;
    u->x=x;
    u->p=rand();
    if(BinarySearchTree<Node,T>::add(u)){
        bubbleUp(u); //as it is leaf node, fix the property of probabilty violation from down to top
        return true;
    }
    delete u;
    return false;
};

//fix the probabilty voialaiton to parents using rotation
template <class Node,class T> void Treap<Node,T>::bubbleUp(Node *u) {
    while(u->parent!=nil && u->parent->p >u->p){
        if(u->parent->right ==u)
            rotateLeft(u->parent);
        else
            rotateRight(u->parent);//up one position
    }
    if(u->parent ==nil)
        r=u;
}

template <class Node,class T> bool Treap<Node,T>::remove(T x) {
    Node *u=findLast(x);
    if(u!=nil && compare(u->x,x)==0){
        trickleDown(u); //rotate down to leaf
        split(u);
        delete u;
        return true;
    }
    return false;
}

//proagate the violation edge to left node ,only one edge exist wrong at the same time
//initially no wrong in the graph
template <class Node,class T> void
        Treap<Node,T>::trickleDown(Node *u) {
    //become leaf node to be end of the violation
    while(u->left!=nil || u->right!=nil){
        if(u->left=nil)
            rotateLeft(u);
        else if(u->right==nil)
            rotateRight(u);
        else if(u->left->p < u->right->p){
            rotateRight(u);
        }
        else{
            rotateLeft(u);
        }
        if(r==u)
            r=u->parent;//reassign root if u is root cause r is level down
    }
}


template <class Node,class T> Treap<Node,T>* Treap<Node,T>::split(T x) {
    ///split the tree using T,T will be new root
    Node* u=findLast(x);
    Node* s=new Node();//find the parent node or T Node,note that we need to start at leaf,but T is not neccasry at leaf,so we need to add a imagine value and rotate up
    if(u->right ==nil){
        u->right=s;
    }
    else{
        //important
        //it dont contains any value,should we put this imagine node TO WHATEVER >=t,show that the T ,not matter we found it or not
        //it's always
        //case left node is nil
        u = u->right;
        while (u->left != nil)
            u = u->left;
        u->left = s;
    }
    //reminding the s do not contain any value T x!! so it do not violate the bst
    s->parent=u;
    s->p=INT_MIN;//generate manual violation all to the root cause we are defintely smallest
    bubbleUp(s);
    this->r=s->right;//split this tree is the right one?
    if(this->r!=nil)
        this->r->parent=nil;
    n=INT_MIN;
    Treap<Node,T> *ret=new Treap<Node,T>(null);
    ret->r=s->left;//ret is the left one
    if (ret->r != nil) ret->r->parent = nil;
    n = INT_MIN;
    return ret;
}

/**
 * Absorb the elements of treap t, which should all be smaller than
 * all the elements in this
 * @param t
 * @return
 */
template<class Node, class T>
void Treap<Node,T>::absorb(Treap<Node,T> &t) {
    Node* s = new Node();//a node with value 0 prob 0,suitable for node t
    s->right = this->r;
    if (this->r != nil) this->r->parent = s;
    s->left = t.r;
    if (t.r != nil) t.r->parent = s;
    this->r = s;
    t.r = nil;//discard tree t,not necessary
    trickleDown(s);//trickle down a non-value node into edfes
    splice(s);
}

#endif //DATASTRUCTURE_TREAP_H
