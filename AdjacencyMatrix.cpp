//
// Created by steaphan on 11/4/2020.
//

#include "AdjacencyMatrix.h"


AdjacencyMatrix::AdjacencyMatrix(int n) {
    n=n;
    a=new bool*[n];
    for(int i=0;i<n;i++)
        a[i]=new bool[n];
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            a[i][j]=false;
}


AdjacencyMatrix::~AdjacencyMatrix() {
    for(int i=0;i<n;i++)
        delete [] a[i];
    delete [] a;
}
