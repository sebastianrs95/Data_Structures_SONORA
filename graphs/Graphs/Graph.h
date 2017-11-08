#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include "NodeList.h"
#include "ArcList.h"
#include "routeList.h"

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
            \param newLength The length between the nodes.
        */
        void addArc(int firstNode, int secondNode, float newLength);


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
        void printShortestRoute(){ L.print(); }

        bool getRouteExists(){return routeExists; }


    private:
        NodeList A;
        RouteList L;
        bool routeExists;

};

Graph::Graph()
{
    A.renew();
    routeExists = false;
}

Graph::~Graph()
{
}

void Graph::addArc(int firstNode, int secondNode, float newLength)
{
    Node * temp, * temp2;
    arcNode * tempArc;

    A.add(firstNode);
    temp = A.getLastNodeAdded();
    temp->outgoing.add(secondNode);
    tempArc = temp->outgoing.getLastNodeAdded();

    tempArc->length = newLength;

    A.add(secondNode);
    temp2 = A.getLastNodeAdded();

    tempArc->nodeAddress = temp2;
    temp2->incoming.add(firstNode);
    tempArc = temp2->incoming.getLastNodeAdded();
    tempArc->length = 0;
    tempArc->nodeAddress = temp;
}

void Graph::getShortestRoute(int startNode, int endNode)
{
    Node* p;
    arcNode* q;

    A.add(startNode);
    p = A.getLastNodeAdded();

    p->shortestRoute = 0;

    while(p)
    {
        //cout << "p is: " << p->numNode << endl;
        p->flag = 2;
        if(p->numNode == endNode)
        {

            routeExists = true;
            L.renew();

            while(p)
            {
                L.add(p, p->shortestRoute);
                p = p->predecessor;
            }
            return;
        }

        q = p->outgoing.getFirstNode();
        while(q)
        {
            //cout << "q is: " << q->numNode << endl;

            if(q->nodeAddress->flag == 0)
            {
                q->nodeAddress->flag = 1;

                q->nodeAddress->shortestRoute = p->shortestRoute + q->length;
                q->nodeAddress->predecessor = p;
                L.add(q->nodeAddress, p->shortestRoute + q->length);
                q->nodeAddress->address = L.getLastNodeAdded();
            }
            else
            {
                // if the new route is shorter than the one we had before
                if(q->nodeAddress->flag == 1 && p->shortestRoute + q->length < q->nodeAddress->shortestRoute)
                {
                    q->nodeAddress->shortestRoute = p->shortestRoute + q->length;
                    q->nodeAddress->predecessor = p;
                    L.adjust(q->nodeAddress->address, p->shortestRoute + q->length);
                }
            }
            /*
            L.print();
            cout << endl;
            system("pause");
            */
            q = q->next;

        } // end of while(q)
        p = L.getFirstNode();
    } // end of while(p)
}


void Graph::print()
{
    A.print();
}


#endif // GRAPH_H_INCLUDED
