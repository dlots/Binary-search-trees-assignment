#ifndef SEMINAR_LAB2_ABSTRACT_TREE_H
#define SEMINAR_LAB2_ABSTRACT_TREE_H

#include <cinttypes>
#include <string>
#include <vector>

using namespace std;


struct Node
{
    explicit Node(uint64_t key) :
            key(key),
            //max(key),
            //min(key),
            priority(0),
            left(nullptr),
            right(nullptr),
            parent(nullptr),
            height(1)
    {
    }

    Node(uint64_t key, uint64_t priority) :
            key(key),
            //max(key),
            //min(key),
            priority(priority),
            left(nullptr),
            right(nullptr),
            parent(nullptr),
            height(1)
    {
    }

    /*void updateMinMax()
    {
        if (left)
        {
            if (left->min < min)
            {
                min = left->min;
            }
            if (left->max > max)
            {
                max = left->max;
            }
        }
        if (right)
        {
            if (right->min < min)
            {
                min = right->min;
            }
            if (right->max > max)
            {
                max = right->max;
            }
        }
        if (parent)
        {
            parent->updateMinMax();
        }
    }*/

    Node* left;
    Node* right;
    Node* parent;
    uint64_t key;
    uint64_t priority;
    int64_t height;

    /*uint64_t max;
    uint64_t min;*/
};

typedef pair<Node*, Node*> SplitResult;

class AbstractTree
{
public:

    AbstractTree() :
        root(nullptr),
        min(UINT64_MAX),
        max(0)
    {
    }

    ~AbstractTree()
    {
        clear();
    }

    virtual Node* search(uint64_t key);
    Node* successor(uint64_t key);
    Node* predecessor(uint64_t key);
    Node* getKthStatistic(uint64_t k);
    void inOrderTraversal(vector<uint64_t>& traversal_vector);
    string inOrderTraversalString();

    uint64_t getMax() { return max; }
    uint64_t getMin() { return min; }

    virtual Node* insert(uint64_t key);
    virtual Node* remove(uint64_t key);

    virtual SplitResult split(Node* tree, uint64_t key) = 0;
    virtual Node* merge(Node* tree1, Node* tree2) = 0;

    void clear();
    Node* getRoot() { return root; }

private:
    void successor(Node* node, uint64_t key, Node*& succ);
    void predecessor(Node* node, uint64_t key, Node*& pred);
    Node* getKthStatistic(Node* node, uint64_t& k);

protected:
    Node* insert(Node* node, uint64_t key);
    Node* remove(Node* node);
    Node* search(Node* node, uint64_t key);

    Node* root;
    uint64_t min;
    uint64_t max;
};


#endif //SEMINAR_LAB2_ABSTRACT_TREE_H
