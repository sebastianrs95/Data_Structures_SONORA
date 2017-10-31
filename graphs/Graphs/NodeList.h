#ifndef NODELIST_H_INCLUDED
#define NODELIST_H_INCLUDED

#include "ArcList.h"
#include "Node.h"

using std::cout;
using std::endl;

struct routeNode;

struct Node
{
    int numNode;
    float shortestRoute;
    int flag;
    Node * predecessor, * next;
    ArcList incoming, outgoing;
    routeNode * address;
};

class NodeList
{

    public:

        NodeList();
        ~NodeList();

        void renew();
        void clear();

        bool searchNode(int value);
        int add(int value);
        int remove(int value);

        Node * getLastNodeAdded();
        void print();
        void oldPrint();

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

void NodeList::renew()
{
    firstNode = lastNode = previousNode = lastNodeAdded = NULL;
    found = false;
    where = EMPTY;
}

void NodeList::clear()
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
                lastNodeAdded = temp;
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
    if( found ) return 0;

    temp = (Node*) malloc(sizeof(Node));
    temp->numNode = value;
    temp->outgoing.renew();
    temp->incoming.renew();
    //temp->incoming.erase();

    if( where == EMPTY )
    {
        temp->next = NULL;
        lastNodeAdded = temp;
        firstNode = temp;
    }
    else
    {
        if( where == BEGINNING )
        {
            temp->next = firstNode;
            firstNode = temp;
            lastNodeAdded = temp;
        }
        else
        {
            if( where == BETWEEN )
            {
                temp->next= previousNode->next;
                previousNode->next = temp;
                //lastNodeAdded = previousNode->next;
                lastNodeAdded = temp;
            }
            else
            {
                if( where == END )
                {
                    temp->next = NULL;
                    previousNode->next = temp;
                    lastNodeAdded = temp;
                }
            }
        }
    }



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
        cout << endl << endl << endl;
        node = node->next;
    }
}

void NodeList::oldPrint()
{
    Node * temp;

    temp = firstNode;
    while(temp)
    {
        cout << temp->numNode << " ";
        temp = temp->next;
    }
}


#endif // NODELIST_H_INCLUDED
