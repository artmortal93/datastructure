//
// Created by steaphan on 20/2/2020.
//

#ifndef DATASTRUCTURE_SELIST_H
#define DATASTRUCTURE_SELIST_H

#include "ArrayDeque.h"
#include "array.hpp"
//space efficent linkedlist
// block deque as the linkedlist node

template <class T> class SEList{

protected:
    int n;
    int b; //paramaterized block size
    class BDeque:public ArrayDeque<T>{
        using ArrayDeque<T>::a;
        using ArrayDeque<T>::j; //start pointer
        using ArrayDeque<T>::n; //n elements
    public:
        //b block element could capcity b+1 elements
        BDeque(int b){
            n=0;
            j=0;
            array<int> z(b+1);
            a=z;
        }

        virtual ~BDeque(){

        }
        //why is this necessary(?) c++
        //Answer:?
        //Could not add
        virtual void add(int i, T x){
            ArrayDeque<T>::add(i,x);
        }

        virtual bool add(T x){
            ArrayDeque<T>::add(ArrayDeque<T>::size(),x);
            return true;
        }
        void resize(){}//override to empty implementation, could not resize like a vector
    };

    class Node{
    public:
        BDeque d;
        Node *prev, *next;
        Node(int b):d(b){}
    };

    Node dummy;
    //easy data structure to store the location
    class Location{
    public:
        Node* u;
        int j;
        Location(){}
        Location(Node* u, int j){
            this->u=u;
            this->j=j;
        }
    };
    //add before w
    //reutrn the add-before node
    Node* addBefore(Node* w){
        Node* u=new Node(b);
        u->prev=w->prev;
        u->next=w;
        u->next->prev=u;
        u->prev->next=u;
        return u;
    }

    void remove(Node* w){
        w->prev->next=w->next;
        w->next->prev=w->prev;
        delete w;
    }


    void getLocation(int i,Location& ell){
        if(i<n/2){
            Node* u=dummy.next;
            while (i >= u->d.size()){
                i-= u->d.size();
                u=u->next;
            }
            ell.u=u;
            ell.j=i;
        }
        else{
            Node* u=&dummy;
            int idx=n;
            while (i<idx){
                u=u->prev;
                idx-=u->d.size();
            }
            ell.u=u;
            ell.j=i-idx;
        }
    }


public:
    SEList(int b):dummy(b){
        this->b=b;
        dummy.next=&dummy;
        dummy.prev=&dummy;
        n=0;
    }

    virtual ~SEList(){
        clear();
    }

    virtual void clear(){
        Node *u=dummy.next;
        while(u!=&dummy){
            Node *w=u->next;
            delete u;
            u=w;
        }
        n=0;
    }

    T get(int i){
        Location l;
        getLocation(i,l);
        return l.u->d.get(l.j);
    }

    T set(int i,T x){
        Location l;
        getLocation(i,l);
        T y=l.u->d.get(l.j);
        l.u->d.set(l.j,x);
        return y;
    }

    int size(){
        return n;
    }

    void add(T x){
        Node* last=dummy.prev;
        if(last==&dummy || last->d.size()==b+1){
            last=addBefore(&dummy);
        }
        last->d.add(x);
        n++;
    }

    /**
 * Call this function on a node u such that u and its b-1 successors
 * all contain b+1 items.  This adds a new node so that u and its
 * b successors each contain b items
 */
    void spread(Node* u){
        Node *w=u;
        for(int j=0;j<b;j++){
            w=w->next;
        }

        w=addBefore(w); //get last node

        while(w!=u){
            while(w->d.size()<b)
                w->d.add(0,w->prev->d.remove(w->prev->d.size()-1));
            w=w->prev;
        }

    }

    //space efficent add
    void add(int i,T x){
         if(i==n)
         {
             add(x);
             return;
         }

         Location l;
         getLocation(i,l);
         Node* u=l.u;
         int r=0;
         while(r<b && u!=&dummy && u->d.size()==b+1){
             u=u->next;
             r++;
         }
         if(r==b){
             spread(l.u);
             u=l.u;
             //now u is the original node,and left one place
         }
         if(u==&dummy){
             u=addBefore(u);
             //u is the last node
         }
         while(u!=l.u){
             //shift one element
             u->d.add(0,u->prev->d.remove(u->prev->d.size()-1));
             u=u->prev;
         }
         u->d.add(l.j,x);
         n++;
    }

    /**
	 * Call this function on a node u such that u and its b-1 successors
	 * all contain b-1 items.  This removes a node so that u and its
	 * b-2 successors each contain b items
	 */
    void gather(Node* u){
       Node *w=u;
       //discard a b-1 block
       for(int j=0;j<b-1;j++){
           while(w->d.size()<b)
               w->d.add(w->next->d.remove(0));
           w=w->next;
       }
       remove(w);
    }

    T remove(int i){
       Location l;
       getLocation(i,l);
       T y=l.u->d.get(l.j);
       Node *u=l.u;
       int r=0;
       while(r<b && u!=&dummy && u->d.size() == b-1){
           u=u->next;
           r++;
       }

       if(r==b)
           gather(l.u);

       u=l.u;
       u->d.remove(l.j);
       while(u->d.size() <b-1 && u->next!=&dummy){
           u->d.add(u->next->d.remove(0));
           u=u->next;
       }
       if(u->d.size()==0)
           remove(u);
       n--;
       return y;
    }
};

#endif //DATASTRUCTURE_SELIST_H
