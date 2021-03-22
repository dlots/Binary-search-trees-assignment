#ifndef SEMINAR_LAB2_SPLAY_TREE_H
#define SEMINAR_LAB2_SPLAY_TREE_H

#include "AbstractTree.h"


class SplayTree : public AbstractTree
{
public:
    Node* search(uint64_t key) override;
    SplitResult split(Node* tree, uint64_t key) override;
    Node* merge(Node* tree1, Node* tree2) override;
    Node* insert(uint64_t key) override;
    Node * remove(uint64_t key) override;

private:
    void splay(Node* node);
    //right rotation
    static void rotate_left(Node* node);
    //left rotation
    static void rotate_right(Node* node);
};


#endif //SEMINAR_LAB2_SPLAY_TREE_H
