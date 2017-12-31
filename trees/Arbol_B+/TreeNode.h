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

    TreeNode(){ isLeaf = false; data.clear(); children.clear() ;}
    ~TreeNode(){}
    void addNode(Node* newNode);
    void print();
    bool checkLeaf(){ return isLeaf; }
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
