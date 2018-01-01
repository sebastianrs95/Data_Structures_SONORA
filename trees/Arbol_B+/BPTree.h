#ifndef BPTREE_H_INCLUDED
#define BPTREE_H_INCLUDED

#include <queue>
#include <cstdlib>
#include <iostream>

using std::queue;

class BPTree
{
    TreeNode * root;
    bool found;
    int degree; // Minimun number of elements on a node

public:
    BPTree(){degree =2; root=NULL;}
    ~BPTree(){}

    TreeNode * searchNode(int value);
    void add(int value);
    void splitRoot(TreeNode *tNode);
    void split(TreeNode *tNode);
    void deleteValue(int value);
    bool borrow(TreeNode *tNode);
    TreeNode* mergeNodes(TreeNode *tNode);
    void print();

};

    /*
     \brief  function that search if a element if present on the tree
     \param value the value to be search in the tree
     \return a boolean that indicates if the element was found
    */
TreeNode * BPTree::searchNode(int value)
{
    if(!root)
    {
        found=false;
        std::cout<<"Not root\n";
        return (NULL);
    }

    TreeNode *temp;
    temp = root;
    int i;
    while(!temp->isLeaf)
    {
        std::cout<<"entered while\n";
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
            found=true;
            std::cout<<"Found\n";
            return(temp);
        }
    }

    //if(found) return temp;
    found= false;
    std::cout<<"Not Found\n";
    return(temp);
}

//******************************************************************

void BPTree::add(int value)
{
    std::cout<<"Add entered\n";
    TreeNode *temp = searchNode(value);
    if(found)
    {
      std::cout<<"The element is already in the tree \n";
      return;
    }

    std::cout<<"Not found(add)\n";

    Node *aux;
    aux= (Node*)malloc(sizeof(Node));
    aux->value=value;

    if(!root)
    {
        //temp = (TreeNode*)malloc(sizeof(TreeNode));
        temp = new TreeNode;
        temp->isLeaf = true;
        temp->data.clear();
        std::cout<< temp->data.empty() << "\n";
        temp->data.push_back(aux);
        root=temp;
        std::cout<<"Value added to the tree\n";
        //std::cout<<root->data[0]->value;
        std::cout<<temp->data.size();
        return;
    }

    int i;
    for(i=0; i<temp->data.size();i++)
    {
        if(value<temp->data[i]->value) break;
    }
    temp->data.insert(temp->data.begin()+i, aux);

    while(temp->data.size()==2*degree+1)
    {
       if(temp==root) splitRoot(temp);
       else split(temp);
       temp=temp->parent;
       if(!temp) break;
    }

}

//***************************************************************
void BPTree::splitRoot(TreeNode *tNode)
{
    TreeNode *temp;
    temp=tNode;


    std::cout << "Entered temp==root inside split" << std::endl;

    TreeNode *auxP, *auxR; //auxP is the new parent, auxR is the new right child
    auxP= new TreeNode;
    auxR= new TreeNode;

    if(temp->isLeaf)
    {
        std::cout << "Entered root is a leaf inside split" << std::endl;
        int midVal = temp->data[degree]->value;


        for(int i=degree; i<temp->data.size();i++)
        {
            auxR->data.push_back(temp->data[i]);

        }

        std::cout << "auxR contents: " << std::endl;
        auxR->print();
        int auxSize = temp->data.size();
        //we made a for with the same number of iterations that the last for
        for(int i=degree; i < auxSize;i++)
        {
            temp->data.pop_back();//delete the elements that are copied in auxR
        }

        std::cout << "temp contents: " << std::endl;
        temp->print();
        Node *newNode;
        newNode=(Node*)malloc(sizeof(Node));
        newNode->value=midVal;
        auxP->data.push_back(newNode);
        auxP->children.push_back(temp);
        auxP->children.push_back(auxR);
        temp->parent=auxP;
        auxR->parent=auxP;

        auxR->isLeaf=true;
        auxP->isLeaf=false;

        std::cout << "auxR parent: " << std::endl;
        auxR->parent->print();

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


        std::cout << "temp contents: " << std::endl;
        temp->print();
        std::cout << "auxR contents: " << std::endl;
        auxR->print();

        auxP->data.push_back(newNode);
        auxP->children.push_back(temp);
        auxP->children.push_back(auxR);
        temp->parent=auxP;
        auxR->parent=auxP;

        auxR->isLeaf=false;
        auxP->isLeaf=false;

        std::cout << "auxR parent: " << std::endl;
        auxR->parent->print();

        root = auxP;
    }
}

