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
    int degree; // Minimun number of elements on a node

public:
    bool check_found(){return found;}
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
    void readFromFile( const char * filename );
    void deleteFromFile( const char * filename );
    TreeNode * searchIndex(int value);
    void changeReference(TreeNode *tNode, int value);


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
        //std::cout<<"Not root\n";
        return (NULL);
    }

    TreeNode *temp;
    temp = root;
    int i;
    while(!temp->isLeaf)
    {
        //std::cout<<"entered while\n";
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
            //std::cout<<"Found\n";
            return(temp);
        }
    }

    //if(found) return temp;
    found= false;
    //std::cout<<"Not Found\n";
    return(temp);
}

//******************************************************************

void BPTree::add(int value)
{
    //std::cout<<"Add entered\n";
    TreeNode *temp = searchNode(value);
    if(found)
    {
      //std::cout<<"The element is already in the tree \n";
      return;
    }

    //std::cout<<"Not found(add)\n";

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


    //std::cout << "Entered temp==root inside split" << std::endl;

    TreeNode *auxP, *auxR; //auxP is the new parent, auxR is the new right child
    auxP= new TreeNode;
    auxR= new TreeNode;

    if(temp->isLeaf)
    {
        //std::cout << "Entered root is a leaf inside split" << std::endl;
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


        std::cout << "temp contents2: " << std::endl;
        temp->print();
        std::cout << "auxR contents2: " << std::endl;
        auxR->print();

        auxP->data.push_back(newNode);
        auxP->children.push_back(temp);
        auxP->children.push_back(auxR);
        temp->parent=auxP;
        auxR->parent=auxP;

        auxR->isLeaf=false;
        auxP->isLeaf=false;

        std::cout << "auxR parent2: " << std::endl;
        auxR->parent->print();

        root = auxP;
    }
}

//*********************************************************************************************************

