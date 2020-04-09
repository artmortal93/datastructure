//
// Created by steafan on 2020/4/8.
//

#ifndef DATASTRUCTURE_BINARYHEAP_H
#define DATASTRUCTURE_BINARYHEAP_H

#include <cstring>
#include "utils.h"
#include "array.hpp"
///implementation of min heap,son is always bigger than parrent
/// properity queue
template <class T> class BinaryHeap{
protected:
    array<T> a;
    int n;
    void resize();
    void bubbleUp(int i);
    void trickleDown(int i);
    static int left(int i){
        return 2*i+1;
    }
    static int right(int i){
        return 2*i+2;
    }
    static int parent(int i){
        return (i-1)/2;
    }

public:
    BinaryHeap();
    BinaryHeap(array<T>& b);
    virtual  ~BinaryHeap();
    bool add(T x);
    T findMin(){
        return a[0]; //minimum heap
    }
    T remove();
    void clear();
    int size(){
        return n;
    }
    static void sort(array<T> &b);//heapsort

};

template <class T> void BinaryHeap<T>::resize() {
    array<T> b(max(2*n,1));
    array<T>::copyOfRange(b,a,0,n);
    a=b;
}
/// in heap , this bubble up and tickle down operation is similliar to rotation, but much simplier
template <class T> bool BinaryHeap<T>::add(T x) {
    if(n+1>a.length)
        resize();
    a[n++]=x;
    bubbleUp(n-1);//bubble up and swap until meet the min-heap crietria
    return true;
}

template <class T> void BinaryHeap<T>::bubbleUp(int i) {
    int p=parent(i);
    while(i>0 && compare(a[i],a[p])<0) //swap until to the root 0 >0
    {
        a.swap(i,p);
        i=p;
        p=parent(i);
    }
}

template <class T> T BinaryHeap<T>::remove() {
    T x=a[0]; //take out the urgent number, the value smallest the priority is higher
    a[0] =a[--n];//swap big value
    trickleDown(0);//fix up
    if(3*n<a.length)
        resize();
    return x;
}


template<class T>
BinaryHeap<T>::BinaryHeap() : a(1) {
    n = 0;
}
template <class T> void BinaryHeap<T>::sort(array<T> &b) {
    BinaryHeap<T> h(b);
    while(h.n>1){
        h.a.swap(--h.n,0); //keep in mind that h[0] is always smallest
        h.trickleDown(0);
    }
    b=h.a;
    b.reverse();
}


template <class T> BinaryHeap<T>::BinaryHeap(array<T> &b):a(0){
    a=b;
    n=a.length;
    for(int i=n/2-1;i>=0;i--){
        trickleDown(i); //resort the order from bottom(2nd layer) to top
    }
}


template<class T>
BinaryHeap<T>::~BinaryHeap() {
    // nothing to do
}




template<class T>
void BinaryHeap<T>::clear() {
}

template <class T> void BinaryHeap<T>::trickleDown(int i) {
    do{
        int j=-1;//next value, also determinate should go down or not
        int r=right(i);
        if(r<n && compare(a[r],a[i])<0){//case: both have left child and right child
            int l=left(i);
            if(compare(a[l],a[r])<0){
                j=l;
            }
            else{
                j=r;
            }
        }
        else{ //case only have left child
            int l=left(i);
            if(l<n && compare(a[l],a[i])<0){
                j=l;
            }
        }
        if(j>=0)
            a.swap(i,j);
        i=j;
    }
    while(i>=0);
}

#endif //DATASTRUCTURE_BINARYHEAP_H
