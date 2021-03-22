#ifndef SEMINAR_LAB2_TESTS_H
#define SEMINAR_LAB2_TESTS_H

#include "../src/trees/AVLTree.h"
#include "../src/trees/Treap.h"
#include "../src/trees/SplayTree.h"

#include <cinttypes>
#include <algorithm>
#include <vector>

using namespace std;

// Utility
bool traversalIsSorted(AbstractTree& tree);

// Unit

// All
bool removeRoot();
bool removeKey();

// Treap
bool checkHeapOrder();

// Splay

// AVL
bool checkHeightBalanceAndDepth();

// Stress
bool largeStructureTraversal();

void runTests();

#endif //SEMINAR_LAB2_TESTS_H
