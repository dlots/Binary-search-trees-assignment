#include "AbstractTree.h"

#include <functional>
#include <iostream>
#include <sstream>
#include <iterator>


Node* AbstractTree::search(uint64_t key)
{
    return search(root, key);
}

Node* AbstractTree::successor(uint64_t key)
{
    if (key >= max)
    {
        return search(max);
    }

    Node* succ;
    successor(root, key, succ);
    return succ;
}

Node* AbstractTree::predecessor(uint64_t key)
{
    if (key <= min)
    {
        return search(min);
    }

    Node* pred;
    predecessor(root, key, pred);
    return pred;
}

Node* AbstractTree::getKthStatistic(uint64_t k)
{
    return getKthStatistic(root, k);
}

Node* AbstractTree::search(Node* node, uint64_t key)
{
    if (!node || (node->key == key))
    {
        return node;
    }
    else if (key < node->key)
    {
        return search(node->left, key);
    }
    else
    {
        return search(node->right, key);
    }
}

void AbstractTree::successor(Node* node, uint64_t key, Node*& succ)
{
    if (!node)
    {
        return;
    }

    if (key == node->key)
    {
        if (node->right)
        {
            Node *leftmostInRightSubtree = node->right;
            while (leftmostInRightSubtree->left) {
                leftmostInRightSubtree = leftmostInRightSubtree->left;
            }
            succ = leftmostInRightSubtree;
        }
    }
    else if (key < node->key)
    {
        succ = node;
        successor(node->left, key, succ);
    }
    else
    {
        successor(node->right, key, succ);
    }
}

void AbstractTree::predecessor(Node* node, uint64_t key, Node*& pred)
{
    if (!node)
    {
        return;
    }

    if (key == node->key)
    {
        if (node->left)
        {
            Node *rightmostInLeftSubtree = node->left;
            while (rightmostInLeftSubtree->right) {
                rightmostInLeftSubtree = rightmostInLeftSubtree->right;
            }
            pred = rightmostInLeftSubtree;
        }
    }
    else if (key < node->key)
    {
        predecessor(node->left, key, pred);
    }
    else
    {
        pred = node;
        predecessor(node->right, key, pred);
    }
}

Node* AbstractTree::getKthStatistic(Node *node, uint64_t& k)
{
    if (!node)
    {
        return node;
    }

    if (Node* left = getKthStatistic(node->left, k))
    {
        return left;
    }

    --k;
    if (k == 0)
    {
        return node;
    }

    return getKthStatistic(node->right, k);
}

void AbstractTree::inOrderTraversal(vector<uint64_t>& traversal_vector)
{
    function<void(Node*)> recursiveTraversal;
    recursiveTraversal = [&recursiveTraversal, &traversal_vector](Node* node)
    {
        if (!node)
        {
            return;
        }

        recursiveTraversal(node->left);
        traversal_vector.push_back(node->key);
        recursiveTraversal(node->right);
    };

    recursiveTraversal(this->root);
}

void AbstractTree::clear()
{
    if (!root)
    {
        return;
    }

    function<void(Node*)> recursiveClear;
    recursiveClear = [&recursiveClear](Node* node)
    {
        if (!node)
        {
            return;
        }

        recursiveClear(node->left);
        Node* right = node->right;
        delete node;
        recursiveClear(right);
    };

    recursiveClear(root);
}

Node* AbstractTree::insert(uint64_t key)
{
    Node* newNode;

    if (root)
    {
        newNode = insert(root, key);
    }
    else
    {
        root = new Node(key);
        newNode = root;
    }

    /*if (newNode->parent)
    {
        newNode->parent->updateMinMax();
    }*/

    if (key < min)
    {
        min = key;
    }
    if (key > max)
    {
        max = key;
    }

    return newNode;
}

Node* AbstractTree::remove(uint64_t key)
{
    if (key == max)
    {
        max = predecessor(key)->key;
    }
    if (key == min)
    {
        min = successor(key)->key;
    }
    return remove(search(key));
}

Node* AbstractTree::insert(Node* node, uint64_t key)
{
    if (!node)
    {
        cerr << "Attempt to call AbstractTree::insert with nullptr." << endl;
    }

    if (key == node->key)
    {
        return node;
    }
    else if (key < node->key)
    {
        if (!node->left)
        {
            node->left = new Node(key);
            node->left->parent = node;
            return node->left;
        }
        else
        {
            return insert(node->left, key);
        }
    }
    else
    {
        if (!node->right)
        {
            node->right = new Node(key);
            node->right->parent = node;
            return node->right;
        }
        else
        {
            return insert(node->right, key);
        }
    }
}

Node* AbstractTree::remove(Node* node)
{
    if (!node)
    {
        return nullptr;
    }

    Node* parent = node->parent;
    if (!(node->left || node->right))
    {
        if (!parent)
        {
            root = nullptr;
        }
        else if (parent->left == node)
        {
            parent->left = nullptr;
        }
        else if (parent->right == node)
        {
            parent->right = nullptr;
        }
    }
    else if (node->left && node->right)
    {
        if (!parent)
        {
            root = node->left;
        }
        else if (parent->left == node)
        {
            parent->left = node->left;
        }
        else if (parent->right == node)
        {
            parent->right = node->left;
        }

        Node* rightmostOfLeftTree = node->left;
        while (rightmostOfLeftTree->right)
        {
            rightmostOfLeftTree = rightmostOfLeftTree->right;
        }
        rightmostOfLeftTree->right = node->right;
        node->right->parent = rightmostOfLeftTree;
        //rightmostOfLeftTree->updateMinMax();
    }
    else if (node->left)
    {
        if (!parent)
        {
            root = node->left;
        }
        else if (parent->left == node)
        {
            parent->left = node->left;
            node->left->parent = parent;
        }
        else if (parent->right == node)
        {
            parent->right = node->left;
            node->left->parent = parent;
        }
    }
    else if (node->right)
    {
        if (!parent)
        {
            root = node->right;
        }
        else if (parent->left == node)
        {
            parent->left = node->right;
            node->right->parent = parent;
        }
        else if (parent->right == node)
        {
            parent->right = node->right;
            node->right->parent = parent;
        }
    }

    //parent->updateMinMax();
    delete node;
    if (root)
        root->parent = nullptr;
    return (parent ? parent : nullptr);
}

string AbstractTree::inOrderTraversalString()
{
    stringstream traversal_output;
    vector<uint64_t> traversal_vector;
    inOrderTraversal(traversal_vector);
    copy(traversal_vector.begin(), traversal_vector.end(), ostream_iterator<uint64_t>(traversal_output));
    return traversal_output.str();
}
