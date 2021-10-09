#include <stdio.h>

typedef struct Node
{
	int			key;
	struct Node	*parent;
	struct Node	*left;
	struct Node	*right;
}				Node;

