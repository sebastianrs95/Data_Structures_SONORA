#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
using namespace std;

template <typename T>
class Stack
{

    struct Node
    {
        Node * next;
        T value;
    };

public:

    Stack()
    {
        topNode = NULL;
        numElements = 0;
    }
    ~Stack()
    {
        while(!empty()) pop();
    }


    void push( T value );
    T pop();
    T top();
    unsigned short size();
    bool empty();

    void print();

private:
    int numElements;
    Node * topNode;
};

/***************************************************************************************************************/

template <typename T>
void Stack<T>::push( T value )
{
    Node * newNode;
    newNode = new Node;
    newNode->value = value;

    if(empty())
    {
       topNode = newNode;
       topNode->next = NULL;
       ++numElements;
    }
    else
    {
        newNode->next = topNode;
        topNode = newNode;
        ++numElements;
    }
}


/***************************************************************************************************************/

template <typename T>
T Stack<T>::pop()
{
    T value;
    if( empty() )
    {
        throw 0;
    }
    else
    {
        Node * temp;

        temp = topNode;
        topNode = topNode->next;

        value = temp->value;
        temp->next = NULL;
        temp->value = 0;

        free(temp);
        --numElements;
    }
    return value;
}


/***************************************************************************************************************/

template <typename T>
T Stack<T>::top()
{
    if( empty() ) return 999999999;
    else return topNode->value;
}


/***************************************************************************************************************/

template <typename T>
unsigned short Stack<T>::size()
{
    return numElements;
}


/***************************************************************************************************************/

template <typename T>
bool Stack<T>::empty()
{
    if( numElements == 0 ) return true;
    else return false;
}


/***************************************************************************************************************/

template <typename T>
void Stack<T>::print()
{
    if(empty()) return;


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

    Node * temp;
    temp = topNode;

    const int WIDTH = 10;
    cout << char(218);  // top left angle
    for( int i = 0 ; i < WIDTH ; ++i ) cout << char(196);   // horizontal bar
    cout << char(191) << endl;  // top right angle

    if( numElements == 1 )
    {
        cout << char(179) << setw(WIDTH) << temp->value << char(179) << endl; // vertical bar
        cout << char(192);
        for( int i = 0 ; i < WIDTH ; ++i ) cout << char(196);
        cout << char(217);
    }
    else
    {

        for( int i = 0 ; i < numElements-1 ; ++i )
        {

            cout << char(179) << setw(WIDTH) << temp->value << char(179) << endl;
            cout << char(195); // left joining bar
            for( int j = 0 ; j < WIDTH ; ++j ) cout << char(196);
            cout << char(180) << endl; // right joining bar
            temp = temp->next;
        }

        cout << char(179) << setw(WIDTH) << temp->value << char(179) << endl;
        cout << char(192);
        for( int i = 0 ; i < WIDTH ; ++i ) cout << char(196);
        cout << char(217);
    }
}

#endif // STACK_H_INCLUDED
