
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

Node	*getNode();
Tree	*initTree();

int		isRoot(Node *node);
int		isExternal(Node *node);
int		isInternal(Node *node);
int		isBalanced(Node *node);

void	expandExternal(Node *node);

void	insertItem(Tree *t);
void	searchItem(Tree *t);

void	postRefreshHeight(Node *node);
void	refreshHeight(Node *node);
Node	*searchAndFixAfterInsertion(Node *node);
Node	*restructure(Node *x, Node *y, Node *z);

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
	expandExternal(temp);
	postRefreshHeight(t->root);
	if (!isRoot(temp))
		if (!isRoot(temp->parent))
			t->root = searchAndFixAfterInsertion(temp);
	postRefreshHeight(t->root);
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

void	refreshHeight(Node *node)
{
	node->height = node->left->height > node->right->height
		? node->left->height + 1 : node->right->height + 1;
}

void	postRefreshHeight(Node *node)
{
	if (isInternal(node->left))
		postRefreshHeight(node->left);
	if (isInternal(node->right))
		postRefreshHeight(node->right);
	refreshHeight(node);
}

Node	*searchAndFixAfterInsertion(Node *node)
{
	Node	*x, *y, *z, *zp;
	int		child_flag;

	x = node;
	do
	{
		y = x->parent;
		z = y->parent;
		zp = z->parent;
		if (!isRoot(z))
		{
			if (zp->left == z)
				child_flag = 0;
			else if (zp->right == z)
				child_flag = 1;
		}
		if (!isBalanced(z))
		{
			z = restructure(x, y, z);
			break;
		}
		else
			x = y;
	} while (!isRoot(z));

	if (zp)
	{
		if (child_flag == 0)
			zp->left = z;
		else
			zp->right = z;
	}
	while (!isRoot(z))
		z = z->parent;
	return z;	
}

void	expandExternal(Node *node)
{
	node->left = getNode();
	node->left->parent = node;
	node->left->height = 0;
	node->right = getNode();
	node->right->parent = node;
	node->right->height = 0;
}

int		isRoot(Node *node)
{
	return !node->parent;
}

int		isExternal(Node *node)
{
	return (!(node->left) && !(node->right));
}

int		isInternal(Node *node)
{
	return (node->left || node->right);
}

int		isBalanced(Node *node)
{
	int	delta = node->left->height - node->right->height;

	return (-2 < delta) && (delta < 2);
}

Node	*restructure(Node *x, Node *y, Node *z)
{
	Node	*inorderRank[3] = { x, y, z };
	Node	*T[4];
	Node	*temp;
	int		min = 0;
	int		t_idx, i_idx;

	for (int i = 1; i < 3; i++)
		if (inorderRank[min]->key > inorderRank[i]->key)
			min = i;
	temp = inorderRank[min];
	inorderRank[min] = inorderRank[0];
	inorderRank[0] = temp;
	if (inorderRank[1]->key > inorderRank[2]->key)
	{
		temp = inorderRank[1];
		inorderRank[1] = inorderRank[2];
		inorderRank[2] = temp;
	}

	t_idx = 0;
	i_idx = 0;
	while (t_idx < 4)
	{
		for (int i = 0; i < 3; i++)
			if (inorderRank[i_idx]->left == inorderRank[i])
				break;
			else if (i == 2)
				T[t_idx++] = inorderRank[i_idx]->left;
		for (int i = 0; i < 3; i++)
			if (inorderRank[i_idx]->right == inorderRank[i])
				break;
			else if (i == 2)
				T[t_idx++] = inorderRank[i_idx]->right;
		i_idx++;
	}

	inorderRank[1]->left = inorderRank[0];
	inorderRank[1]->right = inorderRank[2];
	inorderRank[0]->left = T[0];
	inorderRank[0]->right = T[1];
	inorderRank[2]->left = T[2];
	inorderRank[2]->right = T[3];
	
	return inorderRank[1];
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
