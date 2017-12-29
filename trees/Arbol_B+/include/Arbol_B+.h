#ifndef ARBOL_B+_H_INCLUDED
#define ARBOL_B+_H_INCLUDED

class BPTree {

public:

    bool search(int value);
    bool add(int value);

private:
    TreeNode * root, * where;
    int n;  // tree's degree, which is the maximum number of data per node
};

bool BPTree::search(int value)
{
    treeNode * temp = root;
    Node * aux;

    while( !temp->isLeaf )
    {
        aux = temp->searchNode(value);
        if(value < aux->reference->value ) temp = aux->lChild;
        else temp = aux->rChild;
    }

    where = temp;
    return temp->search(value);
}

bool BPTree::add(int value)
{
    if(search(value)) return true;

    where->add(value);
    Node * temp;
    if( where->size > n )
    {
        temp = where->divideNode();
        where->addNode(temp);
        newParent = where->
    }
}

#endif // ARBOL_B+_H_INCLUDED
