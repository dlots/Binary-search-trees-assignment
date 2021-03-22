#ifndef SEMINAR_LAB2_TREAP_H
#define SEMINAR_LAB2_TREAP_H

#include "AbstractTree.h"
#include "../util/RandomGenerator.h"

#include <random>


class Treap : public AbstractTree
{
public:
    SplitResult split(Node* tree, uint64_t key) override;
    Node* merge(Node* tree1, Node* tree2) override;
    Node* insert(uint64_t key) override;
    Node * remove(uint64_t key) override;
};


#endif //SEMINAR_LAB2_TREAP_H
