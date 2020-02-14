//
//  utils.h
//  datastructure
//
//  Created by steafan on 2020/2/15.
//  Copyright © 2020年 steaphan. All rights reserved.
//

#ifndef utils_h
#define utils_h
template<class T> inline
T min(T a, T b) {
    return ((a)<(b) ? (a) : (b));
}

template<class T> inline
T max(T a, T b) {
    return ((a)>(b) ? (a) : (b));
}

template<class T> inline
int compare(T &x, T &y) {
    if (x < y) return -1;
    if (y < x) return 1;
    return 0;
}

template<class T> inline
bool equals(T &x, T &y) {
    return x == y;
}

inline
unsigned intValue(int x) {
    return (unsigned)x;
}

/**
 * This is terrible - don't use it
 */
int hashCode(int x);

template<class T> class XFastTrieNode1;


template<class T>
unsigned hashCode(const XFastTrieNode1<T> *u) {
    return u->prefix;
}


class dodo {
public:
    bool operator < (dodo &d) {
        return this < &d;
    }
};



#endif /* utils_h */
