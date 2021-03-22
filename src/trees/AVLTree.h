#ifndef SEMINAR_LAB2_AVL_TREE_H
#define SEMINAR_LAB2_AVL_TREE_H

#include "AbstractTree.h"


class AVLTree : public AbstractTree
{
public:
    Node* insert(uint64_t key) override;
    Node * remove(uint64_t key) override;

    SplitResult split(Node* tree, uint64_t key) override;
    Node* merge(Node* tree1, Node* tree2) override;

private:
    void balanceNode(Node* node, uint64_t key);
    //right rotation
    void rotate_left(Node* node);
    //left rotation
    void rotate_right(Node* node);

    static int64_t height(Node* node);
    static int64_t nodeBalance(Node* node);
};


#endif //SEMINAR_LAB2_AVL_TREE_H
