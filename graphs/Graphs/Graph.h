#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include "NodeList.h"
#include "ArcList.h"

#include <cstdlib>
using std::cout;

class Graph
{
    public:
        Graph();
        ~Graph();

        /**
            \brief Adds an arc to the Graph.
            \param firstNode An integer that represents the number of the first node of the arc.
            \param secondNode An integer that represents the number of the second node of the arc.
        */
        void addArc(int firstNode, int secondNode);


        /**
            \brief Prints the contents of the Graph in the format:
                Node A:
                    Outgoing:
                        B, C.

                    Incoming:
                        D, F.
        */
        void print();

    private:
        NodeList A;

};

Graph::Graph()
{
}

Graph::~Graph()
{
}

void Graph::addArc(int firstNode, int secondNode)
{
    Node * temp;
    A.add(firstNode);
    temp = A.getLastNodeAdded();

    temp->outgoing.add(secondNode);

    A.add(secondNode);
    temp = A.getLastNodeAdded();
    temp->incoming.add(firstNode);

}

void Graph::print()
{
    A.print();
}


#endif // GRAPH_H_INCLUDED
