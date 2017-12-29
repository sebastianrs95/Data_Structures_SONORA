#ifndef NODOARBOL_H_INCLUDED
#define NODOARBOL_H_INCLUDED

// esta clase es una lista ordenada
enum WHERE {EMPTY, BEGINNING, BETWEEN, END};


struct Node {

    int value;
    treeNode * lChild, * rChild, *container;
    Node ** reference;
    Node * next, * previous;
};

class TreeNode {
public:

    Node * searchNode(int value);
    bool search(int value);
    int add(int value);
    int remove(int value);
    int size(){ return numElements; }
    Node * divideNode();
    void changeParent (Node *newParent){parent=newParent;}
    Node * getParent(){return (parent);}
    void addNode(Node*);

    Node * getLastNodeAdded(){ return lastNodeAdded; }
    void oldPrint();

private:

    Node * firstNode, * lastNode, * previousNode, * lastNodeAdded, * parent;
    bool found, isLeaf;
    int where, numElements;
};

/***************************************************************************************/

Node * TreeNode::searchNode(int value)
{
    Node * temp = firstNode;
    while( value > temp->reference->value && temp->next != NULL )
        temp = temp->next;

    return temp;
}


/***************************************************************************************/

Node * TreeNode::divideNode()
{
    int middleVal = numElements / 2 + 1;
    TreeNode * leftList, * rightList;
    leftList = (TreeNode*) malloc(sizeof(TreeNode));
    rightList = (TreeNode*) malloc(sizeof(TreeNode));

    Node * temp;
    temp = firstNode;
    for( int i = 1 ; i < middleVal ; ++i )
    {
        leftList.add(temp->value);
        temp = temp->next;
    }

    Node * newNode = (Node*) malloc(sizeof(Node));
    newNode->reference=temp;
    newNode->lChild=leftList;

    for( int i = middleVal ; i < numElements ; ++i )
    {
        rightList.add(temp->value);
        temp = temp->next;
    }

    newNode->rChild=rightList;
    newNode->lChild->changeParent(newNode);
    newNode->rChild->changeParent(newNode);

    return(newNode);
}

/***************************************************************************************/

void TreeNode::addNode(Node*)
{

}

/***************************************************************************************/
bool TreeNode::search(int value)
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

int TreeNode::add(int value)
{
    Node * temp;
    found = searchNode(value);
    if( found ) return 0;

    temp = (Node*) malloc(sizeof(Node));

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

    temp->container = this;

    return 1;
}


/***************************************************************************************/

int TreeNode::remove(int value)
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

void TreeNode::oldPrint()
{
    Node * temp;

    temp = firstNode;
    while(temp)
    {
        cout << temp->numNode << " ";
        temp = temp->next;
    }
}


#endif // NODOARBOL_H_INCLUDED
