//
// Created by steaphan on 17/2/2020.
//

#ifndef DATASTRUCTURE_ARRAYQUEUE_H
#define DATASTRUCTURE_ARRAYQUEUE_H

#include "array.hpp"
#include "utils.h"
//single pointer implementation to track the start and end of the queue
template <class T> class ArrayQueue{
protected:
    array<T> a;
    int j;//start of the pointer
    int n;//elem number
    void resize();

public:
    ArrayQueue();
    virtual ~ArrayQueue();
    virtual bool add(T x);
    virtual T remove();
    int size();
};

template <class T> ArrayQueue<T>::ArrayQueue() :a(1){
    n=0;
    j=0;
}

template <class T> ArrayQueue<T>::~ArrayQueue() {

}

template <class T> void ArrayQueue<T>::resize() {
    array<T> b(max(1,2*n));
    for(int k=0;k<n;k++){
        b[k]=a[(j+k)%a.length];
    }
    a=b;
    j=0;
}

template <class T> bool ArrayQueue<T>::add(T x) {
    if(n+1 > a.length)
        resize();
    a[(j+n)%a.length]=x;
    n++;
    return true;
}
template <class T> T ArrayQueue<T>::remove() {
    T x=a[j];
    j=(j+1)%a.length;
    n--;
    if(a.length>=3*n)
        resize();
    return x;
}

template <class T> int ArrayQueue<T>::size() {
    return n;
}


#endif //DATASTRUCTURE_ARRAYQUEUE_H
