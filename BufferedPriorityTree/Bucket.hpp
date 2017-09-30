//
//  Bucket.hpp
//  BufferedPriorityTree
//
//  Created by Kaitlyn Reinan on 9/22/17.
//  Copyright © 2017 Kaitlyn Reinan. All rights reserved.
//

#ifndef Bucket_hpp
#define Bucket_hpp

#include <stdio.h>
#include "DoublingArray.hpp"

template <typename T>
class Bucket {
    Bucket *next;
    DoublingArray<T> array;
    
public:
    Bucket(DoublingArray<T> items) {
        array = items;
        next = nullptr;
    }
    ~Bucket() {
        delete array;
    }
    Bucket &operator=(Bucket other) = delete;
    Bucket(Bucket const &other) = delete;
    void setNext(Bucket *n) {
        next = n;
    }
    int length() {
        return array.length();
    }
    T &operator[](int i) {
        return array[i];
    }
};

#endif /* Bucket_hpp */
