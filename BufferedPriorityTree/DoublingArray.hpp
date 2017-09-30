//
//  DoublingArray.hpp
//  BufferedPriorityTree
//
//  Created by Kaitlyn Reinan on 9/22/17.
//  Copyright © 2017 Kaitlyn Reinan. All rights reserved.
//

#ifndef DoublingArray_hpp
#define DoublingArray_hpp

#include <stdio.h>

template <typename T>
class DoublingArray {
    int len;
    int capacity;
    T *array;
    
public:
    DoublingArray() {
        array = new T[1];
        capacity = 1;
        len = 0;
    }
    DoublingArray &operator=(DoublingArray other) = delete;
    DoublingArray(DoublingArray const &other) = delete;
    ~DoublingArray() {
        delete[] array;
    }
    void push(int numItems, T *items) {
        while(len + numItems > capacity) {
            capacity *= 2;
            T *temp = new T[capacity];
            for(int i = 0; i < len; ++i) {
                temp[i] = array[i];
            }
            delete[] array;
            array = temp;
        }
        for(int i = 0; i < numItems; ++i) {
            array[len + i] = items[i];
        }
        len += numItems;
    }
    void push(T item) {
        if(len >= capacity) {
            capacity *= 2;
            T *temp = new T[capacity];
            for(int i = 0; i < len; ++i) {
                temp[i] = array[i];
            }
            delete[] array;
            array = temp;
        }
        array[len] = item;
        ++len;
    }
    T pop() {
        --len;
        return array[len];
    }
    T &operator[](int i) {
        return array[i];
    }
    void empty() {
        len = 0;
    }
    void length() {
        return len;
    }
};

#endif /* DoublingArray_hpp */
