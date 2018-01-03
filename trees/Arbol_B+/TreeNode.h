#pragma once

#ifndef TREENODE_H_INCLUDED
#define TREENODE_H_INCLUDED

#include <vector>
#include <algorithm>

using std::vector;
using std::cout;

class TreeNode;

struct Node{
    int value;
};


class TreeNode {

    vector<Node*> data;
    vector<TreeNode*> children;
    TreeNode *parent;
    bool isLeaf;
    friend class BPTree;

public:


    /**
        \brief Default constructor
    */
    TreeNode()
    {
        isLeaf = false;
        data.clear();
        children.clear();
        parent = NULL;
    }


    /**
        \brief Destructor
    */
    ~TreeNode()
    {
        Node * p;
        int numElements = data.size();
        for(int i = 0; i < numElements ; ++i)
        {
            p = data.back();
            data.pop_back();
            p = NULL;
        }

        TreeNode * q;
        numElements = children.size();
        for(int i = 0; i < numElements ; ++i)
        {
            q = children.back();
            children.pop_back();
            q = NULL;
        }

        parent = NULL;
        isLeaf = false;
    }


    /**
        \brief Adds a Node to the data (a vector<Node*>).
        \param newNode The Node to be added to data.
    */
    void addNode(Node* newNode);


    /**
        \brief Prints the contents of the data vector.
    */
    void print();


    /**
        \brief Checks itself to see if it is a leaf.
        \return A boolean that indicates if it is a leaf or not.
    */
    bool checkLeaf(){ return isLeaf; }



    /**
        \brief Sets the value of the isLeaf variable.
        \param status The value to be inserted to isLeaf.
    */
    void setLeafStatus(bool status){ isLeaf = status; }

};

void TreeNode::addNode(Node* newNode)
{

    if(data.empty())
    {
        data.push_back(newNode);
    }

    else
    {
        bool isGreater = true;
        int i;

        for( i = 0 ; i < data.size() ; ++i )
        {
            if(newNode->value < data[i]->value) break;
        }

        if(i == data.size()) data.push_back(newNode);      // if the new value is greater than all the preceding ones
        else
        {
            data.insert(data.begin()+i, newNode);
        }
    }
}

void TreeNode::print()
{
    for( int i = 0 ; i < data.size() ; ++i )
    {
        cout << data[i]->value << " ";
    }

    cout<<"\n\n";
}

#endif // TREENODE_H_INCLUDED
