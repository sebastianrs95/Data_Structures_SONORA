#include <iostream>
#include "Graph.h"
#include "ArcList.h"
#include "NodeList.h"
#include "routeList.h"

using namespace std;

int main()
{
    Graph G;

    G.addArc(1,2,1);
    G.addArc(1,3,2);
    G.addArc(1,4,2);

    G.addArc(2,3,4);
    G.addArc(2,5,1);

    G.addArc(3,4,1);
    G.addArc(3,5,7);
    G.addArc(3,6,2);

    G.addArc(4,6,1);

    G.addArc(5,7,1);

    G.addArc(6,5,3);
    G.addArc(6,7,2);


    //G.print();

    int firstNode, secondNode;
    cout << "Enter the first node's tag: ";
    cin >> firstNode;

    cout << endl << endl << "Enter the second node's tag: ";
    cin >> secondNode;
    G.getShortestRoute( firstNode, secondNode );

    if(G.getRouteExists())
    {
        cout << "The shortest route between node " << firstNode << " and " << secondNode << " is:" << endl;
        G.printShortestRoute();
    }


/*

    RouteList l;

    Node * example = new Node;
    example->numNode = 8;

    l.add(NULL, 2);

    l.add(NULL, 1);
    l.add(example, 5);

    example->address = l.getLastNodeAdded();

    l.add(NULL, 4);

    l.add(NULL, 6);
    l.add(NULL, 6);
    l.add(NULL, 3);
    l.add(NULL, 3);


    //l.adjust(example->address, 1);



    l.print();

    */



    return 0;
}
