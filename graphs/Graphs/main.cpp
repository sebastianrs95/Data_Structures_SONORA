#include <iostream>
#include "Graph.h"


using namespace std;

int main()
{
    Graph G;

    G.addArc(1,3);
    G.addArc(2,4);
    G.addArc(5,7);
    G.addArc(6,7);

    G.print();
    return 0;
}
