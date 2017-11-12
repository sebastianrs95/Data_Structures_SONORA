#ifndef NODE_H_INCLUDED
#define NODE_H_INCLUDED

struct node {

    int value;
    node * rChild, * lChild, * parent, * previous, * next;
};


#endif // NODE_H_INCLUDED
