//
// Created by steaphan on 20/2/2020.
//

#ifndef DATASTRUCTURE_SLLIST_H
#define DATASTRUCTURE_SLLIST_H

#include "stdlib.h"
//#define NULL nullptr
template <class T> class SLList{
    T null; //a represent emptyptr maybe used for recyclic SLList

protected:
    class Node{
    public:
        T x;
        Node *next;
        explicit Node(T x0){
            x=x0;
            next=NULL;
        }
    };
    //implement double pointer-style linked list
    Node *head;
    Node *tail;
    int n;

public:
    SLList(){
        null=(T)NULL; //?
        n=0;
        head=tail=NULL;
    }

    virtual ~SLList(){
        Node *u=head;
        while(u!=NULL){
            Node *w=u;
            u=u->next;
            delete w;
        }
    }

    int size(){
        return n;
    }

    T push(T x){
        Node *u=new Node(x);
        u->next=head;
        head=u;
        if(n==0)
            tail=u;
        n++;
        return x;
    }

    T pop(){
        if(n==0)
            return null;//return a value represent NULL

        T x=head->x;
        Node* u=head;
        head=head->next;
        delete u;
        if(--n==0)
            tail=NULL;
        return x;
    }
    //add in bottom, queue interface
    bool add(T x){
        Node* u=new Node(x);
        if(n==0)
        {
            head=u;
        }
        else{
            tail->next=u;
        }
        tail=u;
        n++;
        return true;
    }

    T remove(){
        if(n==0)
            return null;

        T x=head->x;
        Node *u=head;
        head=head->next;
        delete u;
        if(--n==0)
            tail=NULL;
        return x;
    }

    T peek(){
        return head->x;//NOT SAFE function
    }





};

//single linked LIst

#endif //DATASTRUCTURE_SLLIST_H
