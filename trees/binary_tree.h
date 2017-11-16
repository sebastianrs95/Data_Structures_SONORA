#pragma once

struct node {
	int value;
	node *rChild, *lChild, *parent, *previous, *next;
};

enum WHERE = { EMPTY, ROOY, RCHILD, LCHILD }


class binary_tree
{
public:
	binary_tree();
	~binary_tree();

	void searchNode(int val);
	void add(int val);
	void remove1(node * p);
	void print();

private:
	node * root;
	bool found;
	int how;
	node * where;
};

