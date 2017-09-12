#include <iostream>
#include "Stack.h"
#include "Queue.h"

using namespace std;

int main()
{
    Stack q;
    Queue s;
    int numElements = 10;
    for( int i = 0 ; i < numElements ; ++i )
    {
        q.push(i);
    }

    q.push(100);
    q.push(10000);
    q.push(1);
    q.push(1000000);

    q.print();

    cout << endl << endl << "Popping the first element: " << q.pop() << endl;

    cout << endl << "printing again with size: " << q.size() << endl;
    q.print();


    return 0;
}
