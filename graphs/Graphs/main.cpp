#include <iostream>
#include "Graph.h"
#include "ArcList.h"
#include "NodeList.h"
#include "routeList.h"

using namespace std;

int main()
{
    Graph G;

    G.addArc(1,2,3);
    G.addArc(1,3,4);

    G.addArc(2,5,6);
    G.addArc(2,6,9);

    G.addArc(3,4,9);
    G.addArc(3,5,8);

    G.addArc(4,5,1);

    G.addArc(5,7,5);
    G.addArc(5,8,2);

    G.addArc(6,9,6);

    G.addArc(7,8,6);

    G.addArc(8,10,9);
    G.addArc(8,9,3);

    G.addArc(9,12,7);

    G.addArc(10,11,8);

    G.addArc(11,12,6);
    G.addArc(11,13,6);

    G.print();

    int firstNode, secondNode;
    cout << "Enter the first node's tag: ";
    cin >> firstNode;

    cout << endl << endl << "Enter the second node's tag: ";
    cin >> secondNode;
    G.getShortestRoute( firstNode, secondNode );

    if(G.getRouteExists())
    {
        system("cls");
        cout << "The shortest route between node " << firstNode << " and " << secondNode << " is:" << endl;
        cout << endl << endl;
        G.printShortestRoute();
        cout << endl << endl << endl;
    }
    else
    {
        system("cls");
        cout << "The route doesn't exist between node " << firstNode << " and " << secondNode << endl;
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
