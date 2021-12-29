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
	int		key;

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
	Node	*succ;
	int	key;

	scanf("%d", &key);
	getchar();
	while (isInternal(temp))
	{
		if (temp->key == key)
		{
			printf("%d\n", temp->key);
			
			if (isInternal(temp->left) && isInternal(temp->right))
			{
				succ = inOrderSucc(temp);
				temp->key = succ->key;
				reduceExternal(succ);
				return;
			}
			else if (isInternal(temp->left))
			{
				temp->left->parent = temp->parent;
				if (temp->parent->left == temp)
					temp->parent->left = temp->left;
				else
					temp->parent->right = temp->left;
				free(temp->right);
				free(temp);

			}
			else if (isInternal(temp->right))
			{
				temp->right->parent = temp->parent;
				if (temp->parent->left == temp)
					temp->parent->left = temp->right;
				else
					temp->parent->right = temp->right;
				free(temp->left);
				free(temp);
			}
			else
				reduceExternal(temp);
			return;
		}
		else if (temp->key > key)
			temp = temp->left;
		else
			temp = temp->right;
	}
	printf("X\n");
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

void	reduceExternal(Node *node)
{
	Node	*p = node->parent;
	Node	*c;

	if (isExternal(node->left) && isExternal(node->right))
	{
		free(node->left);
		node->left = NULL;
		free(node->right);
		node->right = NULL;
	}
	else
	{
		if (isInternal(node->left))
		{
			c = node->left;
			free(node->right);
			free(node);
		}
		else
		{
			c = node->right;
			free(node->left);
			free(node);
		}
		if (p->left == node)
			p->left = c;
		else
			p->right = c;
	}
}

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
	while (isInternal(succ->left))
		succ = succ->left;
	return succ;
}

void	printPreorder(Tree *t)
{
	preorder(t->root);
	printf("\n");
}

void	preorder(Node *node)
{
	if (isExternal(node))
		return;
	printf(" %d", node->key);
	preorder(node->left);
	preorder(node->right);
}
