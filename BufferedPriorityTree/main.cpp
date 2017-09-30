//
//  main.cpp
//  BufferedPriorityTree
//
//  Created by Kaitlyn Reinan on 9/22/17.
//  Copyright © 2017 Kaitlyn Reinan. All rights reserved.
//

#include <iostream>
#include "Node.hpp"

int main(int argc, const char * argv[]) {
    Leaf<int> *n = new Leaf<int>(3);
    std::cout << n->getVal() << std::endl;
    return 0;
}
