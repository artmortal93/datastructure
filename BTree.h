//
// Created by steafan on 2020/4/15.
//

#ifndef DATASTRUCTURE_BTREE_H
#define DATASTRUCTURE_BTREE_H


#include "array.hpp
#include "BlockStore.h"
//two elements:keys(index) childens(node) in one node
// B-2B Nodes(except root)(B-2-2B-1 keys)
//key= the value need to be stored
// i= the simulated phsyical address of the block
// which equals B-1,2B-1 keys
//PROPERTY:SAME HEIGHT,AND KEY IN PARENT NODE always bigger than left child's keys
//T x is not involved into the comparison
template <class T> class BTree{
public:
    T null;
    int b;//the maximum number of children of a node
    int B;//b div 2 (B-b) nodes in non-leaf non-root node
    int n;//number of elements stored in the tree
    int ri;//index of the root?(key)(0)
    //array<T> could be partially null,but the suffix of array is garuanttee full
    // if not found ,return the index which it's value is smallest bigger than key
    // [a,b) for binary search, the invariant is that b is not capable for searching so a=b == could not search anything
    int findIt(array<T> &a, T x) {
        int lo = 0, hi = a.length;
        while (hi != lo) {
             int m=(hi+lo)/2;
             int cmp=a[m]==null?-1:compare(x,a[m]);
             if(cmp<0)
                 hi=m;//acceptable for null
             else if (cmp>0)
                 lo=m+1;
             else ///if found?
                 return -m-1;//if found return a negative number
        }
        //could not find any,return a positive?
        return lo;
    }

    class Node;
    //bs is the simulated of the hard-disk,each node is one block in the disk?

    BlockStore<Node*> bs;
    class Node{
    public:
        BTree *t;
        int id;
        array<T> keys; //key is T???
        array<int> children;//int index of the block store hard disk
    public:
        //reserve one place for full condition(2B+1)
        Node(BTree* t):keys(t->b),children(t->b+1){
            this->t=t;
            std::fill_n(children,t->b+1,-1);
            id=t->bs.placeBlock(this);//get the id in the place block(hardware system)
        }

        bool isLeaf(){
            return children[0]<0;
        }

        bool isFull(){
            return keys[keys.length-1] != t->null;
        }
        ///use binary search to find the length of children
        int size(){
            int lo=0, h=keys.length;
            while(h!=lo){
                int m=(h+lo)/2;
                if(keys[m]==t->null)
                    h=m;
                else
                    lo=m+1;
            }
            return lo;
        }
        //add a key and node index into children
        bool add(T x,int ci){
            int i=t->findIt(keys,x);
            if(i<0)
                return false;
            if(i<keys.length-1)//could not find,find the prev index
                //right shift to make place
                std::copy(keys+i,keys+t->b-1,keys+i+1);
            keys[i]=x;
            if (i < keys.length-1) //right shift to insert
                std::copy(children + i+1, children + t->b, children + i+2);
            children[i+1] = ci;//child i,key i,child i+1....
            return true;
        }
        //remove a key at index i
        T remove(int i){
            T y=keys[i];
            std::copy(keys+i+1,keys+t->b,keys+i); //resort keys array in order
            keys[keys.length-1]=t->null;
            return y;
        }
        //split two node if one node is full
        Node* split(){
           Node *w=new Node(t);
           int j=keys.length/2;//2B Keys->B keys
           std::copy(keys+j,keys+t->b,w->keys+0);
           std::fill(keys+j,keys+t->b,t->null);
           std::copy(children+j+1,children+t->b+1,w->children+0);
           std::fill(children+j+1,children+t->b+1,-1);
           t->bs.writeBlock(id,this);
            return  w;
        }

        virtual ~Node(){

        }
    };

public:
    void clear(){
        //FAKE CLEAN UP
        ri=(new Node(this))->id;
    }
    ///add T x in block ui
    Node* addRecursive(T x,int ui){
        Node *u=bs.readBlock(ui);
        int i=findIt(u->keys,x);
        if(i<0)
            throw(-1); //already added
        if(u->children[i]<0) //leaf node case
        {
            u->add(x,-1);//children is -1 for leaf node case
            //child i,key i,child i+1
            bs.writeBlock(u->id,u);//simulated read operation in harddisk
        }
        else{
            Node* w=addRecursive(x,u->children[i]);
            if(w!=NULL)//child was split,w is a new child
            {
                //u is the node of current layer,here comes new w child instead of children[i]
                //0 is a redundant key information left when splitting the nodes
                x=w->remove(0);//w contains bigger part of u->children[i]
                bs.writeBlock(w->id,w);//read back
                u->add(x,w->id);//w's key is all bigger than key value x
                bs.writeBlock(u->id,u);
            }
        }
        return u->isFull()?u->split():NULL;
    }

    //merge u's children v,w into v
    void merge(Node* u,int i,Node* v,Node* w){
         assert(v->id==u->children[i]);
         assert(w->id==u->children[i+1]);
         int sv=v->size();
         int sw=w->size();
         //copy from w to v to keys
         std::copy(w->keys+0,w->keys+sw,v->keys+sv+1);
         //leave sv to empty key slot
         std::copy(w->children+0,w->children+sw+1,v->children+sv+1);
         v->keys[sv]=u->keys[i];
         std::copy(u->keys+i+1,u->keys+b,u->keys+i);//left shifting
         u->keys[b-1]=null;
         std::copy(u->children+i+2,u->children+b+1,u->children+i+1);
         u->children[b]=-1;
    }
    //borrow from v to w
    void shiftLR(Node *u,int i,Node *v,Node *w){
        int sw=w->size();
        int sv=v->size();
        int shift=((sw+sv/2))-sw;
        //make space for new keys in w
        std::copy(w->keys+0,w->keys+sw,w->keys+shift);
        std::copy(w->children+0,w->children+sw+1,w->children+shift);
        //move keys and children out of v into w(and u)
        w->keys[shift-1]=u->keys[i];
        u->keys[i]=v->keys[sv-shift];
        std::copy(v->keys+sv-shift+1,v->keys+sv,w->keys+0);
        std::fill(v->keys+sv-shift,v->keys+sv,null);
        std::copy(v->children+sv-shift+1,v->children+sv+1,w->children+0);
        std::fill(v->children+sv-shift+1,v->children+sv+1,-1);
    }

   //borrow from w to v
    void shiftRL(Node *u,int i,Node *v,Node *w){
       assert(w->id == u->children[i] && v->id == u->children[i+1]);
       int sw = w->size();
       int sv = v->size();
       int shift = ((sw+sv)/2) - sw;  // num. keys to shift from v to w
       // shift keys and children from v to w
       w->keys[sw] = u->keys[i];
       std::copy(v->keys + 0, v->keys + shift-1, w->keys + sw+1);
       std::copy(v->children + 0, v->children + shift, w->children + sw+1);
       u->keys[i] = v->keys[shift-1];
       // delete keys and children from v
       std::copy(v->keys + shift, v->keys + b, v->keys + 0);
       std::fill(v->keys + sv-shift, v->keys + b, null);
       std::copy(v->children + shift, v->children + b+1, v->children + 0);
       std::fill(v->children + sv-shift+1, v->children + b+1, -1);
    }

    //use i-1,i+1 to avoid underflow
    void checkUnderflow(Node* u,int i){
        if(u->children[i]<0) //if is leaf node,no need to solve undeflow problem
            return;
        if(i==0)
            checkUnderflowZero(u,i);//use u's right sibling
        else
            checkUnderflowNonZero(u,i);//else use i-1
    }
    //when i=0
    void checkUnderflowZero(Node* u,int i){
        Node *w=bs.readBlock(u->children[i]);
        if(w->size()<B-1){//underflow at w
            Node *v = bs.readBlock(u->children[i+1]);
            if (v->size() > B) { // w can borrow from v
                shiftRL(u, i, v, w);
            } else { // w will absorb w
                merge(u, i, w, v);
                u->children[i] = w->id;
            }
        }
    }
    //when i!=0
    //i-1,i
    void checkUnderflowNonZero(Node* u,int i){
        Node *w=bs.readBlock(u->children[i]);
        if(w->size()<B-1){//underflow at w
            Node *v = bs.readBlock(u->children[i-1]);
            if(v->size()>B){//could borrow
                shiftLR(u,i-1,v,w);
            }
            else{
                merge(u,i-1,v,w);
            }
        }
    }
    //remove the smallest T in the tree
    T removeSmallest(int ui){
        Node* u=bs.readBlock(ui);
        if(u->isLeaf())
            return u->remove(0);
        T y=removeSmallest(u->children[0]);
        checkUnderflow(u,0);
        return y;
    }

    bool removeRecursive(T x,int ui){
        if(ui<0)//didnt find it
            return false;
        Node* u=bs.readBlock(ui);
        int i=findIt(u->keys,x);
        if(i<0)//found it
        {
            i=-(i+1);
            if(u->isLeaf()){
                u->remove(i);
            }
            else{
                u->keys[i]=removeSmallest(u->children[i+1]); //find the smallest leave and replace it
                checkUnderflow(u,i+1);
            }
            return true;
        }
        //if not found in this kayer
        else if(removeRecursive(x,u->children[i])){
            checkUnderflow(u,i);
            return true;
        }
        return false;
    }

    bool remove(T x) {
        if (removeRecursive(x, ri)) {
            n--;
            Node *r = bs.readBlock(ri);
            if (r->size() == 0 && n > 0) // root has only one child
                ri = r->children[0];
            return true;
        }
        return false;
    }

public:
    BTree(int b):bs(){
        null=(T)NULL;
        b+= (b+1)%2;
        this->b=b;
        b=b/2;
        ri=(new Node(this))->id;//0
    }

    bool add(T x){
        Node *w;
        try{
            w=addRecursive(x,ri);
        }
        catch(int e){
            return false;//duplicate
        }
        if(w!=NULL)//rot need to split to make new root
        {
            Node* newroot=new Node(this);
            x=w->remove(0);
            bs.writeBlock(w->id,w);
            newroot->children[0]=ri;
            newroot->keys[0]=x;
            newroot->children[1]=w->id;
            ri=newroot->id;
            bs.writeBlock(ri,newroot);
        }
        n++;
        return true;
    }
    //find the value greater or equal than x
    T find(T x){
        T z=null;//the value(entry in the disk)
        int ui=ri;//the hardware address of root node
        while(ui>=0){
            Node* u=bs.readBlock(ui);
            int i=findIt(u->keys,x);
            if(i<0) //founded it
                return u->keys[-(i+1)];
            //else found it's next key that it's happened to be bigger than the key
            if(u->keys[i]!=null)
                z=u->keys[i];//z is larger than x
            //children[i]<key[i]<children[i+1]
            ui=u->children[i];
        }
        return z;
    }

    virtual ~BTree() {
        // FIXME: Do this
    };

    int size() {
        return n;
    }

};

#endif //DATASTRUCTURE_BTREE_H
