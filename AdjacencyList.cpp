//
// Created by steafan on 2020/4/12.
//

#include "AdjacencyList.h"


AdjacencyLists::AdjacencyLists(int n0) {
    n=n0;
    adj=new List[n];
}


AdjacencyLists::~AdjacencyLists() {
    delete[] adj;
}