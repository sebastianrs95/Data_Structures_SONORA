#include <iostream>
#include "Graph.h"
#include "ArcList.h"
#include "NodeList.h"
#include "routeList.h"

using namespace std;

int main()
{
    Graph G;

    G.addArc(1,2);

    G.addArc(1,3);
    G.addArc(1,4);
    G.addArc(2,3);
    //G.addArc(4,3);
    G.addArc(3,4);
    G.addArc(4,5);
    G.addArc(5,7);
    G.addArc(6,7);
    G.addArc(2,6);
    G.addArc(3,5);
    G.addArc(3,6);

    G.print();


    /*
    //ArcList l;
    NodeList l;
    l.add(3);
    l.add(1);
    l.add(2);

    l.oldPrint();
    l.add(-9);
    cout << endl;
    l.oldPrint();
    cout << endl;
    */

    return 0;
}
