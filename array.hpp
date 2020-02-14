//
//  array.hpp
//  datastructure
//
//  Created by steafan on 2020/2/14.
//  Copyright © 2020年 steaphan. All rights reserved.
//

#ifndef array_hpp
#define array_hpp
#include <iostream>
#include <algorithm>

#include <stdlib.h>
#include <assert.h>

template<class T> class array{
protected:
    T* a;
public:
    int length;
    array(int len);
    array(int len,T init);
    void fill(T x);
    virtual ~array();
    
    array<T>& operator=(array<T> &b){
        if(a!=NULL)
            delete[] a;
        a=b.a;
        b.a=NULL;
        length=b.length;
        return *this;
    }
    
    T& operator[](int i){
        assert(i>=0 && i<length);
        return a[i];
    }
    
    void swap(int i,int j){
        T x=a[i];
        a[i]=a[j];
        a[j]=x;
    }
    
    static void copyOfRange(array<T> &a0,array<T> &a, int i,int j);
    virtual void reverse();
};


template<class T> array<T>::array(int len){
    length=len;
    a=new T[length];
    
}

template<class T> array<T>::array(int len,T init){
    length=len;
    a=new T[length];
    for(int i=0;i<length;i++)
        a[i]= init;
}

template<class T> array<T>::~array(){
    if(a!=NULL)
        delete[] a;
}

template<class T> void array<T>::reverse(){
    for(int i=0;i<length/2;i++){
        swap(i,length-i-1);
    }
}

template <class T> void array<T>::copyOfRange(array<T> &a0, array<T> &a, int i, int j){
    //copy value from a to a0
    array<T> b(j-1);
    std::copy(a.a,a.a+j-i,b.a);
    a0=b;
}


template<class T> void array<T>::fill(T x){
    std::fill(a,a+length,x);
}

#endif /* array_hpp */
