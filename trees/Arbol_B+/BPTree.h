#ifndef BPTREE_H_INCLUDED
#define BPTREE_H_INCLUDED

#include <queue>
#include <cstdlib>
#include <iostream>
#include <fstream>

using std::queue;

class BPTree
{
    TreeNode * root;
    bool found;
    int degree; // Minimum number of elements on a node

public:

    BPTree(){degree =2; root=NULL;}
    BPTree(int _degree){degree =_degree; root=NULL;}

    ~BPTree()
    {
        queue<TreeNode*> levels;
        TreeNode * p;

        levels.push(root);
        while(!levels.empty())
        {
            if(!levels.front()->checkLeaf())
            {
                for(int i = 0 ; i < levels.front()->children.size() ; ++i)
                {
                    levels.push(levels.front()->children[i]);
                }
                p = levels.front();
                delete p;
                levels.pop();

            }

            else
            {
                p = levels.front();
                delete p;
                levels.pop();
            }
        }
    }

    /**
        \brief  Searches for an element inside the tree.
        \param value The value to be searched inside the tree.
        \return A pointer to the TreeNode that contains such value.
    */
    TreeNode * searchNode(int value);


    /**
        \brief  Searches for an element inside the tree.
        \param value The value to be searched inside the tree.
        \return A boolean that is true if it was found, false otherwise.
    */
    bool searchValue(int value);


    /**
        \brief Method that adds a value to the BPTree
        \param value The value to be added.
    */
    void add(int value);


    /**
        \brief Splits a TreeNode if it is the root, regarding the case.
        \param tNode A pointer to a TreeNode that contains the node to be split.
    */
    void splitRoot(TreeNode *tNode);


    /**
        \brief Splits a TreeNode, regarding the case.
        \param tNode A pointer to a TreeNode that contains the node to be split.
    */
    void split(TreeNode *tNode);


    /**
        \brief Deletes a value from the BPTree, prints a message if it's not there.
        \param value The value to be deleted.
    */
    void deleteValue(int value);


    /**
        \brief Checks if a TreeNode can borrow a value from a sibling, and if it can, it does so.
        \param tNode A pointer to a TreeNode that contains the node that will try to borrow.
        \return A boolean that indicates whether it could borrow or not.
    */
    bool borrow(TreeNode *tNode);


    /**
        \brief Merges a node, regarding its case.
        \param tNode A pointer to a TreeNode that contains the node to be merged.
        \return A pointer to the TreeNode that was just merged.
    */
    TreeNode* mergeNodes(TreeNode *tNode);


    /**
        \brief Prints the contents of the leaves.
    */
    void print();


    /**
        \brief Reads data from a file, and then it inserts it to the BPTree.
        \param filename A string that contains the file to be read.
    */
    void readFromFile( const char * filename );


    /**
        \brief Reads data from a file, and then it deletes it from the BPTree.
        \param filename A string that contains the file to be read.
    */
    void deleteFromFile( const char * filename );

    /**
        \brief
        \param
    */
    void saveToFile ( const char * filename);

};


bool BPTree::searchValue(int value)
{
    if(!root)
    {
        return false;
    }

    TreeNode *temp;
    temp = root;
    int i;
    while(!temp->isLeaf)
    {
        i=0;
        for(; i<temp->data.size();i++)
        {
            if(value<temp->data[i]->value)break;
            if(value==temp->data[i]->value)
            {
                i++;
                break;
            }
        }
        temp= temp->children[i];
    }

    for(i=0; i<temp->data.size();i++)
    {
        if(value==temp->data[i]->value)
        {
            return true;
        }
    }

    return false;
}

TreeNode * BPTree::searchNode(int value)
{
    if(!root)
    {
        found=false;
        return (NULL);
    }

    TreeNode *temp;
    temp = root;
    int i;
    while(!temp->isLeaf)
    {
        i=0;
        for(; i<temp->data.size();i++)
        {
            if(value < temp->data[i]->value)break;
            if(value == temp->data[i]->value)
            {
                i++;
                break;
            }
        }
        temp = temp->children[i];
    }

    for(i=0; i<temp->data.size();i++)
    {
        if(value == temp->data[i]->value)
        {
            found = true;
            return(temp);
        }
    }

    found = false;
    return(temp);
}


//******************************************************************

