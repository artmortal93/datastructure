//
// Created by steafan on 2020/4/16.
//
#include "array.hpp"

#ifndef DATASTRUCTURE_TRIE_H
#define DATASTRUCTURE_TRIE_H
///as trie dont have parent like B-tree
//trie's delete should
static int alphabet=26;

template <class T,class Node> class TrieNode{
public:
    array<TrieNode*> childrens;
    bool is_word=false;
    explicit TrieNode(bool word=false):childrens(alphabet,NULL){
        is_word=word;
    }

};


template <class T,class Node> class Trie{
public:
     Node* r;
     int n;
     explicit Trie(){
         n=0;
         r=new TrieNode();
     }
     explicit ~Trie(){
         delete r;
     }

     void insert(T string){
         Node* u=r;
         for(int i=0;i<string.size();i++){
             int index=string[i]-'a';
             if(u->childrens[index]==NULL){
                 u->childrens[index]=new Node();
             }
             u=u->children[index];
         }
         u->is_word=true;
     }

     bool search(T string){
         Node *u=r;
         for(int i=0;i<string.size();i++){
             int index=string[i]-'a';
             if(u->childrens[index]==NULL){
                 return false;
             }
             u=u->children[index];
         }
         return u!=NULL && u->is_word;
     }

     bool isEmpty(Node* u){
         for (int i = 0; i < alphabet; i++)
             if (u->children[i])
                 return false;
         return true;
     }

     //remove the next layer node,return null if should be deleted ,or return node if it also be other word's prefix node
     Node* recursive_remove(Node* u,T string,int depth=0){
        if(!u)
            return NULL;
        //reach the match end, all strings are matched
        if(depth==string.size()){
            if(u->is_word)
                u->is_word= false;
            if(isEmpty(u)){ //if is  leaf node
               delete u;
               u=NULL;
            }
            return u;
        }

        int index=string[depth]-'a';
        u->children[index]=recursive_remove(u->children[index],string,depth+1);
        //after remove the children,is this node have other words's prefix
         //root should not be deleted
         if (isEmpty(u) && u->isword == false && u!=r) {
             delete (u);
             u = NULL;
         }
         return u;
     }

     void remove(T string){
         if(!search(string))
             return;
         recursive_remove(r,string,0);
     }
};

#endif //DATASTRUCTURE_TRIE_H
