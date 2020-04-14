//
// Created by steafan on 2020/4/15.
//

#ifndef DATASTRUCTURE_BLOCKSTORE_H
#define DATASTRUCTURE_BLOCKSTORE_H

#include "ArrayStack.hpp"
/**
 * This class fakes an external memory block storage system. It's just a list
 * of blocks.
 **/

template <class T> class BlockStore{
protected:
    ArrayStack<T> blocks;
    ArrayStack<unsigned> free; // unused block indices
public:
    BlockStore():blocks(),free(){};
    virtual void clear(){
        blocks.clear();
        free.clear();
    }

    virtual ~BlockStore(){
        clear();
    }

    //add a block by expand if no free size is available,return new size ,or return the free block idx and do nth
    //or return a free idx?
    virtual int placeBlock(T block){
        int i;
        if(free.size()>0){
            i=free.remove(free.size());
        }
        else{
            i=blocks.size();
            blocks.add(i,block);

        }
        return i;
    }
    virtual void freeBlock(int i) {
        blocks.set(i, NULL);
        free.add(i);
    }
    virtual T readBlock(int i) {
        return blocks.get(i);
    }
    void writeBlock(int i, T block) {
        blocks.set(i, block);
    }
};

#endif //DATASTRUCTURE_BLOCKSTORE_H