void BPTree::add(int value)
{
    TreeNode *temp = searchNode(value);
    if(found) return;

    Node *aux;
    aux= (Node*)malloc(sizeof(Node));
    aux->value = value;

    if(!root)
    {
        temp = new TreeNode;
        temp->isLeaf = true;
        temp->data.clear();
        temp->data.push_back(aux);
        root=temp;
        return;
    }

    int i;
    for(i=0; i<temp->data.size();i++)
    {
        if(value < temp->data[i]->value) break;
    }
    temp->data.insert(temp->data.begin()+i, aux);

    while(temp->data.size() == 2*degree+1)
    {
       if(temp==root) splitRoot(temp);
       else split(temp);
       temp = temp->parent;
       if(!temp) break;
    }

}


//***************************************************************

void BPTree::splitRoot(TreeNode *tNode)
{
    TreeNode *temp;
    temp=tNode;

    TreeNode *auxP, *auxR; //auxP is the new parent, auxR is the new right child
    auxP= new TreeNode;
    auxR= new TreeNode;

    if(temp->isLeaf)
    {
        int midVal = temp->data[degree]->value;

        for(int i=degree; i<temp->data.size();i++)
        {
            auxR->data.push_back(temp->data[i]);
        }

        int auxSize = temp->data.size();

        //we made a for with the same number of iterations than the last for
        for(int i=degree; i < auxSize;i++)
        {
            temp->data.pop_back();  //delete the elements that are copied in auxR
        }

        Node *newNode;
        newNode=(Node*)malloc(sizeof(Node));
        newNode->value = midVal;
        auxP->data.push_back(newNode);
        auxP->children.push_back(temp);
        auxP->children.push_back(auxR);
        temp->parent = auxP;
        auxR->parent = auxP;

        auxR->isLeaf = true;
        auxP->isLeaf = false;
        root = auxP;
    }
    //In case the node is not a leaf
    else
    {

        Node *newNode;
        newNode=temp->data[degree];
        auxR->children.push_back(temp->children[degree+1]);
        for(int i=degree+1; i<temp->data.size();i++)
        {
            auxR->data.push_back(temp->data[i]);
            auxR->children.push_back(temp->children[i+1]);
        }

        //we made a for with the same number of iterations that the last for
        int auxSize = temp->data.size();
        for(int i=degree, j=0; i<auxSize;i++, j++)
        {
            temp->data.pop_back();//delete the n elements that are copied in auxR
            temp->children.pop_back(); //deletes n children copied in auxR
            auxR->children[j]->parent=auxR;
        }

        auxP->data.push_back(newNode);
        auxP->children.push_back(temp);
        auxP->children.push_back(auxR);
        temp->parent=auxP;
        auxR->parent=auxP;

        auxR->isLeaf=false;
        auxP->isLeaf=false;
        root = auxP;
    }
}


//*********************************************************************************************************

void BPTree::split(TreeNode *tNode)
{
    TreeNode *temp;
    temp=tNode;

    TreeNode  *auxR;    //auxP is the new parent, auxR is the new right child
    auxR= new TreeNode;

    if(temp->isLeaf)
    {
        int midVal = temp->data[degree]->value;

        for(int i=degree; i<temp->data.size();i++)
        {
            auxR->data.push_back(temp->data[i]);
        }

        int auxSize = temp->data.size();

        //we made a for with the same number of iterations than the last for
        for(int i=degree; i < auxSize;i++)
        {
            temp->data.pop_back();  //delete the elements that are copied in auxR
        }

        Node *newNode;
        newNode=(Node*)malloc(sizeof(Node));
        newNode->value=midVal;

        int i;
        for(i=0; i<temp->parent->data.size();i++)
        {
            if(newNode->value < temp->parent->data[i]->value) break;
        }
        temp->parent->data.insert(temp->parent->data.begin()+i, newNode);
        temp->parent->children.insert(temp->parent->children.begin()+i+1, auxR);


        auxR->parent = temp->parent;

        auxR->isLeaf=true;
    }

    //In case the node is not a leaf
    else
    {

        Node *newNode;
        newNode=temp->data[degree];
        auxR->children.push_back(temp->children[degree+1]);

        //insert the last n elements and children of temp into auxR
        for(int i=degree+1; i<temp->data.size();i++)
        {
            auxR->data.push_back(temp->data[i]);
            auxR->children.push_back(temp->children[i+1]);
        }
        //we made a for with the same number of iterations that the last for to eliminate from temp
        int auxSize = temp->data.size();
        for(int i=degree, j=0; i<auxSize;i++, j++)
        {
            temp->data.pop_back();//delete the n elements that are copied in auxR
            temp->children.pop_back(); //deletes n children copied in auxR
            auxR->children[j]->parent = auxR;
        }

        int i;
        for(i=0; i<temp->parent->data.size();i++)
        {
            if(newNode->value < temp->parent->data[i]->value) break;
        }

        temp->parent->data.insert(temp->parent->data.begin()+i, newNode);
        temp->parent->children.insert(temp->parent->children.begin()+i+1, auxR);
        auxR->parent = temp->parent;
        auxR->isLeaf = false;
    }
}

