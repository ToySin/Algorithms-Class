
#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
	int	key;
	int height;
	struct Node	*parent;
	struct Node	*left;
	struct Node	*right;
}Node;

typedef struct Tree
{
	Node	*root;
}Tree;