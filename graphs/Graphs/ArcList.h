#ifndef ARCLIST_H_INCLUDED
#define ARCLIST_H_INCLUDED

#include <cstdlib>
using std::cout;

enum { EMPTY = 0, BEGINNING, BETWEEN, END };

struct arcNode
{
    int numNode;
    arcNode * next;
};

class ArcList
{


    public:

        ArcList();
        ~ArcList();

        void renew();
        void clear();

        bool searchNode(int value);
        int add(int value);
        int remove(int value);

        arcNode * getLastNodeAdded();
        void print();

    private:

        arcNode * firstNode, * lastNode, * previousNode, * lastNodeAdded;
        bool found;
        int where;
};


ArcList::ArcList()
{
    firstNode = lastNode = previousNode = lastNodeAdded = NULL;
    found = false;
    where = EMPTY;
}


ArcList::~ArcList()
{
    arcNode * temp;

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

void ArcList::renew()
{
    firstNode = lastNode = previousNode = lastNodeAdded = NULL;
    found = false;
    where = EMPTY;
}

void ArcList::clear()
{
    arcNode * temp;

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

bool ArcList::searchNode(int value)
{
    arcNode * temp;
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

int ArcList::add(int value)
{
    arcNode * temp;
    found = searchNode(value);
    if( found )
    {
        //lastNodeAdded = previousNode->next;
        return 0;
    }

    temp = (arcNode*) malloc(sizeof(arcNode));
    temp->numNode = value;
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

int ArcList::remove(int value)
{
    arcNode * temp;
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

    free(temp);
    return 1;
}


/***************************************************************************************/

arcNode * ArcList::getLastNodeAdded()
{
    return lastNodeAdded;
}

/***************************************************************************************/

void ArcList::print()
{
    arcNode * temp;

    temp = firstNode;
    while(temp)
    {
        cout << temp->numNode << " ";
        temp = temp->next;
    }
}

#endif // ARCLIST_H_INCLUDED
