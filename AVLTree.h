//
// Created by steafan on 2020/4/2.
//

#ifndef DATASTRUCTURE_AVLTREE_H
#define DATASTRUCTURE_AVLTREE_H

#include "BinarySearchTree.h"

template <class Node,class T> class AVLTree;

template <class Node,class T> class AVLNode:public BSTNode<Node,T>{

};

template <class Node,class T> class AVLTree: public BinarySearchTree<Node, T>{
protected:
    // I hate C++
    using BinaryTree<Node>::r;//root
    using BinaryTree<Node>::nil;//nil
    using BinarySearchTree<Node,T>::n;//size
    using BinarySearchTree<Node,T>::findLast;
    using BinarySearchTree<Node,T>::rotateLeft;
    using BinarySearchTree<Node,T>::rotateRight;
    using BinarySearchTree<Node,T>::splice;
    using BinarySearchTree<Node,T>::size;

public:
    AVLTree();
    virtual ~AVLTree();
    virtual bool add(T x);
    virtual bool remove(T x);
    void addFixup(Node* u);
    void removeFixup(Node* u);
    int BalanceFactor(Node* u);
};

template<class T>
class AVLNode1 : public AVLNode<AVLNode1<T>, T> { };

template<class T>
class AVLTree1 : public AVLTree<AVLNode1<T>, T> { };

template <class Node,class T> bool AVLTree<Node,T>::add(T x) {
    Node *u=new Node();
    u->left=u->right=u->parent=nil;
    u->x=x;
    bool added=BinarySearchTree::add(u);
    if(added)
        addFixup(u);
    else
        delete u;
    return added;
}

template <class Node,class T> bool AVLTree<Node,T>::remove(T x) {
    Node *u=findLast(x);
    Node *p=nil;
    if(u==nil || compare(u->x,x)!=0)
        return false;
    if(u->left==nil || u->right==nil){
        p=u->parent;
        splice(u);
        delete u;//delete u in 0 sprout and 1 sprout case
    }
    else{
        Node* w=u->right;
        while(w->left!=nil)//find the closest bigger value and replace u with that
            w=w->left;//gauranted to has almost 1 node child to use splice
        u->x=w->x;
        p=w->parent;
        splice(w);
        delete w;
    }
    removeFixup(p);
    return true;
}

template <class Node,class T> AVLTree::AVLTree(){

}

template <class Node,class T> AVLTree::~AVLTree() {

}

template <class Node,class T> int AVLTree::BalanceFactor(Node *u) {
    if(u==nil)
        return 0;
    else
        return height(u->left)-height(u->right);
}

template <class Node,class T> void AVLTree::addFixup(Node *u) {
    if(u==nil) {
        //add the only one node in the tree
        return;
    }
    Node* prev=nil;
    while(u!=nil){
         int factor=BalanceFactor(u);
         //retrive balance case like spray tree
         if(factor>1 && BalanceFactor(u->left)>0){ //LL
              rotateRight(u);
              u=u->parent;
         }
         else if(factor>1 && BalanceFactor(u->left)<=0){ //LR
              rotateLeft(u->left);
              rotateRight(u);
              u=u->parent;
         }
         else if(factor<-1 && BalanceFactor(u->right)<=0){ //RR
               rotateLeft(u);
               u=u->parent;
         }
         else if(factor<-1 && BalanceFactor(u->right)>0){ //RL
              rotateRight(u->right);
              rotateLeft(u);
              u=u->parent;
         }
         prev=u;
         u=u->parent;//move up
    }
    r=prev;
}


template <class Node,class T> void AVLTree<Node,T>::removeFixup(Node *u) {
    if(u==nil){
        //remove the only node
        return;
    }
    Node* prev=nil;
    while(u!=nil){
        int factor=BalanceFactor(u);
        if(factor>1 && BalanceFactor(u->left)>0){ //LL
            rotateRight(u);
            u=u->parent;
        }
        else if(factor>1 && BalanceFactor(u->left)<=0){ //LR
            rotateLeft(u->left);
            rotateRight(u);
            u=u->parent;
        }
        else if(factor<-1 && BalanceFactor(u->right)<=0){ //RR
            rotateLeft(u);
            u=u->parent;
        }
        else if(factor<-1 && BalanceFactor(u->right)>0){ //RL
            rotateRight(u->right);
            rotateLeft(u);
            u=u->parent;
        }
        prev=u;
        u=u->parent;//move up to upper layer to fix
    }
    r=prev;
}


#endif //DATASTRUCTURE_AVLTREE_H
