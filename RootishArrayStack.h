//
// Created by steaphan on 17/2/2020.
//

#ifndef DATASTRUCTURE_ROOTISHARRAYSTACK_H
#define DATASTRUCTURE_ROOTISHARRAYSTACK_H

#include "ArrayStack.hpp"
#include <math.h>

//vector with a 1,2,3,4,5 style array block
//efficency in space preseveration
template <class T> class RootishArrayStack{
protected:
     ArrayStack<T*> blocks;
     int n;
     int i2b(int i);
     void grow();
     void shrink();

public:
    RootishArrayStack();
    virtual  ~RootishArrayStack();
    int size();
    T get(int i);
    T set(int i,T x);
    virtual void add(int i,T x);
    virtual T remove(int i);
    virtual void clear();
};

template <class T> inline int RootishArrayStack<T>::size() {
    return n;
}

template <class T> inline T RootishArrayStack<T>::get(int i) {
    int b=i2b(i);
    int j=i-b*(b+1)/2;
    return blocks.get(b)[j];
}

template <class T> inline T RootishArrayStack<T>::set(int i, T x) {
    int b=i2b(i);
    int j=i-b*(b+1)/2;
    T y=blocks.get(b)[j];
    blocks.get(b)[j]=x;
    return y;
}

template<class T> inline
int RootishArrayStack<T>::i2b(int i) {
    double db = (-3.0 + sqrt(9 + 8*i)) / 2.0;
    int b = (int)ceil(db);
    return b;
}

template<class T>
RootishArrayStack<T>::RootishArrayStack() {
    n = 0;
}

template<class T>
RootishArrayStack<T>::~RootishArrayStack() {

}


template <class T> void RootishArrayStack<T>::add(int i,T x){
    int r=blocks.size();
    if(r*(r+1)/2<n+1)
        grow();
    n++;
    for(int j=n-1;j>i;j--)
        set(j,get(j-1));
    set(i,x);
}

template <class T> T RootishArrayStack<T>::remove(int i) {
    T x=get(i);
    for(int j=i;j<n-1;j++)
        set(j,get(j+1));
    n--;
    int r=blocks.size();
    if((r-2)*(r-1)/2>=n)
        shrink();
    return x;
}

template <class T> void RootishArrayStack<T>::grow() {
    blocks.add(blocks.size(),new T[blocks.size()+1]);
}

template <class T> void RootishArrayStack<T>::shrink() {
    //more than one empty block should shrink
    int r=blocks.size();
    while(r>0 && (r-2)*(r-1)/2>=n){
        delete [] blocks.remove(blocks.size()-1);
        r--;
    }
}

#endif //DATASTRUCTURE_ROOTISHARRAYSTACK_H
