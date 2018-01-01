#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include "pruebas.h"
#include "TreeNode.h"
#include "BPTree.h"


using namespace std;

int main()
{
    BPTree bp;

    bp.add(23);
    bp.print();

    bp.add(45);
    bp.print();

    bp.add(11);
    bp.print();

    bp.add(3);
    bp.print();


    bp.add(3);
    bp.print();

    bp.add(21);
    bp.print();

    bp.add(50);
    bp.print();

    bp.add(40);
    bp.print();

    bp.add(15);
    bp.print();

    bp.add(8);
    bp.print();


    bp.add(5);
    bp.print();

    bp.add(60);
    bp.print();

    bp.add(70);
    bp.print();

    bp.add(20);
    bp.print();

    bp.add(18);
    bp.print();

    bp.add(49);
    bp.print();

    bp.deleteValue(50);
    bp.print();

    bp.deleteValue(60);
    bp.print();

    bp.deleteValue(40);
    bp.print();


    return 0;
}
