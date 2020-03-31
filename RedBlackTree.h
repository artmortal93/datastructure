//
// Created by steaphan on 6/3/2020.
//

#ifndef DATASTRUCTURE_REDBLACKTREE_H
#define DATASTRUCTURE_REDBLACKTREE_H
#include "BinarySearchTree.h"

template<class Node, class T> class RedBlackTree;

///left leaning red-black tree
///left leaning simplify the case of 3 nodes in 2-3-4 tree, only possibly when left red
/// and right black
/// black node parent== case2
/// red node parent with black uncle==case3
/// red node parent with red uncle ==case 4
template<class Node, class T>
class RedBlackNode : public BSTNode<Node, T> {
protected:
    friend class RedBlackTree<Node, T>;
    char colour;
};


template<class Node, class T>
class RedBlackTree : public BinarySearchTree<Node, T> {
protected:
    // I hate C++
    using BinaryTree<Node>::r;//root
    using BinaryTree<Node>::nil;//nil
    using BinarySearchTree<Node,T>::n;//size
    using BinarySearchTree<Node,T>::findLast;
    using BinarySearchTree<Node,T>::rotateLeft;
    using BinarySearchTree<Node,T>::rotateRight;
    using BinarySearchTree<Node,T>::splice;

    static const int red = 0;
    static const int black = 1;
    void pushBlack(Node *u);
    void pullBlack(Node *u);
    void flipLeft(Node *u);
    void flipRight(Node *u);
    void swapcolours(Node *u, Node *w);
    void addFixup(Node *u);
    void removeFixup(Node *u);
    Node *removeFixupCase1(Node *u);
    Node *removeFixupCase2(Node *u);
    Node *removeFixupCase3(Node *u);
    void verify();
    int verify(Node *u);
public:
    RedBlackTree();
    virtual ~RedBlackTree();
    virtual bool add(T x);
    virtual bool remove(T x);
};


template<class T>
class RedBlackNode1 : public RedBlackNode<RedBlackNode1<T>, T> { };

template<class T>
class RedBlackTree1 : public RedBlackTree<RedBlackNode1<T>, T> { };

//node black to red
///change the color in case 4 without violating black height(down black)
template <class Node,class T> void RedBlackTree<Node,T>::pushBlack(Node *u) {
    u->colour--; //red 0 black 1 turn black into red
    u->left->colour++;
    u->right->colour++; //two sub node from red to black
}

//oposite operation node red to black(up black)
template <class Node ,class T> void RedBlackTree<Node,T>::pullBlack(Node* u){
    u->colour++; //red 0 black 1 turn black into red
    u->left->colour--;
    u->right->colour--;
}

///use for 2-3-4 tree 3 node case
///change all two possible situation in 3-node case into black left lean situation
//effect:change color from left child to right child
        ///both operation keep black height propertyq
template <class Node,class T> void RedBlackTree<Node,T>::flipLeft(Node *u) {
    swapcolours(u,u->right);
    rotateLeft(u);
    //this solution is right,check the diagram of figure 9.7 or simply imagine
}

///opposite operation
/// /////effect:change color from right child to left child
template <class Node,class T> void RedBlackTree<Node,T>::flipRight(Node *u) {
    swapcolours(u,u->left);
    rotateRight(u);
}

template <class Node,class T> void RedBlackTree<Node,T>::swapcolours(Node *u, Node *w) {
    char tmp = u->colour;
    u->colour = w->colour;
    w->colour = tmp;
}


template <class Node,class T> bool RedBlackTree<Node,T>::add(T x) {
     Node *u=new Node();
     u->left=u->right=u->parent=nil;
     u->x=x;
     u->colour=red;
     bool added=BinarySearchTree::add(u);
     if(added)
         addFixup(u);
     else
         delete u;
     return added;
}


template <class Node,class T> void RedBlackTree<Node,T>::addFixup(Node *u) {
    ///only two prop could be violate:
    /// red edge connect prop and left lean prop
    ///
    while(u->colour==red){
        ///only 3,4 node case should be considered
        if(u==r){
            u->colour=black;
            return ;
        }
    }
}

#endif //DATASTRUCTURE_REDBLACKTREE_H
