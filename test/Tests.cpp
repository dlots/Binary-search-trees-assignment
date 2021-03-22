#include "../src/util/RandomGenerator.h"
#include "Tests.h"

#include <iostream>
#include <functional>


bool traversalIsSorted(AbstractTree& tree)
{
    vector<uint64_t> traversal_output;
    tree.inOrderTraversal(traversal_output);
    return is_sorted(traversal_output.begin(), traversal_output.end());
}

bool removeRoot()
{
    AVLTree avl;
    Treap treap;
    SplayTree splay;

    vector<uint64_t> numbers;
    RandomNumberGenerator::getUniqueRandomNumbers(10, numbers);

    for (auto const &number : numbers)
    {
        avl.insert(number);
        treap.insert(number);
        splay.insert(number);
    }

    bool result = true;

    auto stri = treap.inOrderTraversalString();

    avl.remove(avl.getRoot()->key);
    treap.remove(treap.getRoot()->key);
    splay.remove(splay.getRoot()->key);

    stri = treap.inOrderTraversalString();

    result &= avl.inOrderTraversalString().length() == 9;
    result &= treap.inOrderTraversalString().length() == 9;
    result &= splay.inOrderTraversalString().length() == 9;

    result &= traversalIsSorted(avl);
    result &= traversalIsSorted(treap);
    result &= traversalIsSorted(splay);

    return result;
}

bool checkHeapOrder()
{
    Treap treap;
    vector<uint64_t> numbers;
    RandomNumberGenerator::getUniqueRandomNumbers(100, numbers);
    for (auto const &number : numbers)
    {
        treap.insert(number);
    }

    function<bool(Node*)> recursiveCheckHeapOrder;
    recursiveCheckHeapOrder = [&recursiveCheckHeapOrder](Node* node)
    {
        if (!node)
        {
            return true;
        }

        bool ordered = true;

        if (node->left)
        {
            ordered &= node->priority > node->left->priority;
            ordered &= recursiveCheckHeapOrder(node->left);
        }
        if (node->right)
        {
            ordered &= node->priority > node->right->priority;
            ordered &= recursiveCheckHeapOrder(node->right);
        }

        return ordered;
    };

    return recursiveCheckHeapOrder(treap.getRoot());
}

bool checkHeightBalanceAndDepth()
{
    AVLTree avl;
    vector<uint64_t> numbers;
    uint64_t n = 100;
    RandomNumberGenerator::getUniqueRandomNumbers(n, numbers);
    for (auto const &number : numbers)
    {
        avl.insert(number);
    }

    function<bool(Node*)> recursiveCheckHeightBalance;
    recursiveCheckHeightBalance = [&recursiveCheckHeightBalance](Node* node)
    {
        if (!node)
        {
            return true;
        }

        bool balanced = true;

        if (node->left && node->right)
        {
            balanced &= abs(node->left->height - node->right->height) < 2;
            balanced &= recursiveCheckHeightBalance(node->left);
            balanced &= recursiveCheckHeightBalance(node->right);
        }
        else if (node->left)
        {
            balanced &= node->left->height == 1;
        }
        else if (node->right)
        {
            balanced &= node->right->height == 1;
        }

        return balanced;
    };

    return recursiveCheckHeightBalance(avl.getRoot()) &&
            (avl.getRoot()->height <= (1.45 * log2(n+2)));
}

bool largeStructureTraversal()
{
    AVLTree avl;
    Treap treap;
    SplayTree splay;

    vector<uint64_t> numbers;
    RandomNumberGenerator::getUniqueRandomNumbers(100000, numbers);

    for (auto const &number : numbers)
    {
        avl.insert(number);
        treap.insert(number);
        splay.insert(number);
    }

    return (traversalIsSorted(avl) && traversalIsSorted(treap) && traversalIsSorted(splay));
}

void runTests()
{
    cout << "Unit tests" << endl;

    cout << endl << "Treap specific unit tests" << endl;
    cout << "Check treap heap order: " << (checkHeapOrder() ? "PASSED." : "FAILED.") << endl;

    cout << endl << "Splay specific unit tests" << endl;

    cout << endl << "AVL specific unit tests" << endl;
    cout << "Check AVL tree balance and depth: " << (checkHeightBalanceAndDepth() ? "PASSED." : "FAILED.") << endl;

    cout << endl << "Common unit tests" << endl;
    cout << "Removing a root does not corrupt a tree: " << (removeRoot() ? "PASSED." : "FAILED.") << endl;

    cout << endl << "Stress tests" << endl;
    cout << "Correct traversal output for n=100000: " << (largeStructureTraversal() ? "PASSED." : "FAILED.") << endl;
}