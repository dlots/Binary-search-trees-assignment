#include "Treap.h"

#include <iostream>


Node* Treap::insert(uint64_t key)
{
    if (!root)
    {
        root = new Node(key, RandomNumberGenerator::getRandomNumber());
        return root;
    }

    Node* newNode = new Node(key, RandomNumberGenerator::getRandomNumber());
    SplitResult splitResult = split(root, key);
    root = merge(merge(splitResult.first, newNode), splitResult.second);

    if (key > max)
    {
        max = key;
    }
    if (key < min)
    {
        min = key;
    }

    return newNode;
}

Node* Treap::remove(uint64_t key)
{
    if (!root)
    {
        return nullptr;
    }

    SplitResult splitResult = split(root, key);
    Node* toDelete = AbstractTree::search(splitResult.first, key);
    Node* parent = nullptr;
    AbstractTree::remove(toDelete);
    // Node to delete may be a root of T1 subtree. After that, a pointer
    // to deleted memory will remain in splitResult.first. But in remove(),
    // new T1 subtree root is set to this->root.
    if (splitResult.first == toDelete)
    {
        splitResult.first = root;
    }
    root = merge(splitResult.first, splitResult.second);
    return parent;
}

SplitResult Treap::split(Node* tree, uint64_t key)
{
    Node* tree1 = nullptr;
    Node* tree2 = nullptr;

    if (!tree)
    {
        return { tree1, tree2 };
    }

    if (key < tree->key)
    {
        SplitResult splitResult = split(tree->left, key);
        tree1 = splitResult.first;
        tree2 = tree;
        tree2->left = splitResult.second;
        if (tree2->left)
        {
            tree2->left->parent = tree2;
        }
        //tree2->updateMinMax();
    }
    else
    {
        SplitResult splitResult = split(tree->right, key);
        tree1 = tree;
        tree1->right = splitResult.first;
        if (tree1->right)
        {
            tree1->right->parent = tree1;
        }
        //tree1->updateMinMax();
        tree2 = splitResult.second;
    }

    return {tree1, tree2};
}

Node* Treap::merge(Node* tree1, Node* tree2)
{
    if (!tree1)
    {
        return tree2;
    }
    if (!tree2)
    {
        return tree1;
    }

    /*if (tree1->max > tree2->min)
    {
        cerr << __FUNCTION__ << " trees are not split by key, unable to merge";
        return nullptr;
    }*/

    if (tree1->priority >= tree2->priority)
    {
        tree1->right = merge(tree1->right, tree2);
        if (tree1->right)
        {
            tree1->right->parent = tree1;
        }
        //tree1->updateMinMax();
        return tree1;
    }
    else
    {
        tree2->left = merge(tree1, tree2->left);
        if (tree2->left)
        {
            tree2->left->parent = tree2;
        }
        //tree2->updateMinMax();
        return tree2;
    }
}