//*********************************************************************************************************

void BPTree::split(TreeNode *tNode)
{
    TreeNode *temp;
    temp=tNode;


    std::cout << "Entered temp==root inside split" << std::endl;

    TreeNode  *auxR; //auxP is the new parent, auxR is the new right child
    auxR= new TreeNode;

    if(temp->isLeaf)
    {
        std::cout << "Entered root is a leaf inside split" << std::endl;
        int midVal = temp->data[degree]->value;


        for(int i=degree; i<temp->data.size();i++)
        {
            auxR->data.push_back(temp->data[i]);

        }

        std::cout << "auxR contents: " << std::endl;
        auxR->print();
        int auxSize = temp->data.size();
        //we made a for with the same number of iterations that the last for
        for(int i=degree; i < auxSize;i++)
        {
            temp->data.pop_back();//delete the elements that are copied in auxR
        }

        std::cout << "temp contents: " << std::endl;
        temp->print();
        Node *newNode;
        newNode=(Node*)malloc(sizeof(Node));
        newNode->value=midVal;

        int i;
        for(i=0; i<temp->parent->data.size();i++)
        {
            if(newNode->value<temp->parent->data[i]->value) break;
        }
        temp->parent->data.insert(temp->parent->data.begin()+i, newNode);
        temp->parent->children.insert(temp->parent->children.begin()+i+1, auxR);


        auxR->parent=temp->parent;

        auxR->isLeaf=true;
        std::cout << "auxR parent: " << std::endl;
        auxR->parent->print();

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

        int i;
        for(i=0; i<temp->parent->data.size();i++)
        {
            if(newNode->value<temp->parent->data[i]->value) break;
        }
        std::cout << "temp contents: " << std::endl;
        temp->print();
        std::cout << "auxR contents: " << std::endl;
        auxR->print();


        temp->parent->data.insert(temp->parent->data.begin()+i, newNode);
        temp->parent->children.insert(temp->parent->children.begin()+i+1, auxR);

        auxR->parent=temp->parent;

        std::cout << "auxR parent: " << std::endl;
        auxR->parent->print();

        auxR->isLeaf=false;
    }
}

