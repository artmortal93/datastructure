//
// Created by steaphan on 26/2/2020.
//

#ifndef DATASTRUCTURE_SKIPLISTSSET_H
#define DATASTRUCTURE_SKIPLISTSSET_H


#include <cstdlib>
#include <cstring>

#include "utils.h"

/*
 * maximum height is 32's skiplist
 */

template  <class T> class SkiplistSSet{
protected:
    T null;
    struct  Node{
        T x;
        int height;//;length of next node's high
        Node* next[];
    };

    Node *sentinel;
    int h;//total high;
    int n;
    Node** stack;// stack of sentinel path finder

    Node *newNode(T x,int h); //create a new node with height h
    void deleteNode(Node* u);
    Node* findPredNode(T x);

public:

    SkiplistSSet();
    virtual ~SkiplistSSet();

    T find(T x);
    bool remove(T x);
    bool add(T x);
    int pickHeight();
    void clear();
    int size(){ return n;}
};


template <class T> SkiplistSSet<T>::SkiplistSSet() {
    null=(T)NULL;
    n=0;
    sentinel=newNode(null, sizeof(int)*8);//default expandable height is 32 for next*
    memset(sentinel->next,'\0', sizeof(Node*)*sentinel->height);//32 slot with null
    stack=(Node**)new Node*[sentinel->height];
    h=0;
}


template <class T> SkiplistSSet<T>::~SkiplistSSet() {
    clear();
    deleteNode(sentinel);
    delete[] stack;
}

template <class T> typename SkiplistSSet<T>::Node* SkiplistSSet<T>::newNode(T x, int h) {
    Node* u=(Node*)malloc(sizeof(Node)+(h+1)*sizeof(Node*));//0 is original height
    // struct only cares about memory layout, init as null
    u->x=x;
    u->height=h;
    return u;
}

template <class T> void SkiplistSSet<T>::deleteNode(SkiplistSSet<T>::Node *u) {
    free(u);
}

template <class T> typename SkiplistSSet<T>::Node* SkiplistSSet<T>::findPredNode(T x) {
    Node* u=sentinel;
    int r=h;
    while(r>=0){
        while(u->next[r] !=NULL //? out of border issue or same height structure
        &&
        compare(u->next[r]->x,x)<0 //not finding =0 but finding prev one ,which is -1
        )
            u=u->next[r]; ///go right in list r in height
        r--;
    }
    return u;
}

template <class T> T SkiplistSSet<T>::find(T x) {
    Node* u=findPredNode(x);
    return u->next[0]==NULL?null:u->next[0]->x;
}


//randomnize a node's height as 32
template <class T> int SkiplistSSet<T>::pickHeight() {
    int z=rand();
    int k=0;
    int m=1;
    while((z&m)!=0){
        k++;
        m<<=1;
    }
    return k;
}

//
// record path of the prev node
//if height is achieve new high score
//append the new node accordingly
//but it never achieve 32
template <class T> bool SkiplistSSet<T>::add(T x){
    Node* u=sentinel;
    int r=h;//initial height
    int comp=0;
    //find the prev node in 0 layer
    while(r>=0){
         while(u->next[r]!=NULL
          && (comp = compare(u->next[r]->x, x)) < 0)
             u=u->next[r];
         if(u->next[r]!=NULL && comp==0) //find prev node find the already have one set element
             return false;
         stack[r--]=u; //going down store u,u[0] is the prev node
    }
    //track h paths

    Node* w=newNode(x,pickHeight());//1-32
    while(h<w->height)
        stack[++h]=sentinel; //height increased for stack,and height has been adjusted to new high score

    for(int i=0;i<=w->height;i++){
        w->next[i]=stack[i]->next[i];
        stack[i]->next[i]=w;//stack stores "before" nodes
    }

    n++;
    return true;
}

template <class T> bool SkiplistSSet<T>::remove(T x) {
    bool removed=false;
    Node* u=sentinel,*del;
    int r=h;
    int comp=0;
    while(r>=0){
        while(u->next[r]!=NULL && (comp=compare(u->next[r]->x,x))<0){
            u=u->next[r];
        }
        //search the path but do not need to record the path
        if(u->next[r]!=NULL && comp==0){
            removed=true;
            del=u->next[r];//set the del but not remove yet
            //remove in corresponding layer
            u->next[r]=u->next[r]->next[r];
            if(u==sentinel && u->next[r]==NULL)
                h--;//skiplist has gone down
        }
        r--;
    }

    if(removed){
        delete del;
        n--;
    }
    return removed;
}


template <class T> void SkiplistSSet<T>::clear() {
    Node* u=sentinel->next[0];
    while(u!=NULL){
        Node* n=u->next[0];
        deleteNode(u);
        u=n;
    }
    memset(sentinel->next,'\0',sizeof(Node*)*h);
    h=0;
    n=0;
}


#endif //DATASTRUCTURE_SKIPLISTSSET_H
