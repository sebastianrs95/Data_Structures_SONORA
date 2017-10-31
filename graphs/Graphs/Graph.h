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


        void getShortestRoute(int startNode, int endNode);


    private:
        NodeList A;
        RouteList L;
        bool routeExists;

};

Graph::Graph()
{
    A.renew();
}

Graph::~Graph()
{
}

void Graph::addArc(int firstNode, int secondNode)
{
    Node * temp, * temp2;
    arcNode * tempArc;

    A.add(firstNode);
    temp = A.getLastNodeAdded();
    temp->outgoing.add(secondNode);
    tempArc = temp->outgoing.getLastNodeAdded();

    A.add(secondNode);
    temp2 = A.getLastNodeAdded();

    tempArc->nodeAddress = temp2;
    temp2->incoming.add(firstNode);
    tempArc = temp2->incoming.getLastNodeAdded();
    tempArc->nodeAddress = temp;
}

void Graph::getShortestRoute(int startNode, int endNode)
{
    Node* p;
    arcNode* q;

    A.add(startNode);
    p = A.getLastNodeAdded();

    while(p)
    {
        p->flag = 2;
        if(p->numNode == endNode)
        {
            routeExists = true;

        }
    }
}


void Graph::print()
{
    A.print();
}


#endif // GRAPH_H_INCLUDED