void BPTree::split(TreeNode *tNode)
{
    TreeNode *temp;
    temp=tNode;


    //std::cout << "Entered temp==root inside split" << std::endl;

    TreeNode  *auxR; //auxP is the new parent, auxR is the new right child
    auxR= new TreeNode;

    if(temp->isLeaf)
    {
        //std::cout << "Entered root is a leaf inside split" << std::endl;
        int midVal = temp->data[degree]->value;


        for(int i=degree; i<temp->data.size();i++)
        {
            auxR->data.push_back(temp->data[i]);

        }

        std::cout << "auxR contents3: " << std::endl;
        auxR->print();
        int auxSize = temp->data.size();
        //we made a for with the same number of iterations that the last for
        for(int i=degree; i < auxSize;i++)
        {
            temp->data.pop_back();//delete the elements that are copied in auxR
        }

        std::cout << "temp contents3: " << std::endl;
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
        std::cout << "auxR parent3: " << std::endl;
        auxR->parent->print();

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
            auxR->children[j]->parent=auxR;
        }

        int i;
        for(i=0; i<temp->parent->data.size();i++)
        {
            if(newNode->value<temp->parent->data[i]->value) break;
        }
        std::cout << "temp contents4: " << std::endl;
        temp->print();
        std::cout << "auxR contents4: " << std::endl;
        auxR->print();


        temp->parent->data.insert(temp->parent->data.begin()+i, newNode);
        temp->parent->children.insert(temp->parent->children.begin()+i+1, auxR);

        auxR->parent=temp->parent;

        std::cout << "auxR parent4: " << std::endl;
        auxR->parent->print();

        auxR->isLeaf=false;
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

    std::cout<<"The element "<<value<<" is been deleting\n\n";
    int i;
    for(i=0; i<temp->data.size();i++)
    {
        if(value==temp->data[i]->value)break;
    }
    temp->data.erase(temp->data.begin()+i);

    //auxReference = searchIndex(value);

    //if(auxReference) changeReference(auxReference, value);


    bool couldBorrow; //aux variable for the while
    couldBorrow=false;
    while(!couldBorrow && (temp->data.size()<degree /*&&temp!=root*/))
    {
        std::cout<<"Need Borrow Or Merge\n";
        cout<<"//////////////////////////////////////////////////////////////////////////////\n";
        std::cout<<"temp before BORROW(";
        if(temp->isLeaf) cout<<"isLeaf):\n";
        else cout<<"is not a leaf):\n";
        temp->print();
        for(int i=0; i<temp->children.size();i++) {
            cout<<"Children "<<i;
            if(temp->children[i]->isLeaf)cout<<" is a leaf\n";
            else cout<<" is not a leaf\n";
            temp->children[i]->print();

        }
        std::cout<<"temp parent before BORROW:\n";
        if(temp->parent){
            temp->parent->print();
            std::cout<<"temp PARENT childrens after BORROW("<<temp->parent->children.size()<<")\n";
                for(int i=0; i<temp->parent->children.size();i++) {
                    cout<<"PARENT Children "<<i;
                    if(temp->parent->children[i]->isLeaf)cout<<" is a leaf\n";
                    else cout<<" is not a leaf\n";
                    temp->parent->children[i]->print();

                }
        }
        else{
            std::cout<<"temp is root ";
            root->print();
        }


        couldBorrow = borrow(temp);
        if (!couldBorrow) cout<<"//////////////////////////////////////////////////////////////////////////////\n";
        else{
            std::cout<<"temp after BORROW(";
            if(temp->isLeaf) cout<<"isLeaf):\n";
            else cout<<"is not a leaf):\n";
            temp->print();
            std::cout<<"temp childrens after BORROW("<<temp->children.size()<<")\n";
            for(int i=0; i<temp->children.size();i++) {
                    cout<<"Children "<<i;
                    if(temp->children[i]->isLeaf)cout<<" is a leaf\n";
                    else cout<<" is not a leaf\n";
                    temp->children[i]->print();

            }
            std::cout<<"temp PARENT after BORROW:\n";
            if(temp->parent){
                    temp->parent->print();
                    std::cout<<"temp PARENT childrens after BORROW("<<temp->parent->children.size()<<")\n";
                        for(int i=0; i<temp->parent->children.size();i++) {
                            cout<<"PARENT Children "<<i;
                            if(temp->parent->children[i]->isLeaf)cout<<" is a leaf\n";
                            else cout<<" is not a leaf\n";
                            temp->parent->children[i]->print();

                        }
            }
            else{
                std::cout<<"temp is root ";
                root->print();
            }
            cout<<"//////////////////////////////////////////////////////////////////////////////\n";
        }

        if(!couldBorrow)
        {
            cout<<"******************************************************************************\n";


            std::cout<<"TEMP before merge(";
            if(temp->isLeaf) cout<<"isLeaf):\n";
            else cout<<"is not a leaf):\n";
            temp->print();
            std::cout<<"temp childrens before merge("<<temp->children.size()<<")\n";
            for(int i=0; i<temp->children.size();i++) {
                cout<<"Children "<<i;
                if(temp->children[i]->isLeaf)cout<<" is a leaf\n";
                else cout<<" is not a leaf\n";
                temp->children[i]->print();

            }

            std::cout<<"temp PARENT before merge:\n";
            if(temp->parent){
                temp->parent->print();
                std::cout<<"temp PARENT childrens before merge("<<temp->parent->children.size()<<")\n";
                for(int i=0; i<temp->parent->children.size();i++) {
                    cout<<"PARENT Children "<<i;
                    if(temp->parent->children[i]->isLeaf)cout<<" is a leaf\n";
                    else cout<<" is not a leaf\n";
                    temp->parent->children[i]->print();

                }
            }

            else{
                std::cout<<"temp is root ";
                root->print();
            }

            temp = mergeNodes(temp);

            //std::cout<<"AFTER MERGE\n TEMP: ";
            //temp->print();

            //std::cout<<"TEMP PARENT: ";
            //if(temp->parent) temp->parent->print();
            //else std::cout<<"this is the root";
            std::cout<<"temp after merge(";
            if(temp->isLeaf) cout<<"isLeaf):\n";
            else cout<<"is not a leaf):\n";
            temp->print();
            std::cout<<"temp childrens after merge("<<temp->children.size()<<")\n";
            for(int i=0; i<temp->children.size();i++) {
                    cout<<"Children "<<i;
                    if(temp->children[i]->isLeaf)cout<<" is a leaf\n";
                    else cout<<" is not a leaf\n";
                    temp->children[i]->print();

            }
            std::cout<<"temp parent after merge:\n";
            if(temp->parent){
                    temp->parent->print();
                    std::cout<<"temp PARENT childrens after merge("<<temp->parent->children.size()<<")\n";
                    for(int i=0; i<temp->parent->children.size();i++) {
                        cout<<"PARENT Children "<<i;
                        if(temp->parent->children[i]->isLeaf)cout<<" is a leaf\n";
                        else cout<<" is not a leaf\n";
                        temp->parent->children[i]->print();

                    }
            }
            else{
                std::cout<<"temp is root ";
                root->print();
        }
        cout<<"******************************************************************************\n";
        }//call merge


        if (temp==root || temp->parent==root) return;
        //if(!temp->parent)return;
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
    //std::cout<<"entered borrow\n";
    //if(tNode->parent==NULL)std::cout<<"RROOOOTT\n";
    int indexChildren;
    indexChildren= temp->parent->children.size()-1;
    //std::cout<<indexChildren<<"\n";

    if(temp->parent->children[indexChildren]->data[0]->value==temp->data[0]->value) // last right children
    {
       //std::cout<<"borrow1\n";
       if(temp->parent->children[indexChildren-1]->data.size()<=degree) return false; //check if the node that will borrow have n+1 elements if not return false to merge
       if(temp->isLeaf)
       {
           cout<<"borrow 1\n";
           /*Node *newNode;
           newNode= (Node*)malloc(sizeof(Node));
           newNode->value=temp->parent->children[indexChildren-1]->data.back()->value;*/
           temp->data.insert(temp->data.begin(), temp->parent->children[indexChildren-1]->data.back());
           temp->parent->data.back()->value= temp->parent->children[indexChildren-1]->data.back()->value;
           temp->parent->children[indexChildren-1]->data.pop_back();
           //temp->parent->data.pop_back();
           //temp->parent->data.push_back(newNode);
       }
       else//case treeNode temp isn't leaf
       {
           /*
           temp->data.insert(temp->data.begin(), temp->parent->children[indexChildren-1]->data.back());
           temp->parent->data.back()->value= temp->parent->children[indexChildren-1]->data.back()->value;

           temp->parent->children[indexChildren-1]->data.pop_back();
           */

            cout<<"borrow 2\n";
           //we borrow the most close node of the parent
           temp->data.insert(temp->data.begin(),temp->parent->data.back());
           temp->parent->data.pop_back();

           //insert the most right node of the left sibling into the parent
           temp->parent->data.push_back(temp->parent->children[indexChildren-1]->data.back());
           temp->parent->children[indexChildren-1]->data.pop_back();

           //move the last children of the sibling to the first position of the children on temp
           temp->children.insert(temp->children.begin(), temp->parent->children[indexChildren-1]->children.back());
           temp->parent->children[indexChildren-1]->children.pop_back();
           temp->children[0]->parent=temp;

       }
    }
    else if(temp->parent->children.front()==temp)//first left children
    {
        //std::cout<<"borrow2\n";
        if(temp->parent->children[1]->data.size()<=degree) return false; //check if the node that will borrow (second children of parent) have n+1 elements if not return false to merge
        cout<<"borrow 3\n";
        if(temp->isLeaf)
        {


           temp->data.push_back(temp->parent->children[1]->data.front());
           temp->parent->children[1]->data.erase(temp->parent->children[1]->data.begin());
           temp->parent->data.front()->value= temp->parent->children[1]->data.front()->value;
        }
        else//temp isn't a leaf
        {
            cout<<"borrow 4\n";
           //we borrow the most close node of the parent
           temp->data.push_back(temp->parent->data.front());
           temp->parent->data.erase(temp->parent->data.begin());

           //insert the most left node of the right sibling into the parent
           temp->parent->data.insert(temp->parent->data.begin(), temp->parent->children[1]->data.front());
           temp->parent->children[1]->data.erase(temp->parent->children[1]->data.begin());

           //move the first children of the sibling to the last position of the children on temp
           temp->children.push_back(temp->parent->children[1]->children.front());
           temp->parent->children[1]->children.erase(temp->parent->children[1]->children.begin());
           temp->children.back()->parent=temp;

        }

    }
    else //can try to borrow from both siblings
    {
        //cout<<"borrow 5\n";
        //std::cout<<"borrow3\n";
        for(indexChildren=0; indexChildren<temp->parent->children.size()-1;indexChildren++) //CHANGED LINE ADDED -1
        {
            if(temp->parent->children[indexChildren]==temp) break;
        }

        //we borrow from the right sibling
        if(temp->parent->children[indexChildren+1]->data.size()>degree)
        {
            if(temp->isLeaf)
            {
                cout<<"borrow 6\n";
                temp->data.push_back(temp->parent->children[indexChildren+1]->data.front());
                temp->parent->children[indexChildren+1]->data.erase(temp->parent->children[indexChildren+1]->data.begin());
                temp->parent->data[indexChildren]->value= temp->parent->children[indexChildren+1]->data.front()->value;
            }

            else //temp isn't a leaf
            {
                cout<<"borrow 7\n";
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
                cout<<"borrow 8\n";
               temp->data.insert(temp->data.begin(), temp->parent->children[indexChildren-1]->data.back());
               temp->parent->data[indexChildren-1]->value= temp->parent->children[indexChildren-1]->data.back()->value;
               temp->parent->children[indexChildren-1]->data.pop_back();//CHANGED LINE
            }
            else //temp isn't a leaf
            {
                cout<<"borrow 9\n";
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
            cout<<"borrow 10\n";
            return false;
        }

    }

    //std::cout<<"temp parent: ";
    //temp->parent->print();
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
        std::cout<<"Merge0\n";
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
            std::cout<<"merge1\n";
            temp=temp->parent->children[indexChildren-1];
            //std::cout<<"merge1\n";
            //temp->print();

            temp->data.push_back(temp->parent->data.back());//put the split key in the merged node

            for(int i=0; i<temp->parent->children[indexChildren]->data.size(); i++)
            {
                //std::cout<<"for loop1\n";
                temp->data.push_back(temp->parent->children[indexChildren]->data[i]);
            }

            //std::cout<<"merge2\n";
            //temp->print();

            for(int i=0; i<temp->parent->children[indexChildren]->children.size(); i++)
            {
                //std::cout<<"for loop2\n";
                temp->children.push_back(temp->parent->children[indexChildren]->children[i]);
            }

            for(int i=0; i<temp->children.size();i++)
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


            std::cout<<"merge3\n";
            temp->print();

            return temp;

            //tNode=temp;


        }//close else
    }

    else if(temp->parent->children.front()==temp)//first left children
    {
        //std::cout<<"merge2\n";
        tNode=temp;

        tNode->print();
        //std::cout<<"Merge2\n";
        if(temp->isLeaf)
        {
            std::cout<<"merge2\n";
            for(int i=0; i<temp->parent->children[1]->data.size(); i++)
            {
                //std::cout<<"for loop\n";
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
            cout<<"merge3\n";
            temp->data.push_back(temp->parent->data[0]);//put the split key in the merged node

            for(int i=0; i<temp->parent->children[1]->data.size(); i++)
            {
                //std::cout<<"for loop\n";
                temp->data.push_back(temp->parent->children[1]->data[i]);
            }

            for(int i=0; i<temp->parent->children[1]->children.size(); i++)
            {
                //std::cout<<"for loop\n";
                temp->children.push_back(temp->parent->children[1]->children[i]);
            }

            for(int i=0; i<temp->children.size();i++)
            {
                temp->children[i]->parent=temp;
            }

            temp->parent->children.erase(temp->parent->children.begin()+1);
            temp->parent->data.erase(temp->parent->data.begin());
            //temp->parent->data.erase(temp->parent->data.begin());
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
        //std::cout<<"Merge4\n";
        for(indexChildren=0; indexChildren<temp->parent->children.size();indexChildren++)
        {
            if(temp->parent->children[indexChildren]==temp) break;
        }


        if(temp->isLeaf)
        {
            std::cout<<"Merge4\n";
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
            std::cout<<"Merge5\n";
            //temp=temp->parent->children[indexChildren-1];

            temp->data.push_back(temp->parent->data[indexChildren]);//put the split key in the merged node

            for(int i=0; i<temp->parent->children[indexChildren+1]->data.size(); i++)
            {
                //std::cout<<"for loop\n";
                temp->data.push_back(temp->parent->children[indexChildren+1]->data[i]);
            }

            for(int i=0; i<temp->parent->children[indexChildren+1]->children.size(); i++)
            {
                //std::cout<<"for loop\n";
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
TreeNode * BPTree::searchIndex(int value)
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
        //std::cout<<"entered while\n";
        i=0;
        for(; i<temp->data.size();i++)
        {
            if(value<temp->data[i]->value)break;
            if(value==temp->data[i]->value)
            {
                return temp;
            }
        }
        temp= temp->children[i];
    }

    return(NULL);

}

//****************************************************************************************
void BPTree::changeReference(TreeNode *tNode, int value)
{
    TreeNode *temp;
    temp =tNode;

    int i=0;
    for(; i<temp->data.size();i++)
    {
        if(value==temp->data[i]->value)
        {
            i++;
            break;
        }
    }

    temp= temp->children[i];

    while(!temp->isLeaf)
    {
        temp=temp->children[0];
    }

    tNode->data[i-1]->value=value;


}

//****************************************************************************************
void BPTree::print()
{
    //std::cout<<"print: 1\n";
    queue<TreeNode> levels;

    //std::cout<<"print: 2\n";
//    levels.push(*root);
    if(root->checkLeaf())
    {
        //std::cout<<"print: 3\n";
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
#endif // BPTREE_H_INCLUDED
