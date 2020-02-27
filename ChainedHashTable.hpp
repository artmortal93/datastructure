//
//  ChainedHashTable.hpp
//  datastructure
//
//  Created by steafan on 2020/2/27.
//  Copyright © 2020年 steaphan. All rights reserved.
//

#ifndef ChainedHashTable_hpp
#define ChainedHashTable_hpp

#include <stdio.h>
#include "utils.h"
#include <climits>
#include "array.hpp"
#include "ArrayStack.hpp"

template <class T>
class ChainedHashTable {
protected:
    typedef ArrayStack<T>  List;
    T null;
    array<List> t;
    int n;//ele size
    int d;//dimension of the integer 2^^d buckets
    int z;//a random seed
    static const int w=32;
    void resize();
    int hash(T x){
        return ((unsigned)(z*hashCode(x)))>>(w-d);//chang byte representation
    }
public:
    ChainedHashTable();
    virtual ~ChainedHashTable();
    bool add(T x);
    T remove(T x);
    T find(T x);
    int size() {
        return n;
    }
    void clear();
};


template <class T>
void ChainedHashTable<T>::resize() {
    d=1; //resize d to shrink to almost fit
    while(1<<d <=n)
        d++;
    
    array<List> newTable(1<<d);
    for(int i=0;i<t.length;i++){
        for(int j=0;j<t[i].size();j++){
            T x=t[i].get(j);
            newTable[hash(x)].add(x);
        }
    }
    t=newTable;
    
}

template <class T> ChainedHashTable<T>::ChainedHashTable():t(2){
    n=0;
    d=1;
    null=INT_MIN;
    z=rand()|1;
    
}

template <class T> bool ChainedHashTable<T>::add(T x){
    if(find(x)!=null)
        return false;
    if(n+1>t.length)
        resize(); //when it reach one for each bucket
    t[hash(x)].add(x);
    n++;
    return true;
}

template <class T> T ChainedHashTable<T>::remove(T x){
    int j=hash(x);
    for(int i=0;i<t[j].size();i++){
        T y=t[j].get(i);
        if(x==y){
            t[j].remove(i);
            n--;
            return y;
            
        }
    }
    return null;
}

template <class T>
T ChainedHashTable<T>::find(T x){
    int j=hash(x);
    for(int i=0;i<t[j].size();i++){
        if(x==t[j].get(i))
            return t[j].get(i);
    }
    return null;
}


template <class T> void ChainedHashTable<T>::clear(){
    n=0;
    d=1;
    array<List> b(2);
    t=b;
}

#endif /* ChainedHashTable_hpp */
