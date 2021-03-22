#include "AVLTree.h"

void AVLTree::rotate_right(Node* node)
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

    y->height = std::max(height(y->left), height(y->right)) + 1;
    node->height = std::max(height(node->left), height(node->right)) + 1;

    if (!node->parent)
    {
        root = node;
    }
}

void AVLTree::rotate_left(Node* node)
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

    y->height = std::max(height(y->left), height(y->right)) + 1;
    node->height = std::max(height(node->left), height(node->right)) + 1;

    if (!node->parent)
    {
        root = node;
    }
}

int64_t AVLTree::height(Node* node)
{
    if (!node)
    {
        return 0;
    }
    else
    {
        return node->height;
    }
}

int64_t AVLTree::nodeBalance(Node* node)
{
    if (!node)
    {
        return 0;
    }
    else
    {
        return height(node->left) - height(node->right);
    }
}

Node* AVLTree::insert(uint64_t key)
{
    Node* node = AbstractTree::insert(key);
    if (node == root)
    {
        return node;
    }

    Node* parent = node->parent;
    while (parent)
    {
        balanceNode(parent, key);
        parent = parent->parent;
    }

    return node;
}

Node* AVLTree::remove(uint64_t key)
{
    Node* parent = AbstractTree::remove(key);
    Node* parentToReturn = parent;
    while (parent)
    {
        balanceNode(parent, key);
        parent = parent->parent;
    }
    return parent;
}

SplitResult AVLTree::split(Node *tree, uint64_t key) {
    return SplitResult();
}

Node *AVLTree::merge(Node *tree1, Node *tree2) {
    return nullptr;
}

void AVLTree::balanceNode(Node* node, uint64_t key)
{
    node->height = 1 + std::max(height(node->left), height(node->right));
    int64_t balance = nodeBalance(node);

    //left left
    if (balance > 1 && key < node->left->key)
    {
        rotate_right(node->left);
    }
        //right right
    else if (balance < -1 && key > node->right->key)
    {
        rotate_left(node->right);
    }
        //left right
    else if (balance > 1 && key > node->left->key)
    {
        rotate_left(node->left->right);
        rotate_right(node->left);
    }
        //right left
    else if (balance < -1 && key < node->right->key)
    {
        rotate_right(node->right->left);
        rotate_left(node->right);
    }
}
