#ifndef NODELIST_H_INCLUDED
#define NODELIST_H_INCLUDED

#include "ArcList.h"

using std::cout;
using std::endl;

struct Node
{
    int numNode;
    Node * next;
    ArcList incoming, outgoing;
};

class NodeList
{

    public:

        NodeList();
        ~NodeList();

        //new();
        //erase();

        bool searchNode(int value);
        int add(int value);
        int remove(int value);

        Node * getLastNodeAdded();
        void print();

    private:

        Node * firstNode, * lastNode, * previousNode, * lastNodeAdded;
        bool found;
        int where;
};


NodeList::NodeList()
{
    firstNode = lastNode = previousNode = lastNodeAdded = NULL;
    found = false;
    where = EMPTY;
}


NodeList::~NodeList()
{
    Node * temp;

    while(firstNode != NULL)
    {
        temp = firstNode;
        firstNode = temp->next;
        free(temp);
    }

    previousNode = firstNode = lastNode = NULL;
    found = false;
    where = EMPTY;
}

/***************************************************************************************/

bool NodeList::searchNode(int value)
{
    Node * temp;
    temp = firstNode;

    if(!temp)
    {
        where = EMPTY;
        return false;
    }

    else
    {
        while(temp)
        {
            if( temp->numNode == value )      // if the value is already at the beginning, mark the position
            {
                if( firstNode == temp ) where = BEGINNING;
                else
                {
                    if( temp->next == NULL ) where = END;
                    else where = BETWEEN;
                }
                return true;
            }

            else
            {
                if( temp->numNode > value )
                {
                    if( firstNode == temp ) where = BEGINNING;
                    else where = BETWEEN;
                    return false;
                }
                else
                {
                    previousNode = temp;
                    temp = temp->next;
                }
            }
        }
        where = END;
        return false;
    }
}


/***************************************************************************************/

int NodeList::add(int value)
{
    Node * temp;
    found = searchNode(value);
    if( found )
    {
        lastNodeAdded = previousNode->next;
        return 0;
    }
    temp = (Node*) malloc(sizeof(Node));
    temp->numNode = value;
    //temp->outgoing.new();
    //temp->incoming.erase();

    if( where == EMPTY )
    {
        temp->next = NULL;
        firstNode = temp;
    }
    else
    {
        if( where == BEGINNING )
        {
            temp->next = firstNode;
            firstNode = temp;
        }
        else
        {
            if( where == BETWEEN )
            {
                temp->next= previousNode->next;
                previousNode->next = temp;
            }
            else
            {
                if( where == END )
                {
                    temp->next = NULL;
                    previousNode->next = temp;
                }
            }
        }
    }

    lastNodeAdded = temp;

    return 1;
}


/***************************************************************************************/

int NodeList::remove(int value)
{
    Node * temp;
    found = searchNode(value);
    if( found == 0 ) return 0;
    if( where == BEGINNING )
    {
        temp = firstNode;
        firstNode = firstNode->next;
    }
    else
    {
        if( where == BETWEEN )
        {
            temp = previousNode->next;
            previousNode->next = previousNode->next->next;
        }
        else
        {
            temp = previousNode->next;
            previousNode->next = NULL;
        }
    }

    //temp->outgoing.erase();
    //temp->incoming.erase();

    free(temp);
    return 1;
}


/***************************************************************************************/

Node * NodeList::getLastNodeAdded()
{
    return lastNodeAdded;
}

/***************************************************************************************/

void NodeList::print()
{
    Node * node;

    node = firstNode;

    while(node)
    {
        cout << "Node: " << node->numNode << endl;
        cout << "Outgoing:" << endl << "\t";
        node->outgoing.print();

        cout << endl << endl << "Incoming: " << endl << "\t";
        node->incoming.print();

        node = node->next;
    }


}


#endif // NODELIST_H_INCLUDED
