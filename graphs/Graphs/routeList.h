#ifndef ROUTELIST_H_INCLUDED
#define ROUTELIST_H_INCLUDED

#include <cstdlib>
using std::cout;

//enum { EMPTY = 0, BEGINNING, BETWEEN, END };

struct Node;
/**
    \brief A doubly-linked list, that is sorted and doesn't allow for repetition.
*/
template <typename T>
class RouteList
{
    struct routeNode
    {
        T length;
        Node * address;
        routeNode * next, * previous;
    };

public:

    /**
        \brief Basic constructor for the Doubly-Linked List.
    */
    RouteList();

    /**
        \brief Basic destructor fo the Doubly-Linked List.
    */
    ~RouteList();

    /**
        \brief Searches for the value provided, in each Node inside the Doubly-Linked List.
                It changes the FOUND attribute.
        \param a A variable of type T that will be added to the doubly-linked list.
    */
    bool searchNode(T value);


    /**
        \brief This method adds a new value (inside a Node struct) to the doubly-linked list.
        \param a A variable of type Node* that represents an address pointint to a node in the Graph.
        \param a A variable of type T that will be added to the doubly-linked list.
        \return An integer that indicates success (1) or failure (0).
    */
    int add(Node * address, T value);


    /**
        \brief This method removes a Node from the doubly-linked list (the one holding the provided value).
        \param a A variable of type T that will be removed from the doubly-linked list.
        \return An integer that indicates success (1) or failure (0).
    */
    int remove(T a);



    /**
        \brief Prints the contents of the sorted list.
    */
    void print();


    /**

        \brief Returns the number of elements in the Doubly-Linked List.
        \return The number of elements in the doubly-linked list.
    */
    int size(){ return numElements; }

private:

    routeNode * firstNode, * lastNode, * previousNode;
    bool found;
    int where, numElements;

};


/***************************************************************************************/
template <typename T>
RouteList<T>::RouteList()
{
    previousNode = firstNode = lastNode = NULL;
    found = false;
    where = numElements = 0;
}


/***************************************************************************************/

template <typename T>
RouteList<T>::~RouteList()
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

template <typename T>
bool RouteList<T>::searchNode(T value)
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

template <typename T>
int RouteList<T>::add(Node * address, T value)
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
            temp->next = firstNode;
            firstNode = temp;
            temp->previous = NULL;
            temp->next->previous = temp;
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
                    previousNode->next = temp;
                    temp->previous = previousNode;
                    lastNode = temp;
                }
            }
        }
    }
    ++numElements;
    return 1;
}


/***************************************************************************************/

template <typename T>
int RouteList<T>::remove(T value)
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
    free(temp);
    return 1;

}


/***************************************************************************************/

template <typename T>
void RouteList<T>::print()
{
    routeNode * temp;

    temp = firstNode;
    while(temp)
    {
        cout << temp->length << " ";
        temp = temp->next;
    }
}


#endif // ROUTELIST_H_INCLUDED
