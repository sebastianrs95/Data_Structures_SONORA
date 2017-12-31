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
    void split(TreeNode *tNode);
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
       split(temp);
       temp=temp->parent;
       if(!temp) break;
    }

}

//***************************************************************
void BPTree::split(TreeNode *tNode)
{
    TreeNode *temp;
    temp=tNode;

    if(temp==root)
    {
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
            for(int i=degree; i<temp->data.size();i++)
            {
                temp->data.pop_back();//delete the n elements that are copied in auxR
                temp->children.pop_back(); //deletes n children copied in auxR
            }
            temp->children.pop_back(); // because after the for theres an extra children in temp


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
