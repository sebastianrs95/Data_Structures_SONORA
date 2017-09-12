#include "Queue.h"
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
using namespace std;

Queue::Queue()
{
    startNode = NULL;
    endNode = NULL;
    numElements = 0;
}

Queue::~Queue()
{
    while(!empty()) pop();
}

void Queue::push( int value )
{
    Node * newNode;
    newNode = (Node*) malloc( sizeof(Node) );
    newNode->value = value;

    if( empty() )
    {
        newNode->next = NULL;
        startNode = newNode;
        endNode = newNode;
        ++numElements;
    }
    else
    {
        newNode->next = NULL;
        endNode->next = newNode;
        endNode = newNode;
        ++numElements;
    }
}

int Queue::pop()
{
    int value;
    if(empty()) return 999999999;
    else
    {
        Node * temp;

        value = startNode->value;
        temp = startNode;
        startNode = temp->next;
        free(temp);
        --numElements;
        if(empty())
        {
            startNode = NULL;
            endNode = NULL;
        }
    }
    return value;
}

bool Queue::empty()
{
    if( numElements == 0 ) return true;
    else return false;
}


void Queue::print()
{
    /*
        Ascii codes
        Top left angle: 218
        Top right angle: 191
        Vertical Bar:   179
        Vertical left joining bar: 195
        Vertical right joining bar: 180
        Horizontal Bar: 196
        Low left angle: 192
        Low right angle: 217
    */

    if(empty()) return;

    Node * temp = startNode;
    int width;
    string widthString;
    ostringstream stringHolder;

    while(temp)
    {
        stringHolder << temp->value;
        width = stringHolder.str().length();

        cout << endl << char(218);
        for( int i = 0 ; i < width ; ++i ) cout << char(196);
        cout << char(191);

        cout << endl;

        cout << char(179) << setw(width) <<  temp->value << char(179);

        cout << endl << char(192);
        for( int i = 0 ; i < width ; ++i ) cout << char(196);
        cout << char(217);

        //printing the vertical bar in the center of the box
        cout << endl << ' ';        // empty space because of the vertical bar, where the box starts

        cout << '^';
        temp = temp->next;
        stringHolder.str(""); // flush the buffer in every iteration
        stringHolder.clear();
    }
    cout << "\b\b  ";
}
