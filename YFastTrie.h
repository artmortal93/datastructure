//
// Created by steafan on 2020/4/14.
//

#ifndef DATASTRUCTURE_YFASTTRIE_H
#define DATASTRUCTURE_YFASTTRIE_H

#include "Treap.h"
#include "XFastTrie.h"

/**
 * Warning YFastTrie depends on XFastTrie, so you can't use it to store
 * the values UINT_MAX-1 or UINT_MAX-2
 */
 //y-fast trie use xfast trie to store n/w value,
 //and each leaf value contains a trap for fast searching
 //ypair is a pair of x-trie node and a corresponding treap
 //also it's the Node<t> TYPE of x-fast trie
 //Y Fast Trie implement a SSET interface, but could also use as a PRIORITY QUEUE
 //because Y-Fast and X-fast both have a double linked list(ordered) structure
 template <class T> class YPair{
public:
     unsigned ix;
     Treap1<T> *t;
     YPair(){};
     YPair(unsigned ix0, Treap1<T> *t0) { ix = ix0; t = t0; }
     YPair(unsigned ix0) { ix = ix0; }
 };


template<class T>
unsigned intValue(const YPair<T> &p) {
    return p.ix;
}

template <class T> class YFastTrie{
    static const int w=32;
    XFastTrie1<YPair<T> > xft;
    int n;
public:
    YFastTrie();
    virtual ~YFastTrie();
    T find(T x);
    bool add(T x);
    bool remove(T x);
    int size() { return n; }
    void clear() {} ;
};


template <class T> YFastTrie<T>::YFastTrie() :xft(){
    n=0;
    xft.add(YPair<T>(UINT_MAX,new Treap1<T>()));//dummy
}

template<class T>
YFastTrie<T>::~YFastTrie() {
/*  FIXME: Need to iterate over the YFastTrie elements
	XFastTrieNode1<YPair<T> > *u = xft.dummy.next;
	while (u != &xft.dummy) {
		delete u->x.t;
		u = u->next;
	}
*/
    xft.clear();
    n = 0;
}


template <class T> T YFastTrie<T>::find(T x) {
    return xft.find(YPair<T>(intValue(x))).t->find(x);
}

template <class T> bool YFastTrie<T>::add(T x) {
    unsigned ix=intValue(x);
    Treap1<T> *t=xft.find(YPair<T>(ix)).t;//find suitable treap
    if(t->add(x)){
        n++;
        if(rand()%w==0){  //1/w chance to add a new node
            Treap1<T> *t1=(Treap1<T>*)t->split(x);//treap split into two subtrees
            xft.add(YPair<T>(ix,t1));
        }
        return true;
    }
    return false;
}

template <class T> bool YFastTrie<T>::remove(T x) {
    unsigned ix=intValue(x);
    XFastTrieNode1<YPair<T> > *u=xft.findNode(ix);
    bool ret=u->x.t->remove(x);
    if(ret)
        n--;
    if(u->x.ix==ix && ix!= UINT_MAX){//happen to be also stored in x-fast trie,had to remove it
        Treap1<T> *t2=u->child[1]->x.t;//child 1 =next node(sibling's) trie
        t2->absorb(*u->x.t);//absort the treap
        xft.remove(u->x);
    }
    return ret;

}


#endif //DATASTRUCTURE_YFASTTRIE_H
