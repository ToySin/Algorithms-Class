#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
	int			key;
	struct Node	*left;
	struct Node	*right;
}				Node;

typedef struct Heap
{
	Node	*root;
}			Heap;

Node	*getNode();
Node	*rBuildHeap(int n, int cur);
void	downHeap(Node *node);
void	printHeap(Heap *heap);

void	swapKey(int *a, int *b);

void	freeHeap(Heap *heap);
void	freeNode(Node *node);

int	main(void)
{
	int		n;
	Heap	*heap = (Heap *)malloc(sizeof(Heap));
	
	if (!(heap = (Heap *)malloc(sizeof(Heap))))
		return 0;
	scanf("%d", &n);
	rBuildHeap(n, 1);
	printHeap(heap);
	freeHeap(heap);
}

Node	*getNode()
{
	Node	*node = (Node *)malloc(sizeof(Node));
	if (node == NULL)
		return 0;
	node->left = NULL;
	node->right = NULL;
	return node;
}

Node	*rBuildHeap(int n, int cur)
{
	Node	*parent, *left, *right;
	
	left = NULL;
	right = NULL;

	parent = getNode();
	scanf("%d", &parent->key);
	if (n == cur)
		return parent;
	
	if (n >= cur * 2)
		left = rBuildHeap(n, cur * 2);
	if (n >= cur * 2 + 1)
		right = rBuildHeap(n, cur * 2 + 1);
	parent->left = left;
	parent->right = right;
	downHeap(parent);
	return parent;
}

void	downHeap(Node *node)
{
	if (!node->left)
		return;
	else if (!node->right)
	{
		if (node->key < node->left->key)
		{
			swapKey((&node->key), &(node->left->key));
			downHeap(node->left);
		}
	}
	else
	{
		if (node->left->key > node->right->key)
		{
			if (node->key < node->left->key)
			{
				swapKey((&node->key), &(node->left->key));
				downHeap(node->left);
			}
		}
		else
		{
			if (node->key < node->right->key)
			{
				swapKey((&node->key), &(node->right->key));
				downHeap(node->right);
			}
		}
	}
}

void	printHeap(Heap *heap)
{
	//code
}

void	swapKey(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void	freeHeap(Heap *heap)
{
	freeNode(heap->root);
	free(heap);
}

void	freeNode(Node *node)
{
	if (node->left)
		freeNode(node->left);
	if (node->right)
		freeNode(node->right);
	free(node);
}