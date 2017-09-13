#include <iostream>
#include "Stack.h"
#include "Queue.h"
#include <string>

using namespace std;

int main()
{
    Stack<char*> s;
    Queue<char*> q;
    int numElements = 10;

    string str;

    str.append("hey");
    for( int i = 0 ; i < numElements ; ++i )
    {
        q.push("are you a guy?");
        //q.push("a guy?");
    }


    q.print();

    cout << endl << endl << "Popping the first element: " << q.pop() << endl;

    cout << endl << "printing again with size: " << q.size() << endl;
    q.print();


    return 0;
}
