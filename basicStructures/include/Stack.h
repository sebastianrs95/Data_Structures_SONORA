#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include "Node.h"

class Stack
{

public:

    Stack();
    ~Stack();


    void push( int value );
    int pop();
    int top();
    unsigned short size();
    bool empty();

    void print();

private:
    int numElements;
    Node * topNode;
};

#endif // STACK_H_INCLUDED