//****************************************************************************************

void BPTree::deleteValue(int value)
{
    TreeNode *temp;
    TreeNode *auxReference;
    temp= searchNode(value);

    if(!found)
    {
        std::cout<<"The element "<<value<<" is not on the tree\n\n";
        return;
    }

    int i;
    for(i=0; i < temp->data.size();i++)
    {
        if(value == temp->data[i]->value)break;
    }
    temp->data.erase(temp->data.begin()+i);


    bool couldBorrow; //aux variable for the while
    couldBorrow = false;
    while(!couldBorrow && (temp->data.size()<degree))
    {
        couldBorrow = borrow(temp);
        if(!couldBorrow)
        {
            temp = mergeNodes(temp);
        }//call merge

        if (temp==root || temp->parent==root) return;
        temp = temp->parent;
    }
    return;
}


//****************************************************************************************

bool BPTree::borrow(TreeNode *tNode) //tNode is the child that need to borrow
{
    TreeNode *temp;
    temp = tNode;
    int indexChildren;
    indexChildren = temp->parent->children.size()-1;

    if(temp->parent->children[indexChildren]->data[0]->value==temp->data[0]->value) // last right children
    {
       if(temp->parent->children[indexChildren-1]->data.size() <= degree) return false; //check if the node that will borrow has n+1 elements, if not return false to merge
       if(temp->isLeaf)
       {
           temp->data.insert(temp->data.begin(), temp->parent->children[indexChildren-1]->data.back());
           temp->parent->data.back()->value= temp->parent->children[indexChildren-1]->data.back()->value;
           temp->parent->children[indexChildren-1]->data.pop_back();
       }
       else     //case treeNode temp isn't leaf
       {
           temp->data.insert(temp->data.begin(),temp->parent->data.back());
           temp->parent->data.pop_back();

           temp->parent->data.push_back(temp->parent->children[indexChildren-1]->data.back());
           temp->parent->children[indexChildren-1]->data.pop_back();

           //move the last child of the sibling to the first position of the child inside temp
           temp->children.insert(temp->children.begin(), temp->parent->children[indexChildren-1]->children.back());
           temp->parent->children[indexChildren-1]->children.pop_back();
           temp->children[0]->parent=temp;
       }
    }
    else if(temp->parent->children.front() == temp)//first left children
    {
        if(temp->parent->children[1]->data.size()<=degree) return false; //check if the node that will borrow (second children of parent) has n+1 elements, if not return false to merge
        if(temp->isLeaf)
        {
           temp->data.push_back(temp->parent->children[1]->data.front());
           temp->parent->children[1]->data.erase(temp->parent->children[1]->data.begin());
           temp->parent->data.front()->value= temp->parent->children[1]->data.front()->value;
        }
        else//temp isn't a leaf
        {
           //we borrow from the closest node of the parent
           temp->data.push_back(temp->parent->data.front());
           temp->parent->data.erase(temp->parent->data.begin());

           //insert the most left node of the right sibling into the parent
           temp->parent->data.insert(temp->parent->data.begin(), temp->parent->children[1]->data.front());
           temp->parent->children[1]->data.erase(temp->parent->children[1]->data.begin());

           //move the first child of the sibling to the last position of the child inside temp
           temp->children.push_back(temp->parent->children[1]->children.front());
           temp->parent->children[1]->children.erase(temp->parent->children[1]->children.begin());
           temp->children.back()->parent=temp;

        }

    }
    else //can try to borrow from both siblings
    {
        for(indexChildren=0; indexChildren<temp->parent->children.size()-1;indexChildren++) //CHANGED LINE ADDED -1
        {
            if(temp->parent->children[indexChildren]==temp) break;
        }

        //we borrow from the right sibling
        if(temp->parent->children[indexChildren+1]->data.size()>degree)
        {
            if(temp->isLeaf)
            {

                temp->data.push_back(temp->parent->children[indexChildren+1]->data.front());
                temp->parent->children[indexChildren+1]->data.erase(temp->parent->children[indexChildren+1]->data.begin());
                temp->parent->data[indexChildren]->value= temp->parent->children[indexChildren+1]->data.front()->value;
            }

            else //temp isn't a leaf
            {
                //we borrow the most close node of the parent
                temp->data.push_back(temp->parent->data[indexChildren]);
                temp->parent->data.erase(temp->parent->data.begin()+indexChildren);

                //insert the most left node of the right sibling into the parent
                temp->parent->data.insert(temp->parent->data.begin()+indexChildren, temp->parent->children[indexChildren+1]->data.front());
                temp->parent->children[indexChildren+1]->data.erase(temp->parent->children[indexChildren+1]->data.begin());

                //move the first children of the sibling to the last position of the children on temp
                temp->children.push_back(temp->parent->children[indexChildren+1]->children.front());
                temp->parent->children[indexChildren+1]->children.erase(temp->parent->children[indexChildren+1]->children.begin());
                temp->children.back()->parent=temp;
            }
        }

        //borrow from the left sibling
        else if(temp->parent->children[indexChildren-1]->data.size()>degree)
        {
            if(temp->isLeaf)
            {
               temp->data.insert(temp->data.begin(), temp->parent->children[indexChildren-1]->data.back());
               temp->parent->data[indexChildren-1]->value= temp->parent->children[indexChildren-1]->data.back()->value;
               temp->parent->children[indexChildren-1]->data.pop_back();//CHANGED LINE
            }
            else //temp isn't a leaf
            {
                //we borrow the most close node of the parent
                temp->data.insert(temp->data.begin(), temp->parent->data[indexChildren-1]);
                temp->parent->data.erase(temp->parent->data.begin()+indexChildren-1);

                //insert the most right node of the left sibling into the parent
                temp->parent->data.insert(temp->parent->data.begin()+indexChildren-1, temp->parent->children[indexChildren-1]->data.back());
                temp->parent->children[indexChildren-1]->data.pop_back();

                //move the last children of the sibling to the first position of the children on temp
                temp->children.insert(temp->children.begin(), temp->parent->children[indexChildren-1]->children.back());
                temp->children[0]->parent=temp;
                temp->parent->children[indexChildren-1]->children.pop_back();
            }
        }

        //cant't borrow form neither sibling
        else
        {
            return false;
        }

    }

    return true;
}


