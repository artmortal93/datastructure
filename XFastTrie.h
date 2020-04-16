//
// Created by steaphan on 14/4/2020.
//

#ifndef DATASTRUCTURE_XFASTTRIE_H
#define DATASTRUCTURE_XFASTTRIE_H

/// x-fast trie =binary trie+ hast table with size w+1
// x-fast trie use hashmap array and binary search to find node
//x-fast trie=hashmaps+trie+double linked-list
//hashmap to store prefix

#include "BinaryTrie.h"
#include "LinearHashTable.hpp"
#include <climits>

template<class Node, class T>
class XFastTrieNode : public BinaryTrieNode<Node,T> {
public:
};
//XPair for hashtable searching,is the hashtable element
template <class Node> class XPair{
public:
    unsigned prefix;
    Node* u;
    explicit XPair(unsigned int prefix0){
        prefix=prefix0;
        u=NULL;
    }
    explicit XPair(unsigned int prefix0,Node *u0){
        prefix=prefix0;
        u=u0;
    }
    bool operator==(XPair &p){
        return prefix==p.prefix;
    }
    bool operator!=(XPair &p){
        return prefix!= p.prefix;
    }
};

template <class Node> int hashCode(XPair<Node> &p){
    return p.prefix;
}

template<class Node, class T>
class XFastTrie : public BinaryTrie<Node,T> {
protected:
    T nullt;
    using BinaryTrie<Node,T>::w;
    using BinaryTrie<Node,T>::n;
    using BinaryTrie<Node,T>::r;
    using BinaryTrie<Node,T>::right;
    using BinaryTrie<Node,T>::left;
    using BinaryTrie<Node,T>::dummy;
    XPair<Node> null;
    LinearHashTable<XPair<Node> > t[w+1];
public:
    XFastTrie();
    virtual ~XFastTrie();
    virtual T find(T x);
    virtual bool add(T x);
    bool remove(T x);
    void clear();
    Node* findNode(unsigned ix); // FIXME: should be protected
};

template <class Node,class T> void XFastTrie<Node,T>::clear() {
    BinaryTrie<Node,T>::clear();
    for(int i=0;i<=w;i++)
        t[i].clear();
}


template <class Node,class T> XFastTrie<Node,T>::XFastTrie()
: BinaryTrie<Node,T>(),null(UINT_MAX-1,NULL)
{
    XPair<Node> del(UINT_MAX-2);
    for(int i=0;i<w+1;i++){
        t[i].setNull(null);
        t[i].setDel(del);//set the del node
    }
};

template <class Node,class T> XFastTrie<Node,T>::~XFastTrie() {
    clear();
}

//find node using binary search,.could return precessor and successor
template <class Node,class T> Node* XFastTrie<Node,T>::findNode(unsigned ix) {
    int l=0,h=w+1;
    Node *v, *u = &r;
    while (h-l > 1) {
        int i = (l+h)/2;
        XPair<Node> p(ix >> (w-i));
        if ((v = t[i].find(p).u) == NULL) {
            h = i;
        } else {
            u = v;
            l = i;
        }
    }
    if (l == w) return u;
    Node *pred = (((ix >> (w-l-1)) & 1) == 1) ? u->jump : u->jump->prev;
    return (pred->next == &dummy) ? NULL : pred->next;
}


template <class Node,class T> bool XFastTrie<Node,T>::add(T x){
    int i, c = 0;
    unsigned ix = intValue(x);
    Node *u = &r;
    // 1 - search for ix until falling out of the trie
    for (i = 0; i < w; i++) {
        c = (ix >> (w-i-1)) & 1;
        if (u->child[c] == NULL) break;
        u = u->child[c];
    }
    if (i == w) return false; // trie already contains x - abort
    Node *pred = (c == right) ? u->jump : u->jump->left; // save for step 3
    u->jump = NULL;  // u will have two children shortly
    for(;i<w;i++){
        c=(ix >>(w-i-1))&1;
        u->child[c]=new Node();
        t[i+1].add(XPair<Node>(ix>>(w-i-1),u->child[c]));
        u->child[c]->parent=u;
    }
    u->x=x;
    // 3 add u to linked list
    u->prev = pred;
    u->next = pred->next;
    u->prev->next = u;
    u->next->prev = u;
    // 4 - walk back up, updating jump pointers
    Node *v = u->parent;
    while (v != NULL) {
        if ((v->left == NULL
             && (v->jump == NULL || intValue(v->jump->x) > ix))
            || (v->right == NULL
                && (v->jump == NULL || intValue(v->jump->x) < ix)))
            v->jump = u;
        v = v->parent;
    }
    n++;
    return true;
}
/// BinarySearch
/// 0-w
/// mid=lower(l+h/2)
/// while(l<h)
/// \tparam Node
/// \tparam T
/// \param x
/// \return
template <class Node,class T> T XFastTrie<Node,T>::find(T x) {
    int l=0, h=w+1;
    unsigned ix=intValue(x);
    Node *v, *u =&r;
    while(h-l>1){
        //finally would come to w
        int i=(l+h)/2;//find the mid point(round to smaller)
        XPair<Node> p(ix>>(w-i)); //get the prefix
        if((v=t[i].find(p).u)==NULL){ //not found
            h=i;
        }
        else{
            //if founded
            u=v;//record the node
            l=i;
        }
    }
    //if reach depth w,the node is found
    // l shows that how many l letters is matched
    if(l==w)
        return u->x;
    //the next node must have only child
    //u is the most matching node(may be root)
    Node *pred= (((ix>>(w-l-1)) &1)==1)
            ? u->jump:u->jump->prev;
    return (pred->next ==&dummy)?nullt:pred->next->x;
}

template <class Node,class T> bool XFastTrie<Node,T>::remove(T x) {
    // 1 - find leaf, u, containing x
    int i = 0, c;
    unsigned ix = intValue(x);
    Node *u = &r;
    for (i = 0; i < w; i++) {
        c = (ix >> (w-i-1)) & 1;
        if (u->child[c] == NULL) return false;
        u = u->child[c];
    }
    // 2 - remove u from linked list
    u->prev->next = u->next;
    u->next->prev = u->prev;
    Node *v = u;
    //3-delete nodes on path to u
    for(i=w-1;i>=0;i--){
        c = (ix >> (w-i-1)) & 1;
        v = v->parent;
        delete v->child[c];
        t[i].remove(XPair<Node>(x>>(w-i)));
        v->child[c]=NULL;
        if(v->child[1-c]!=NULL)
            break;
    }
    // 4 - update jump pointers,and go forward
    c=(ix>>(w-i-1))& 1;
    v->jump=u->child[1-c];//if c=0,use right child,if c=1, use left child
    v=v->parent;
    i--;
    for(;i>=0;i--){
        c=(ix>>(w-i-1))& 1;
        if(v->jump==u){
            v->jump=u->child[1-c];
        }
        v=v->parent;
    }
    n--;
    return true;
}

template<class T>
class XFastTrieNode1 : public XFastTrieNode<XFastTrieNode1<T>, T> { };


template<class T>
class XFastTrie1 : public XFastTrie<XFastTrieNode1<T>, T> { };

#endif //DATASTRUCTURE_XFASTTRIE_H
