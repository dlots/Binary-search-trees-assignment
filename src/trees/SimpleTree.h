#ifndef SEMINAR_LAB2_SIMPLE_TREE_H
#define SEMINAR_LAB2_SIMPLE_TREE_H

#include "AbstractTree.h"


class SimpleTree : public AbstractTree
{
    SplitResult split(Node* tree, uint64_t key) override;
    Node* merge(Node* tree1, Node* tree2) override;
};


#endif //SEMINAR_LAB2_SIMPLE_TREE_H
