//
// Created by steaphan on 11/4/2020.
//

#ifndef DATASTRUCTURE_ADJACENCYMATRIX_H
#define DATASTRUCTURE_ADJACENCYMATRIX_H


class AdjacencyMatrix{
protected:
    int n;
    bool **a;
public:
    AdjacencyMatrix(int n);
    virtual ~AdjacencyMatrix();
    virtual void addEdge(int i,int j){
        a[i][j]=true;
    }

    virtual void removeEdge(int i,int j){
        a[i][j]=false;
    }

    bool hasEdge(int i,int j){
        return a[i][j];
    }

    template <class List> void outEdges(int i,List& edges){
        for(int j=0;j<n;j++){
            if(a[i][j])
                edges.add(j);
        }
    }

    template <class List> void inEdges(int i,List& edges){
        for(int j=0;j<n;j++)
        {
            if(a[j][i])
                edges.add(j);
        }
    }

    int nVertices(){
        return n;
    }
};

class WeightedAdjacnecyMatrix:public AdjacencyMatrix{
protected:
    using AdjacencyMatrix::n;
    using AdjacencyMatrix::a;
    int **weights;
public:
    explicit WeightedAdjacnecyMatrix(int n):AdjacencyMatrix(n){
        weights=new int*[n];
        for(int i=0;i<n;i++)
            weights[i]=new int[n];
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                weights[i][j]=-1;
    }
    ~WeightedAdjacnecyMatrix() override{
        for(int i=0;i<n;i++){
            delete []weights[i];
        }
        delete weights;
        AdjacencyMatrix::~AdjacencyMatrix();
    }

    void addEdge(int i,int j) override{
        a[i][j]=true;
        weights[i][j]=1;
    }

    void removeEdge(int i,int j) override{
        //a[i][j]=false;
        AdjacencyMatrix::removeEdge(i,j);
        weights[i][j]=-1;
    }

    void addEdge(int i,int j,int w=1){
        a[i][j]=true;
        weights[i][j]=w;
    }

    int getEdgeWeight(int i,int j){
        return weights[i][j];
    }


};


#endif //DATASTRUCTURE_ADJACENCYMATRIX_H
