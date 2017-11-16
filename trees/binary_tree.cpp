#include "stdafx.h"
#include "binary_tree.h"


binary_tree::binary_tree()
{
	where = rChild = lChild = parent = previous = next = NULL;
	how = EMPTY;
	found = false;
}


binary_tree::~binary_tree()
{
}



/*******************************************************************************************************************/

void binary_tree::searchNode(int val)
{
	node * p;
	p = root;

	if (p == NULL) {
		found = false;
		how = EMPTY;
		where = NULL;
		return;
	}

	while (p)
	{
		if (p->value == val) {
			found = true;
			return;
		}

		else 
			if (p->value < val) {
				how = RCHILD;
				where = p;
				p = p->rChild;
			}
			else {
				how = LCHILD;
				where = p;
				p = p->lChild;
			}
	}

	found = false;
	return;
}


/*******************************************************************************************************************/

int binary_tree::add(int val)
{
	node * p;
	searchNode(val);
	if (found) return 0;

	p = new node;
	p->value = val;
	p->lChild = NULL;
	p->rChild = NULL;

	if (how == EMPTY)
	{
		// tree
		root = p;
		p->parent = NULL;

		//doubly-linked list
		p->previous = NULL;
		p->next = NULL;
		firstNode = p;
		lastNode = p;
	}

	else 
		if (how == RCHILD)
		{
			where->rChild = p;
			p->parent = where;
			p->next = where->next;
			p->previous = where;
			where->next = p;
			if (p->next == NULL) endNode = p;
			else p->next->previous = p;
		}
		else
		{
			where->lChild = p;
			p->parent = where;
			p->next = where;
			p->previous = where->previous;
			where->previous = p;
			if (p->previous == NULL) firstNode = p;
			else p->previous->next = p;
		}
}


/*******************************************************************************************************************/

int binary_tree::remove1(node * p)
{
	if (p->rChild == NULL && p->lChild == NULL)
	{
		if (how == RCHILD) where->rChild = NULL;
		else if (where == LCHILD) where->lChild = NULL;
		else root = NULL;	// if you want to erase the root
		return;
	}
	else if (p->rChild == NULL && p->lChild != NULL)
	{
		if (how == RCHILD) {
			where->rChild = p->lChild;
			p->lChild->parent = where;
		}

		else
		{
			if (how == LCHILD) {
				where->lChild = p->lChild;
				p->lChild->parent = where;
			}

			else {
				root = p->lChild;
				p->lChild->parent = NULL;
			}

			if (how == RCHILD) {
				where->rChild = p->rChild;
				p->rChild->parent = where;
			}
			else {
				root = p->lChild;
				p->lChild->parent = NULL;
			}
		}
	}

}