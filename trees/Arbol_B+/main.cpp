#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include "TreeNode.h"
#include "BPTree.h"


using namespace std;

int main()
{
    BPTree bp;

    bp.readFromFile("add.txt");
    bp.deleteFromFile("delete.txt");

    bp.print();

    return 0;
}
