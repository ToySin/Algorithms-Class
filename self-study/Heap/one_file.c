#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node
{
	int			key;
	struct Node	*parent;
	struct Node	*left;
	struct Node	*right;
}Node;

typedef struct Heap
{
	Node	*root;
	Node	*last;
}Heap;

void	swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

Node	*getNode()
{
	Node	*node;
	
	if (!(node = (Node *)malloc(sizeof(Node))))
		return NULL;
	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;
}

void	initHeap(Heap *heap)
{
	heap->root = getNode();
	heap->last = heap->root;
}

bool	isRoot(Node *node)
{
	return node->parent;
}

bool	isLeft(Node *node)
{
	return node == node->parent->left;
}

bool	isRight(Node *node)
{
	return node == node->parent->right;
}

bool	isInternal(Node *node)
{
	return node->left && node->right;
}

bool	isExternal(Node *node)
{
	return !(node->left || node->right);
}

Node	*sibiling(Node *node)
{
	return (isLeft(node) ? node->parent->right : node->parent->left);
}

void	expandExternal(Node *node)
{
	node->left = getnode();
	node->left->parent = node;
	node->right = getnode();
	node->right->parent = node;
}

void	upHeap(Node *node)
{
	// root node
	if (isRoot(node))
		return ;
	if (node->key < node->parent->key)
	{
		swap(&(node->key), &(node->parent->key));
		upHeap(node->parent);
	}
}

void	advancedLast(Node *node)
{
	while (isRight(node))
		node = node->parent;
	if (isLeft(node))
		node = sibiling(node);
	while (isInternal(node))
		node = node->left;
}

void	insertItem(Heap *heap)
{
	int	key;

	scanf("%d", &key);
	heap->last->key = key;
	expandExternal(heap->last);
	upHeap(heap->last);
	advancedLast(&(heap->last));
}

