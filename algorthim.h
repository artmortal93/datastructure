//
// Created by steafan on 2020/4/10.
//

#ifndef DATASTRUCTURE_ALGORTHIM_H
#define DATASTRUCTURE_ALGORTHIM_H

#include "SLList.h"
#include "utils.h"
#include "array.hpp"
#include "BinaryHeap.h"


template <class T> void merge(array<T> &a0,array<T> &a1,array<T> &a){
    int i0=0,i1=0;
    for(int i=0;i<a.length;i++){
        if(i0==a0.length)
            a[i]=a1[i1++];
        else if (i1==a1.length)
            a[i]=a[0][i0++];
        else if (compare(a0[i0],a1[i1])<0)
            a[i]=a[0][i0++];
        else
            a[i]=a1[i1++];
    }
}

//using [begin,end)
template <class T> void mergeSort(array<T> &a){
    if(a.length<=1)
        return;
    array<T> a0(0);
    array<T> a1(0);
    array<T>::copyOfRange(a0,a,0,a.length/2);
    array<T>::copyOfRange(a1,a,a.length/2,a.length); //[begin,end)
    mergeSort(a0);
    mergeSort(a1);
    merge(a0,a1,a);

}


template <class T> void heapSort(array<T> &a){
    BinaryHeap<T>::sort(a);
}

template <class T> void quickSort(array<T> &a){
    quickSort(a,0,a.length);

}
//[start,num)
template <class T> void quickSort(array<T> & a,int i,int n){
    if(n<=1)
        return;
    T x=a[i+rand()%n];
    int p=i-1,j=i,q=i+n;
    ///j=a moving pointer
    ///q=end pointer(after last one),indicate the leftmost elements that bigger than pivot
    ///p=start pointer,before the first one,indicate the rightmost elements that smaller than pivot
    while(j<q){
        ///important stop,j run out of space
        int comp=compare(a[j],x);
        if(comp<0){
            p++;
            a.swap(j,p);
            j++;
        }
        else if(comp>0){
            a.swap(j,--q);
        }
        else{
            j++; //ignore
        }
    }
    //until here , the T x has been remove to correct place
    quickSort(a,i,p-i+1);//sort other elements
    quickSort(a,q,n-(q-i));
}



///for example c[1]  c[2]  c[3]  c[4]
///            2      2     5    10
///   so b[0],b[1] should be 1, b[2]..b[4] should be 3
///k=length
void countingSort(array<int> &a,int k){
    array<int> c(k,0);//init k size
    //c is a slot save how many number element the same of index is on this array
    for(int i=0;i<a.length;i++)
        c[a[i]]++;
    for(int i=1;i<k;i++)
        c[i]+=c[i-1]; //calculate the accum sum number until this elements
     array<int> b(a.length);
     for(int i=a.length-1;i>=0;i--){//key reverse order that could reuse in the radix sort
         c[a[i]]--;
         b[i]=a[i];
     }
     a=b;
}

///
/// \param a
///sort big integer 32bit into 8 bit representation
/// counting sort version of big numbers 0---n,which n is very big number
/// example 270,280
///correctness prove:
/// a is alrdeay sorted in increasing order
///but countingsort start inserting value from the biggest value
///so in the next sorting ,280 is always ahead of 270,even 2 is in the same area
void radixSort(array<int> &a){
    int d=8,w=32;
    for(int p=0;p<w/d;p++){
        array<int> c(1<<d,0);//counting slot array of 2^d
        array<int> b(a.length);
        ///doing countingsort,but extract the part of the integer
        for(int i=0;i<a.length;i++)
            c[(a[i]>> d*p)&((1<<d)-1)]++;//extart this part pf 8 bit integer
        for(int i=1;i< 1<<d;i++)
            c[i]+=c[i-1]; //calculate the accum sum number until this elements
        for(int i=a.length-1;i>=0;i--){
            c[(a[i]>> d*p)&((1<<d)-1)]--;
            b[c[(a[i]>> d*p)&((1<<d)-1)]]=a[i];
        }
        a=b;
    }
}



#endif //DATASTRUCTURE_ALGORTHIM_H