//****************************************************************************************
void BPTree::deleteValue(int value)
{
    TreeNode *temp;
    temp= searchNode(value);

    if(!found)
    {
        std::cout<<"That element is not on the tree\n\n";
        return;
    }

    int i;
    for(i=0; i<temp->data.size();i++)
    {
        if(value==temp->data[i]->value)break;
    }
    temp->data.erase(temp->data.begin()+i);

     bool couldBorrow; //aux variable for the while
     couldBorrow=false;
    while(!couldBorrow && (temp->data.size()<degree &&temp!=root))
    {
        std::cout<<"Need Borrow\n";

        couldBorrow = borrow(temp);

        if(!couldBorrow)
        {
            std::cout<<"NEED MERGE!!!\n";
            temp = mergeNodes(temp);

            std::cout<<"AFTER MERGE\n TEMP: ";
            temp->print();

            std::cout<<"TEMP PARENT: ";
            if(temp->parent) temp->parent->print();
            else std::cout<<"this is the root";
        }//call merge
        std::cout<<"Root: ";
        root->print();
        if (temp==root) return;
        temp=temp->parent;
    }

    return;

}
//****************************************************************************************
//tNode is the child that need to borrow
bool BPTree::borrow(TreeNode *tNode)
{
    TreeNode *temp;
    temp =tNode;
    std::cout<<"entered borrow\n";
    if(tNode->parent==NULL)std::cout<<"RROOOOTT\n";
    int indexChildren;
    indexChildren= temp->parent->children.size()-1;
    std::cout<<indexChildren<<"\n";
    if(temp->parent->children[indexChildren]->data[0]->value==temp->data[0]->value) // last right children
    {
       std::cout<<"borrow1\n";
       if(temp->parent->children[indexChildren-1]->data.size()<=degree) return false; //check if the node that will borrow have n+1 elements if not return false to merge
       if(temp->isLeaf)
       {
           /*Node *newNode;
           newNode= (Node*)malloc(sizeof(Node));
           newNode->value=temp->parent->children[indexChildren-1]->data.back()->value;*/
           temp->data.insert(temp->data.begin(), temp->parent->children[indexChildren-1]->data.back());
           temp->parent->data.back()->value= temp->parent->children[indexChildren-1]->data.back()->value;
           temp->parent->children[indexChildren-1]->data.pop_back();
           //temp->parent->data.pop_back();
           //temp->parent->data.push_back(newNode);
       }
       else
       {
           temp->data.insert(temp->data.begin(), temp->parent->children[indexChildren-1]->data.back());
           temp->parent->data.back()->value= temp->parent->children[indexChildren-1]->data.back()->value;
           temp->parent->children[indexChildren-1]->data.pop_back();
       }
    }
    else if(temp->parent->children.front()==temp)//first left children
    {
        std::cout<<"borrow2\n";
        if(temp->parent->children[1]->data.size()<=degree) return false; //check if the node that will borrow (second children of parent) have n+1 elements if not return false to merge


       temp->data.push_back(temp->parent->children[1]->data.front());
       temp->parent->children[1]->data.erase(temp->parent->children[1]->data.begin());
       temp->parent->data.front()->value= temp->parent->children[1]->data.front()->value;
    }
    else
    {
        std::cout<<"borrow3\n";
        for(indexChildren=0; indexChildren<temp->parent->children.size();indexChildren++)
        {
            if(temp->parent->children[indexChildren]==temp) break;
        }

        if(temp->parent->children[indexChildren+1]->data.size()>degree)
        {
            temp->data.push_back(temp->parent->children[indexChildren+1]->data.front());
            temp->parent->children[indexChildren+1]->data.erase(temp->parent->children[indexChildren+1]->data.begin());
            temp->parent->data[indexChildren]->value= temp->parent->children[indexChildren+1]->data.front()->value;
        }

        else if(temp->parent->children[indexChildren-1]->data.size()>degree)
        {
           temp->data.insert(temp->data.begin(), temp->parent->children[indexChildren-1]->data.back());
           temp->parent->data[indexChildren]->value= temp->parent->children[indexChildren-1]->data.back()->value;
           temp->parent->children[indexChildren-1]->data.pop_back();
        }

        else
        {
            return false;
        }

    }

    std::cout<<"temp parent: ";
    temp->parent->print();
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

    std::cout<<"entered Merge\n";
    if(temp->parent->children[indexChildren]==temp) // last right children
    {
        std::cout<<"Merge1\n";
        if(temp->isLeaf)
        {
            auxDir= temp->parent->children[indexChildren-1];
            for(int i=0; i< temp->data.size();i++)
            {
                auxDir->data.push_back(temp->data[i]);
            }
            temp->parent->data.pop_back();
            temp->parent->children.pop_back();
            return auxDir;

        }

        else
        {
            temp=temp->parent->children[indexChildren-1];

            temp->print();

            temp->data.push_back(temp->parent->data.back());//put the split key in the merged node

            for(int i=0; i<temp->parent->children[indexChildren]->data.size(); i++)
            {
                std::cout<<"for loop1\n";
                temp->data.push_back(temp->parent->children[indexChildren]->data[i]);
            }

            temp->print();

            for(int i=0; i<temp->parent->children[indexChildren]->children.size(); i++)
            {
                std::cout<<"for loop2\n";
                temp->children.push_back(temp->parent->children[indexChildren]->children[i]);
            }

            for(int i=0; i<temp->children.size();i++)
            {
                temp->children[i]->parent=temp;
            }

            temp->parent->children.pop_back();
            temp->parent->data.pop_back();
            if (temp->parent==root && root->data.size()==0)
            {
                root=temp;
                delete(temp->parent);
                temp->parent=NULL;
            }

            tNode=temp;

            tNode->print();

            return temp;

            //tNode=temp;


        }//close else
    }

    else if(temp->parent->children.front()==temp)//first left children
    {tNode=temp;

            tNode->print();
        std::cout<<"Merge2\n";
        if(temp->isLeaf)
        {
            for(int i=0; i<temp->parent->children[1]->data.size(); i++)
            {
                std::cout<<"for loop\n";
                temp->data.push_back(temp->parent->children[1]->data[i]);
            }

            for(int i=0; i<temp->children.size();i++)
            {
                temp->children[i]->parent=temp;
            }

            temp->parent->children.erase(temp->parent->children.begin()+1);
            temp->parent->data.erase(temp->parent->data.begin());
        }
        else
        {
            temp->data.push_back(temp->parent->data[0]);//put the split key in the merged node

            for(int i=0; i<temp->parent->children[1]->data.size(); i++)
            {
                std::cout<<"for loop\n";
                temp->data.push_back(temp->parent->children[1]->data[i]);
            }

            for(int i=0; i<temp->parent->children[1]->children.size(); i++)
            {
                std::cout<<"for loop\n";
                temp->children.push_back(temp->parent->children[1]->children[i]);
            }

            for(int i=0; i<temp->children.size();i++)
            {
                temp->children[i]->parent=temp;
            }

            temp->parent->data.erase(temp->parent->data.begin());
            if (temp->parent==root && root->data.size()==0)
            {
                root=temp;
                delete(temp->parent);
                temp->parent=NULL;
                return temp;
            }

            temp->parent->children.erase(temp->parent->children.begin()+1);
            temp->parent->data.erase(temp->parent->data.begin());
        }//close else
    }

    else // children have both siblings
    {
        std::cout<<"Merge3\n";
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
        }

        else
        {
            temp=temp->parent->children[indexChildren-1];

            temp->data.push_back(temp->parent->data[indexChildren]);//put the split key in the merged node

            for(int i=0; i<temp->parent->children[indexChildren]->data.size(); i++)
            {
                std::cout<<"for loop\n";
                temp->data.push_back(temp->parent->children[indexChildren]->data[i]);
            }

            for(int i=0; i<temp->parent->children[indexChildren]->children.size(); i++)
            {
                std::cout<<"for loop\n";
                temp->children.push_back(temp->parent->children[indexChildren]->children[i]);
            }

            for(int i=0; i<temp->children.size();i++)
            {
                temp->children[i]->parent=temp;
            }

            temp->parent->children.erase(temp->parent->children.begin()+indexChildren);
            temp->parent->data.erase(temp->parent->data.begin()+indexChildren);
            if (temp->parent==root && root->data.size()==0)
            {
                root=temp;
                delete(temp->parent);
                temp->parent=NULL;
            }

        }//close else
    }

    return temp;

}
//****************************************************************************************

void BPTree::print()
{
    std::cout<<"print: 1\n";
    queue<TreeNode> levels;

    std::cout<<"print: 2\n";
//    levels.push(*root);
    if(root->checkLeaf())
    {
        std::cout<<"print: 3\n";
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
    std::cout << "imprimiendo raiz" << std::endl;
    root->print();
}

#endif // BPTREE_H_INCLUDED
