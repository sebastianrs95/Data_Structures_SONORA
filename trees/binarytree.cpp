#include "binarytree.h


BinaryTree::BinaryTree()
{
    root = firstNode = endNode = NULL;
    found = false;
    int placement = EMPTY;
    where = NULL;
}

void BinaryTree::search(int value)
{
    node * p;
    p = root;

    if(p == NULL)
    {
        found = false;
        placement = EMPTY;
        where = NULL;
        return;
    }

    while(p)
    {
        if(p->value == value)
        {
            found = true;
            return;
        }
        else if (p->value < a )
        {
            placement = RCHILD;
            where = p;
            p = p->rChild;
        }
        else
        {
            placement = LCHILD;
            where = p;
            p = p->lChild;
        }

    }   // end of while(p)

    found = false;
    return;
}
    void exchange();
    int add(int);
    void remove(int);
    void print();
