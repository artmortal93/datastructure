//
// Created by steafan on 2020/4/11.
//

#ifndef DATASTRUCTURE_GRAPHALGORTHIM_H
#define DATASTRUCTURE_GRAPHALGORTHIM_H

#include "AdjacencyList.h"
#include "AdjacencyMatrix.h"
#include "SLList.h" //first in last out implementation (STACK)
#include "ArrayStack.hpp"

enum { white, grey, black };
///QUEUE BASED breadth first search
///bfs  is used for shortest path
template <class Graph=WeightedAdjacnecyMatrix> void bfs(Graph& g,int r){
    bool *seen=new bool[g.nVerticles()];//only difference for tree/graph bfs,to record it isiteraitved or not
    int* p=new int[g.nVerticles()];//parents
    int* d=new int[g.nVerticles()];//depths,distances
    for(int i=0;i<g.nVertices();i++){
        p[i]=-1;//nil
        d[i]=0;
    }
    SLList<int> q; //queue here
    q.add(r); //r is the idx of the root
    seen[r]=true;
    while(q.size()>0){
        int i=q.remove(); //queue operation
        ArrayStack<int> edges;
        g.outEdges(i,edges);
        for(int k=0;k<edges.size();k++){
            int j=edges.get(k);
            if(!seen[j])
            {
                q.add(j);
                p[j]=i;
                d[j]=d[i]+1;
                seen[j]=true;
            }
        }
    }
    delete[] seen;
}

///recursive dfs
/// graph,start node,status array
template <class Graph> void dfs(Graph& g,int i,char *c){
   c[i]=grey; //currently visited
   ArrayStack<int> edges;
   g.outEdges(i,edges);
   for(int k=0;k<edges.size();k++){
       int j=edges.get(k);
       if(c[j]==white){
           c[j]=grey;
           dfs(g,j,c);
       }
   }
   c[i]=black; //done visiting i,actually no need
}
//graph,root,parent,depth,recursice depth
template <class Graph> void dfs(Graph& g,int i,char *c,int* p,int* d,int depth){
    c[i]=grey; //currently visited
    d[i]=depth;
    depth++;
    ArrayStack<int> edges;
    g.outEdges(i,edges);
    for(int k=0;k<edges.size();k++){
        int j=edges.get(k);
        if(c[j]==white){
            p[j]=i;//j's parent is i
            c[j]=grey;
            dfs(g,j,c,p,d,depth);
        }
    }
    c[i]=black; //done visiting i,actually no need
}


template<class Graph>
void dfs(Graph &g, int r) {
    char *c = new char[g.nVertices()];
    int* p=new int[g.nVertices()];//parents
    int* d=new int[g.nVertices()];//depths
    for(int i=0;i<g.nVertices();i++){
        p[i]=-1;//nil
        d[i]=0;
    }
    dfs(g, r, c,p,d,0);
    delete[] c;
}


//iterartive dfs
///using STACK
template <class Graph> void dfs2(Graph& g, int r){
    char *c = new char[g.nVertices()];
    SLList<int> s;
    s.push(r);
    while(s.size()>0){
        int i=s.pop();
        if(c[i]==white){
            c[i]=grey;
            ArrayStack<int> edges;
            g.outEdges(i,edges);
            for (int k = 0; k < edges.size(); k++)
                s.push(edges.get(k));
        }

    }
    delete[] c;
}


template <class Graph> void TopologicDfs(Graph& g,int i,char *c,int* p,int* d,int depth,SLList<int>& list){
    c[i]=grey; //currently visited
    d[i]=depth;
    depth++;
    ArrayStack<int> edges;
    g.outEdges(i,edges);
    for(int k=0;k<edges.size();k++){
        int j=edges.get(k);
        if(c[j]==white){
            p[j]=i;//j's parent is i
            c[j]=grey;
            dfs(g,j,c,p,d,depth);
        }
    }
    c[i]=black; //done visiting i,actually no need
    list.push(i);//add in head
}

//dfs like topological sort
template <class Graph=WeightedAdjacnecyMatrix> SLList<int> TopologicalSort(Graph& g,int r){
    char *c = new char[g.nVertices()];
    int* p=new int[g.nVertices()];//parents
    int* d=new int[g.nVertices()];//depths
    SLList<int> templist;
    for(int i=0;i<g.nVertices();i++){
        p[i]=-1;//nil
        d[i]=0;
    }
    TopologicDfs(g, r, c,p,d,0,templist);
    return templist;
}



#endif //DATASTRUCTURE_GRAPHALGORTHIM_H
