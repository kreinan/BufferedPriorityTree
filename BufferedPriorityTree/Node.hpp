//
//  Node.hpp
//  BufferedPriorityTree
//
//  Created by Kaitlyn Reinan on 9/22/17.
//  Copyright © 2017 Kaitlyn Reinan. All rights reserved.
//

#ifndef Node_hpp
#define Node_hpp

#include <stdio.h>
#include "Bucket.hpp"
#include "DoublingArray.hpp"
#include <cassert>

template <typename T>
class Node {
protected:
    T value;
    Node<T> *parent;
    Node() {}
public:
    Node<T> *getParent() {
        return parent;
    }
    virtual int getCount() = 0;
};

template <typename T>
class NonLeafNode : public Node<T> {
protected:
    Node<T> *leftChild;
    Node<T> *rightChild;
    NonLeafNode() {}
    int counter;

public:
    void setLeft(Node<T> *l) {
        leftChild = l;
    }
    void setRight(Node<T> *r) {
        rightChild = r;
    }
    int getCount() {
        return counter;
    }
    void decrementCounter() {
        --counter;
    }
    virtual void insertInBuffer(int numItems, T *items) = 0;
    virtual void visit() = 0;
};

template <typename T>
class Root : public NonLeafNode<T> {
    DoublingArray<T> *buffer;

public:
    Root() {
        buffer = new DoublingArray<T>();
        this->parent = nullptr;
    }
    void insertInBuffer(int numItems, T *items) {
        buffer->push(numItems, items);
        this->counter -= numItems;
    }
    void visit() {
        assert(this->counter > 0);
        DoublingArray<T> left = new DoublingArray<T>();
        DoublingArray<T> right = new DoublingArray<T>();
        for(int i = 0; i < buffer->length(); ++i) {
            if(buffer[i] < this->value) {
                left->push(buffer[i]);
            } else {
                right->push(buffer[i]);
            }
        }
        buffer->empty();
        this->leftChild->distributeElements(left);
        this->rightChild->distributeElements(right);
        if(this->leftChild->getCount() > 0) {
            this->leftChild->visit();
        } else {
            this->rightChild->visit();
        }
    }
};

template <typename T>
class InternalNode {
    Bucket<T> *buffer;
    Bucket<T> *lastBucket;
public:
    InternalNode() {
        buffer = nullptr;
        this->value = nullptr;
    }
    void distributeElements(DoublingArray<T> items) {
        Bucket<T> *newBucket = new Bucket<T>(items);
        lastBucket->setNext(newBucket);
        lastBucket = newBucket;
        this->counter -= items.length();
    }
    void visit() {
        DoublingArray<T> left = new DoublingArray<T>();
        DoublingArray<T> right = new DoublingArray<T>();
        Bucket<T> *next = buffer;
        while(next) {
            for(int i = 0; i < next->length(); ++i) {
                if(next[i] < this->value) {
                    left->push(next[i]);
                } else {
                    right->push(next[i]);
                }
            }
            next = next->next();
            delete this;
        }
        buffer = nullptr;
        this->leftChild->distributeElements(left);
        this->rightChild->distributeElements(right);
        if(this->leftChild->getCount() > 0) {
            this->leftChild->visit();
        } else {
            this->rightChild->visit();
        }
    }
};

template <typename T>
class Leaf : public Node<T> {
public:
    Leaf(T val) {
        this->value = val;
    }
    T getVal() {
        return this->value;
    }
    int getCount() {
        return 1;
    }
    void distributeElements(DoublingArray<T> items) { }
    void visit() {
        T ret = this->value;
        NonLeafNode<T> *cur = this->getParent();
        while(cur) {
            cur->decrementCounter();
            cur = cur->getParent();
        }
        return ret;
    }
};

#endif /* Node_hpp */
