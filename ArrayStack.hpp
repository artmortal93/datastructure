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
protectd:
    friend class DualArrayDeque<T>;
    array<T> a;
    int n;
    virtual void resize();//vector implementations
    
public:
    ArrayStack()
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


#endif /* ArrayStack_hpp */
