#include "SplayTree.h"

#include <iostream>


SplitResult SplayTree::split(Node* tree, uint64_t key)
{
    Node* node = search(key);
    if (!node)
    {
        if (key < min)
        {
            node = successor(key);
        }
        else
        {
            node = predecessor(key);
        }
        splay(node);
    }

    Node* tree1;
    Node* tree2;
    if (key < node->key)
    {
        tree1 = node->left;
        node->left = nullptr;
        tree1->parent = nullptr;
        tree2 = node;
    }
    else
    {
        tree2 = node->right;
        node->right = nullptr;
        tree2->parent = nullptr;
        tree1 = node;
    }

    return { tree1, tree2 };
}

Node* SplayTree::merge(Node* tree1, Node* tree2)
{
    if (!tree1)
    {
        return tree2;
    }
    if (!tree2)
    {
        return tree1;
    }

    Node* rightMostInTree1 = tree1;
    while (rightMostInTree1->right)
    {
        rightMostInTree1 = rightMostInTree1->right;
    }
    splay(rightMostInTree1);
    root->right = tree2;
    if (tree2)
    {
        tree2->parent = root;
    }
    return root;
}

Node* SplayTree::search(uint64_t key)
{
    Node* node = AbstractTree::search(key);
    splay(node);
    return node;
}

Node* SplayTree::insert(uint64_t key)
{
    Node* newNode = AbstractTree::insert(key);
    splay(newNode);
    return newNode;
}

Node* SplayTree::remove(uint64_t key)
{
    if (Node* node = search(key))
    {
        if (key == max)
        {
            max = predecessor(key)->key;
        }
        if (key == min)
        {
            min = successor(key)->key;
        }

        // splay(node) is already called in search()
        root = merge(node->left, node->right);
        root->parent = nullptr;
        delete node;
    }
    return root;
}

void SplayTree::splay(Node* node)
{
    if (!node || (node == root))
    {
        return;
    }

    while(node->parent)
    {
        Node* parent = node->parent;
        Node* grandparent = parent->parent;
        if (node == parent->left)
        {
            if (!grandparent)
            {
                rotate_right(node);
            }
            else if (parent == grandparent->left)
            {
                rotate_right(parent);
                rotate_right(node);
            }
            else
            {
                rotate_right(node);
                rotate_left(node);
            }
        }
        else
        {
            if (!grandparent)
            {
                rotate_left(node);
            }
            else if (parent == grandparent->right)
            {
                rotate_left(parent);
                rotate_left(node);
            }
            else
            {
                rotate_left(node);
                rotate_right(node);
            }
        }
    }

    root = node;
}

void SplayTree::rotate_right(Node* node)
{
    Node* y = node->parent;
    if (!y)
    {
        return;
    }
    Node* grandparent = y->parent;
    Node* beta = node->right;

    if (beta)
    {
        beta->parent = y;
    }
    y->left = beta;

    if (grandparent)
    {
        if (y == grandparent->left)
        {
            grandparent->left = node;
        }
        else
        {
            grandparent->right = node;
        }
    }
    y->parent = node;

    node->right = y;
    node->parent = grandparent;
}

void SplayTree::rotate_left(Node* node)
{
    Node* y = node->parent;
    if (!y)
    {
        return;
    }
    Node* grandparent = y->parent;
    Node* beta = node->left;

    if (beta)
    {
        beta->parent = y;
    }
    y->right = beta;

    if (grandparent)
    {
        if (y == grandparent->left)
        {
            grandparent->left = node;
        }
        else
        {
            grandparent->right = node;
        }
    }
    y->parent = node;

    node->left = y;
    node->parent = grandparent;
}
