//
//  ArrayStack.hpp
//  datastructure
//
//  Created by steafan on 2020/2/15.
//  Copyright © 2020年 steaphan. All rights reserved.
//

#ifndef ArrayStack_hpp
#define ArrayStack_hpp
/*
 
 STD:: VECTOR implementation
*/
#include <stdio.h>
#include "utils.h"
#include "array.hpp"

template<class T>
class DualArrayDeque;

template <class T>
class ArrayStack {
protected:
    friend class DualArrayDeque<T>;
    array<T> a;
    int n;
    virtual void resize();//vector implementations
    
public:
    ArrayStack();
    virtual ~ArrayStack();
    int size();
    T get(int i);
    T set(int i,T x);
    virtual void add(int i, T x);
    virtual void add(T x){
        add(size(),x);
    }
    virtual T remove(int i);
    virtual void clear();
};

template<class T> inline int ArrayStack<T>::size(){
    return n;
}

template <class T> inline T ArrayStack<T>::get(int i){
    return a[i];
}

template <class T> inline T ArrayStack<T>::set(int i,T x){
    T y=a[i];
    a[i]=x;
    return y;
}

template <class T> void ArrayStack<T>::clear(){
    n=0;
    array<T> b(1);
    a=b;
}

template <class T> ArrayStack<T>::ArrayStack():a(1){
    n=0;
}

template<class T>
ArrayStack<T>::~ArrayStack() {
}

template <class T> void ArrayStack<T>::resize(){
    array<T> b(max(2*n,1));
    for(int i=0;i<n;i++){
        b[i]=a[i];
    }
    a=b; //our copy construtor behaviour,array is transfer
}

template <class T> void ArrayStack<T>::add(int i,T x){
    if(n+1>a.length)
        resize();
    for(int j=n;j>i;j--)
        a[j]=a[j-1]; //up one position for element >i
    a[i]=x;
    n++;
}


template <class T> T ArrayStack<T>::remove(int i){
    T x=a[i];
    for(int j=i;j<n-1;j++)
        a[j]=a[j+1];
    n--;
    if(a.length>=3*n)
        resize();
    return x;
}


#endif /* ArrayStack_hpp */
