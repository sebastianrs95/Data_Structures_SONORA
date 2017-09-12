#ifndef QUEUE_H
#define QUEUE_H
#include "Node.h"

class Queue
{
    public:
        Queue();
        ~Queue();

        void push( int value );
        int pop();

        void print();
        unsigned int size(){ return numElements; }
        bool empty();

    private:

        Node * startNode, * endNode;
        unsigned int numElements;
};

#endif // QUEUE_H