//****************************************************************************************

TreeNode * BPTree::mergeNodes(TreeNode *tNode)
{
    TreeNode *temp;
    temp = tNode;

    int indexChildren;
    indexChildren= temp->parent->children.size()-1;
    TreeNode *auxDir;

    if(temp->parent->children[indexChildren]==temp) // last right children
    {
        if(temp->isLeaf)
        {
            auxDir= temp->parent->children[indexChildren-1];
            for(int i=0; i< temp->data.size();i++)
            {
                auxDir->data.push_back(temp->data[i]);
            }
            temp->parent->data.pop_back();
            temp->parent->children.pop_back();
            if(auxDir->parent==root && auxDir->parent->data.empty())
            {
                root=auxDir;
                auxDir->parent=NULL;
            }
            return auxDir;
        }

        else//is not a leaf
        {
            temp=temp->parent->children[indexChildren-1];

            temp->data.push_back(temp->parent->data.back());//put the split key in the merged node

            for(int i=0; i<temp->parent->children[indexChildren]->data.size(); i++)
            {
                temp->data.push_back(temp->parent->children[indexChildren]->data[i]);
            }

            for(int i=0; i<temp->parent->children[indexChildren]->children.size(); i++)
            {
                temp->children.push_back(temp->parent->children[indexChildren]->children[i]);
            }

            for(int i=0; i<temp->children.size(); i++)
            {
                temp->children[i]->parent=temp;
            }

            temp->parent->children.pop_back();
            temp->parent->data.pop_back();
            if (temp->parent==root && root->data.empty())
            {
                root=temp;
                delete(temp->parent);
                temp->parent=NULL;
            }

            return temp;

        }//close else
    }

    else if(temp->parent->children.front()==temp)//first left children
    {
        tNode=temp;

        if(temp->isLeaf)
        {
            for(int i=0; i<temp->parent->children[1]->data.size(); i++)
            {
                temp->data.push_back(temp->parent->children[1]->data[i]);
            }

            for(int i=0; i<temp->children.size();i++)
            {
                temp->children[i]->parent=temp;
            }

            temp->parent->children.erase(temp->parent->children.begin()+1);
            temp->parent->data.erase(temp->parent->data.begin());

            if (temp->parent==root && root->data.empty())
            {
                root=temp;
                delete(temp->parent);
                temp->parent=NULL;
            }
            return temp;
        }
        else
        {
            temp->data.push_back(temp->parent->data[0]);//put the split key in the merged node
            for(int i=0; i<temp->parent->children[1]->data.size(); i++)
            {
                temp->data.push_back(temp->parent->children[1]->data[i]);
            }

            for(int i=0; i<temp->parent->children[1]->children.size(); i++)
            {
                temp->children.push_back(temp->parent->children[1]->children[i]);
            }

            for(int i=0; i<temp->children.size();i++)
            {
                temp->children[i]->parent=temp;
            }

            temp->parent->children.erase(temp->parent->children.begin()+1);
            temp->parent->data.erase(temp->parent->data.begin());

            if (temp->parent==root && root->data.empty())
            {
                root=temp;
                delete(temp->parent);
                temp->parent=NULL;
                return temp;
            }

        }//close else merge4
    }

    else // children have both siblings
    {
        for(indexChildren=0; indexChildren<temp->parent->children.size();indexChildren++)
        {
            if(temp->parent->children[indexChildren]==temp) break;
        }


        if(temp->isLeaf)
        {
            for(int i=0; i<temp->parent->children[indexChildren+1]->data.size(); i++)
            {
                temp->data.push_back(temp->parent->children[indexChildren+1]->data[i]);
            }

            for(int i=0; i<temp->children.size();i++)
            {
                temp->children[i]->parent=temp;
            }

            temp->parent->children.erase(temp->parent->children.begin()+indexChildren+1);
            temp->parent->data.erase(temp->parent->data.begin()+indexChildren);

            if (temp->parent==root && root->data.empty())
            {
                root=temp;
                delete(temp->parent);
                temp->parent=NULL;
                return temp;
            }
        }

        else
        {
            temp->data.push_back(temp->parent->data[indexChildren]);//put the split key in the merged node

            for(int i=0; i<temp->parent->children[indexChildren+1]->data.size(); i++)
            {
                temp->data.push_back(temp->parent->children[indexChildren+1]->data[i]);
            }

            for(int i=0; i<temp->parent->children[indexChildren+1]->children.size(); i++)
            {
                temp->children.push_back(temp->parent->children[indexChildren+1]->children[i]);
            }

            for(int i=0; i<temp->children.size();i++)
            {
                temp->children[i]->parent=temp;
            }

            temp->parent->children.erase(temp->parent->children.begin()+indexChildren+1);
            temp->parent->data.erase(temp->parent->data.begin()+indexChildren);

            if (temp->parent==root && root->data.empty())
            {
                root=temp;
                delete(temp->parent);
                temp->parent=NULL;
                return temp;
            }

        }//close else
    }

    return temp;
}


