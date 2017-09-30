//
//  FunnelSort.hpp
//  BufferedPriorityTree
//
//  Created by Kaitlyn Reinan on 9/24/17.
//  Copyright © 2017 Kaitlyn Reinan. All rights reserved.
//

#ifndef FunnelSort_hpp
#define FunnelSort_hpp

#include <stdio.h>
#include <cmath>
#include <algorithm>

template <typename T>
class k-merger {
    int k;
    k-merger *mergers;
public:
    k-merger(T *items, int beginIndex, int endIndex) {
        k = endIndex - beginIndex;
        if(k > 2){
            int numMergers = (int)ceil(pow(k,1.0/2));
            int numItems = (int)ceil((endIndex - beginIndex)/(double)numMergers);
            mergers = new k-merger<T>[numMergers];
            for(int i = 0; i < numMergers; ++i) {
                int mergeItems = std::min(numItems, endIndex - beginIndex - i * numItems);
                mergers[i] = new k-merger(items, beginIndex + i * numItems, beginIndex + i * numItems + mergeItems);
            }
        }
        else {
            mergers = nullptr;
        }
        capacity = 2 * pow(k, 3.0/2);
        outputBuffer = new T[capacity];
        numTaken = 0;
    }
    void invoke() {
        int numMergers = (int)ceil(pow(k,1.0/2));
        if(mergers[0].itemsInBuffer < mergers[0].capacity/2.0) {
            mergers[0].invoke();
        }
        k-merger *smallest = mergers[0];
        for(int i = 1; i < numMergers; ++i) {
            if(mergers[i].itemsInBuffer < mergers[i].capacity/2.0) {
                mergers[i].invoke();
            }
            if(mergers[i].outputBuffer[mergers[i].numTaken % mergers[i].capacity] < smallest.outputBuffer[smallest.numTaken % smallest.capacity]) {
                smallest = mergers[i];
            }
        }
        outputBuffer[(itemsInBuffer + numTaken) % capacity] = smallest.outputBuffer[smallest.numTaken % smallest.capacity];
        ++smallest.numTaken;
        --smallest.itemsInBuffer;
        ++itemsInBuffer;
        for(int i = 1; i < pow(k, 3); ++i) {
            smallest = mergers[0];
            for(int i = 1; i < numMergers; ++i) {
                if(mergers[i].outputBuffer[mergers[i].numTaken % mergers[i].capacity] < smallest.outputBuffer[smallest.numTaken % smallest.capacity]) {
                    smallest = mergers[i];
                }
            }
            outputBuffer[(itemsInBuffer + numTaken) % capacity] = smallest.outputBuffer[smallest.numTaken % smallest.capacity];
            ++smallest.numTaken;
            --smallest.itemsInBuffer;
            ++itemsInBuffer;
        }
    }
    T *outputBuffer;
    int itemsInBuffer;
    int capacity;
    int numTaken;
}

template <typename T>
T *k-merge(T *items, int beginIndex, int endIndex) {
    k-merger merger = new k-merger(items, beginIndex, endIndex);
    merger.invoke();
    for(int i = 0; i < merger.itemsInBuffer; ++i) {
        std::cout << merger.outputBuffer[i];
    }
}

template <typename T>
void funnelSort(T *items, int beginIndex, int endIndex) {
    if(beginIndex + 1 == endIndex) return;
    int numSplits = (int)floor(pow(endIndex - beginIndex), (1.0/3));
    int numItems = (int)ceil((endIndex - beginIndex)/(double)numSplits);
    for(int i = 0; i < numSplits; ++i) {
        int splitItems = std::min(numItems, endIndex - beginIndex - i * numItems);
        funnelSort(items, beginIndex + i * numItems, beginIndex + i * numItems + mergeItems);
    }
}

#endif /* FunnelSort_hpp */
