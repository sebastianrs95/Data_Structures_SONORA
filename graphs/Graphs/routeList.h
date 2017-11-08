#ifndef ROUTELIST_H_INCLUDED
#define ROUTELIST_H_INCLUDED

#include <cstdlib>
using std::cout;

//enum { EMPTY = 0, BEGINNING, BETWEEN, END };

struct Node;
/**
    \brief A doubly-linked list, that is sorted and doesn't allow for repetition.
*/

struct routeNode
{
    float length;
    Node * address;
    routeNode * next, * previous;
};

class RouteList
{


public:

    /**
        \brief Basic constructor for the Doubly-Linked List.
    */
    RouteList();

    /**
        \brief Basic constructor for the Doubly-Linked List.
    */
    void renew();

    /**
        \brief Basic destructor fo the Doubly-Linked List.
    */
    ~RouteList();

    /**
        \brief Searches for the value provided, in each Node inside the Doubly-Linked List.
                It changes the FOUND attribute.
        \param a A variable of type T that will be added to the doubly-linked list.
    */
    bool searchNode(float value);


    /**
        \brief This method adds a new value (inside a Node struct) to the doubly-linked list.
        \param a A variable of type Node* that represents an address pointint to a node in the Graph.
        \param a A variable of type T that will be added to the doubly-linked list.
        \return An integer that indicates success (1) or failure (0).
    */
    int add(Node * address, float value);


    /**
        \brief This method removes a Node from the doubly-linked list (the one holding the provided value).
        \param a A variable of type T that will be removed from the doubly-linked list.
        \return An integer that indicates success (1) or failure (0).
    */
    int remove(float a);



    /**
        \brief Prints the contents of the sorted list.
    */
    void print();


    /**
        \brief Prints the shortest route.
    */
    void printShortestRoute();


    /**

        \brief Returns the number of elements in the Doubly-Linked List.
        \return The number of elements in the doubly-linked list.
    */
    int size(){ return numElements; }


    /**
        \brief Returns the pointer to the Node contained in the first routeNode of the Doubly-Linked List.
        \return The pointer to the Node contained in the first routeNode of the Doubly-Linked List.
    */
    Node * getFirstNode();


    /**
        \brief Returns the pointer to the last routeNode added.
        \return The pointer to the last routeNode added.
    */
    routeNode * getLastNodeAdded(){ return lastNodeAdded; }

    /**
        \brief Adjusts the length of a routeNode with the parameter provided.
        \param addressNode A pointer to a routeNode which length is to be changed.
        \param shortRoute The length to replace the old one.
    */
    void adjust(routeNode * addressNode, float shortRoute);

private:

    routeNode * firstNode, * lastNode, * previousNode, *lastNodeAdded;
    bool found;
    int where, numElements;

};


/***************************************************************************************/

RouteList::RouteList()
{
    previousNode = firstNode = lastNode = lastNodeAdded = NULL;
    found = false;
    where = numElements = 0;
}


/***************************************************************************************/

void RouteList::renew()
{
    previousNode = firstNode = lastNode = lastNodeAdded = NULL;
    found = false;
    where = numElements = 0;
}


/***************************************************************************************/

RouteList::~RouteList()
{
    routeNode * temp;

    while(firstNode != NULL)
    {
        temp = firstNode;
        firstNode = temp->next;
        free(temp);
    }

    previousNode = firstNode = lastNode = NULL;
    found = false;
    where = numElements = 0;
}


/***************************************************************************************/

bool RouteList::searchNode(float value)
{
    routeNode * temp;
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
            if( temp->length == value )      // if the value is already at the beginning, mark the position
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
                if( temp->length > value )
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

int RouteList::add(Node * address, float value)
{
    routeNode * temp;
    found = searchNode(value);


    //if(found) return 0;
    temp = (routeNode*) malloc(sizeof(routeNode));
    temp->length = value;
    temp->address = address;

    if(where == EMPTY)
    {
        temp->next = NULL;
        temp->previous = NULL;
        firstNode = temp;
        lastNode = temp;
    }
    else
    {
        if( where == BEGINNING )
        {
            if(temp->length == firstNode->length && numElements > 1)
            {
                firstNode->next->previous = temp;
                temp->next = firstNode->next;
                temp->previous = firstNode;
                firstNode->next = temp;
            }
            else
            {
                temp->next = firstNode;
                firstNode = temp;
                temp->previous = NULL;
                temp->next->previous = temp;
            }
        }
        else
        {
            if( where == BETWEEN )
            {
                temp->next = previousNode->next;
                previousNode->next = temp;
                temp->previous = previousNode;
                temp->next->previous = temp;
            }
            else
            {
                if( where == END )
                {

                    temp->next = NULL;
                    lastNode->next = temp;
                    temp->previous = lastNode;
                    lastNode = temp;
                }
            }
        }
    }

    lastNodeAdded = temp;
    ++numElements;
    return 1;
}


/***************************************************************************************/

int RouteList::remove(float value)
{
    routeNode * temp;
    found = searchNode(value);
    if(!found) return 0;
    if( where == BEGINNING)
    {
        temp = firstNode;
        firstNode = temp->next;
        if(firstNode == NULL) lastNode = NULL;
        else firstNode->previous  = NULL;
        numElements--;
        return 1;
    }
    else
    {
        if(where == BETWEEN)
        {
            temp = previousNode->next;
            previousNode->next = temp->next;
            temp->next->previous = previousNode;
        }
        else
        {
            temp = previousNode->next;
            previousNode->next = NULL;
            lastNode = previousNode;
        }
    }
    numElements--;
    free(temp);
    return 1;

}


/***************************************************************************************/

void RouteList::print()
{
    routeNode * temp;

    temp = firstNode;
    while(temp)
    {
        cout << "Node " << temp->address->numNode << ", " << temp->length << " | ";
        //cout << temp->length << " | ";
        temp = temp->next;
    }
}


/***************************************************************************************/

void RouteList::printShortestRoute()
{
    routeNode * temp;
    float length;

    temp = firstNode;
    while(temp)
    {
        cout << "Node " << temp->address->numNode << " -> ";
        //cout << temp->length << " | ";
        length = temp->address->shortestRoute;
        temp = temp->next;
    }
    cout << "\b\b\b   ";
    cout << endl << "with a total length of: " << length;
}


/***************************************************************************************/

Node * RouteList::getFirstNode()
{
    Node * temp = firstNode->address;
    remove(firstNode->length);
    return temp;
}

void RouteList::adjust(routeNode * address, float shortRoute)
{
    address->length = shortRoute;

    routeNode * temp;

    temp = address->previous;
    if(temp == NULL ) return;

    while( address->length < temp->length )    // this is, if the previous routeNode has a greater length, move them
    {
        temp->next = address->next;
        address->next->previous = temp;
        address->next = temp;
        address->previous = temp->previous;
        temp->previous->next = address;
        temp->previous = address;

        temp = address->previous;
        if(temp == NULL) break;
    }
}


#endif // ROUTELIST_H_INCLUDED