//****************************************************************************************


void BPTree::print()
{
    queue<TreeNode> levels;
    if(root->checkLeaf())
    {
        root->print();
        return;
    }

    levels.push(*root);
    while(!levels.empty())
    {
        if(!levels.front().checkLeaf())
        {
            for(int i = 0 ; i < levels.front().children.size() ; ++i)
            {
                levels.push(*levels.front().children[i]);
            }
            levels.pop();

        }

        else
        {
            levels.front().print();
            levels.pop();
        }
    }
}

//**********************************************************************
void BPTree::readFromFile( const char * filename )
{
    std::ifstream ifile(filename, std::ios::in);

    if(!ifile.is_open())
    {
        std::cerr << "There was a problem opening the input file!\n";
        return;
    }

    double num = 0.0;
    while( ifile >> num ){
        add(num);
    }
    ifile.close();
}
//************************************************************************
void BPTree::deleteFromFile( const char * filename )
{
    std::ifstream ifile(filename, std::ios::in);

    if(!ifile.is_open())
    {
        std::cerr << "There was a problem opening the input file!\n";
        return;
    }

    double num = 0.0;
    while( ifile >> num ){
        deleteValue(num);
    }
    ifile.close();
}

//************************************************************************

void BPTree::saveToFile ( const char * filename)
{
   queue<TreeNode> levels;

   std::ofstream outputFile;
   outputFile.open(filename);

    if(root->checkLeaf())
    {
        for(int i=0;i<root->data.size(); i++) outputFile<<root->data[i]->value;
        outputFile.close();
        return;
    }

    levels.push(*root);
    while(!levels.empty())
    {
        if(!levels.front().checkLeaf())
        {
            for(int i = 0 ; i < levels.front().children.size() ; ++i)
            {
                levels.push(*levels.front().children[i]);
            }
            levels.pop();

        }

        else
        {
            for(int i=0;i<levels.front().data.size(); i++) outputFile<<levels.front().data[i]->value<<std::endl;
            levels.pop();
        }
    }

    outputFile.close();
}
#endif // BPTREE_H_INCLUDED
