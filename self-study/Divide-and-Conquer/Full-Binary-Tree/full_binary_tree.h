#ifndef __FULL_BINARY_TREE_H__
#define __FULL_BINARY_TREE_H__

typedef struct Node
{
	int			data;
	struct Node	*left;
	struct Node	*right;
}Node;

typedef struct Tree
{
	Node	*root;
}Tree;

Node	*getNode()

#endif