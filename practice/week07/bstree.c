#include <stdio.h>
#include <stdlib.h>


typedef struct Node
{
	int	key;
	struct Node	*parent;
	struct Node	*left;
	struct Node	*right;
}Node;

typedef struct Tree
{
	Node	*root;
}Tree;

Node	*getNode();
Tree	*initTree();

void	insertItem(Tree *t);
void	deleteItem(Tree *t);
void	searchItem(Tree *t);

void	expandInternal(Node *node);
void	reduceExternal(Node *node);

int		findElement(Tree *t);
Node	*treeSearch(Tree *t);

int		isExternal(Node *node);
int		isInternal(Node *node);
Node	*inOrderSucc(Node *node);

void	printPreorder(Tree *t);
void	preorder(Node *node);

int	main()
{
	Tree	*tree = initTree();
	char	oper;
	
	while (1)
	{
		scanf("%c", &oper);
		if (oper == 'q')
			break;
		switch (oper)
		{
			case 'i':
				insertItem(tree);
				break;
			
			case 'd':
				deleteItem(tree);
				break;
			
			case 's':
				searchItem(tree);
				break;
			
			case 'p':
				printPreorder(tree);
				break;
		}
	}
}

Node	*getNode()
{
	Node	*node = (Node *)malloc(sizeof(Node));
	
	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;
	return node;
}

Tree	*initTree()
{
	Tree	*tree = (Tree *)malloc(sizeof(Tree));

	tree->root = getNode();
	return tree;
}

void	insertItem(Tree *t)
{
	Node	*temp = t->root;
	int	key;

	scanf("%d", &key);
	getchar();
	while (isInternal(temp))
	{
		if (key < temp->key)
			temp = temp->left;
		else
			temp = temp->right;
	}
	temp->key = key;
	expandInternal(temp);
}

void	deleteItem(Tree *t)
{
	Node	*temp = t->root;
	int	key;

	scanf("%d", &key);
	getchar();
	while (isInternal(temp))
	{
		if (temp->key == key)
		{
			printf("%d\n", temp->key);
			
		}
		else if (temp->key > key)
			temp = temp->left;
		else
			temp = temp->right;
	}
}

void	searchItem(Tree *t)
{
	Node	*temp = t->root;
	int	key;

	scanf("%d", &key);
	getchar();
	while (isInternal(temp))
	{
		if (temp->key == key)
		{
			printf("%d\n", temp->key);
			return;
		}
		else if (temp->key > key)
			temp = temp->left;
		else
			temp = temp->right;
	}
	printf("X\n");
}

void	expandInternal(Node *node)
{
	node->left = getNode();
	node->left->parent = node;
	node->right = getNode();
	node->right->parent = node;
}

void	reduceExternal(Node *node);

int		findElement(Tree *t);
Node	*treeSearch(Tree *t);

int		isExternal(Node *node)
{
	return (!(node->left) && !(node->right));
}

int		isInternal(Node *node)
{
	return (node->left || node->right);
}

Node	*inOrderSucc(Node *node)
{
	Node	*succ = node;

	succ = succ->right;
	if (isExternal(succ))
		return node->left;
	while (isInternal(succ->left))
		succ = succ->left;
	return succ;
}

void	printPreorder(Tree *t)
{
	preorder(t->root);
}

void	preorder(Node *node)
{
	if (isExternal(node))
		return;
	printf(" %d", node->key);
	preorder(node->left);
	preorder(node->right);
}