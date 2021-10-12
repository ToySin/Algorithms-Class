#include <stdio.h>
#include <stdlib.h>

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
{
	Node	*node;
	if (!(node = (Node *)malloc(sizeof(Node))))
		return NULL;
	node->left = NULL;
	node->right = NULL;
	return node;
}

Tree	initTree(Tree *tree)
{
	
}