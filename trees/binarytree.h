#ifndef BINARYTREE_H_INCLUDED
#define BINARYTREE_H_INCLUDED

#include "node.h"

enum WHERE {EMPTY, ROOT, RCHILD, LCHILD};

class BinaryTree
{
public:
    BinaryTree();
    ~BinaryTree(){};

    void search(int);
    void exchange();
    int add(int);
    void remove(int);
    void print();

private:
    node * root, * firstNode, *endNode;
    bool found;
    int placement;
    node * where;

};

#endif // BINARYTREE_H_INCLUDED
