//
// Created by steaphan on 20/2/2020.
//

#ifndef DATASTRUCTURE_DLLIST_H
#define DATASTRUCTURE_DLLIST_H


//implement Double Linked List Interface

template <class T> class DLList{
protected:
    struct Node{
        T x;
        Node *prev,*next;
    };
    Node dummy;//dummy is the node that connect prev and next
    int n;
    void remove(Node* w);
    //private implementations
    Node* addBefore(Node* w,T x);
    Node* getNode(int i);

public:
    DLList();
    virtual ~DLList();
    int size(){ return n;}
    T get(int i);
    T set(int i,T X);
    virtual void add(int i,T x);
    virtual void add(T x){
        add(size(),x);
    }
    virtual void clear();
    virtual T remove(int i);
};

template <class T> DLList<T>::DLList() {
    //init the dummy node
    dummy.next=&dummy;//dummy.next with be start
    dummy.prev=&dummy;//dummy.prev with be the end
    n=0;
}

template <class T> typename DLList<T>::Node* DLList<T>::getNode(int i) {
    Node* p;
    if(i<n/2){
        p=dummy.next;
        for(int j=0;j<i;j++)
            p=p->next;
    }
    else{
        p=&dummy;
        for(int j=n;j>i;j--)
            p=p->prev;
    }
}


template <class T> T DLList<T>::get(int i) {
    return getNode(i)->x;
}

template <class T> T DLList<T>::set(int i, T x){
    Node* u=getNode(i);
    T y=u->x;
    u->x=x;
    return y;
}

//add before w
template <class T> typename DLList<T>::Node* DLList<T>::addBefore(DLList<T>::Node *w, T x) {
    Node* u=new Node;
    u->x=x;
    u->prev=w->prev;
    u->next=w;
    u->next->prev=u;
    u->prev->next=u;
    n++;
    return u;
}

template <class T> DLList<T>::~DLList() {
    clear();
}

template <class T> void DLList<T>::clear() {
    Node* u=dummy.next;
    while(u!=&dummy){
        Node* w=u->next;
        delete u;
        u=w;
    }
    n=0;
}


template <class T> void DLList<T>::remove(DLList<T>::Node *w) {
    w->prev->next=w->next;
    w->next->prev=w->prev;
    delete w;
    n--;
}


template <class T> T DLList<T>::remove(int i){
    Node* w=getNode(i);
    T x=w->x;
    remove(w);
    return x;
}

template <class T> void DLList<T>::add(int i, T x) {
    addBefore(getNode(i),x);
}

#endif //DATASTRUCTURE_DLLIST_H
