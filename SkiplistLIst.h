//
// Created by steaphan on 26/2/2020.
//

#ifndef DATASTRUCTURE_SKIPLISTLIST_H
#define DATASTRUCTURE_SKIPLISTLIST_H

#include "utils.h"
#include <cstdlib>
#include <cstring>


template <class T> class SkiplistList{
protected:
    T null;
    struct  Node{
        T x;
        int height;//;length of next node's high
        int *length;//length parameter array, array size is as long as Node's height
        Node** next;
    };

    Node *sentinel;
    int h;//total high;
    int n;

    Node* newNode(T x,int h){
        Node* u=new Node;
        u->x=x;
        u->height=h;
        u->length=new int[h+1];
        u->next=new Node*[h+1];
        return u;
    }

    void deleteNode(Node* u){
        delete [] u->length;
        delete [] u->next;
        delete u;
    }

    Node* findPred(int i){
        Node* u=sentinel;
        int r=h;
        int j=-1;//the index of the current node in list 0 (because we start at sentinel
        while(r>=0){
            while(u->next[r]!=NULL && j+u->length[r]<i){
                j+= u->length[r]; //find tbe pred node
                u=u->next[r];
            }
            r--;
        }
        return u;
    }

    Node* add(int i,Node *w){
        Node *u=sentinel;
        int k=w->height;
        int r=h;//height
        int j=-1;//index of u

        while(r>=0){
            while (u->next[r]!=NULL && j+u->length[r]<i){
                j+=u->length[r];
                u=u->next[r];
            }
            u->length[r]++; //the pred node's length in r's path add one
            if(r<=k){
                //if current level fits the node's height
                w->next[r]=u->next[r];
                u->next[r]=w;
                w->length[r]=u->length[r]-(i-j);//update this layer's length
                u->length[r]=i-j;//update this layer's length
            }
            r--;
        }
        n++;
        return u;

    }


    int pickHeight() {
        int z = rand();
        int k = 0;
        int m = 1;
        while ((z & m) != 0) {
            k++;
            m <<= 1;
        }
        return k;
    }


public:
    SkiplistList();
    virtual ~SkiplistList();

    int size() {
        return n;
    }
    T get(int i) {
        return findPred(i)->next[0]->x;
    }

    T set(int i, T x) {
        Node *u = findPred(i)->next[0];
        T y = u->x;
        u->x = x;
        return y;
    }


    void add(int i,T x){
        Node* w=newNode(x,pickHeight());
        if(w->height>h)
            h=w->height;
        add(i,w);
    }


    T remove(int i){
        T x=null;
        Node *u=sentinel,*del;
        int r=h;
        int j=-1;
        while(r>=0){
            //prev node u
            while(u->next[r]!=NULL && j+u->length[r]<i){
                  j+=u->length[r];
                  u=u->next[r];
            }
            u->length[r]--;// for the node we are removing ,-1 length for prev node
            if(j+u->length[r]+1==i && u->next[r]!=NULL){
                //if the node exist in this level
                x=u->next[r]->x;
                u->length[r]+=u->next[r]->length[r];
                del=u->next[r];//record this del node
                u->next[r]=u->next[r]->next[r];
                if(u==sentinel && u->next[r]==NULL)
                    h--; //if no node left
            }
         r--;
        }
        deleteNode(del);
        n--;
        return x;
    }

    void clear(){
        Node* u=sentinel->next[0];
        while(u!= NULL){
            Node *n=u->next[0];
            deleteNode(u);
            u=n;
        }
        memset(sentinel->next,'\0', sizeof(Node*)*h);
        h=0;
        n=0;
    }

};


template <class T> SkiplistList<T>::SkiplistList() {
    null=(T)NULL;
    n = 0;
    sentinel = newNode(null, sizeof(int)*8);
    memset(sentinel->next, '\0', sizeof(Node*)*sentinel->height);
    h = 0;
}



template <class T> SkiplistList<T>::~SkiplistList() {
    clear();
    deleteNode(sentinel);
}


#endif //DATASTRUCTURE_SKIPLISTLIST_H
