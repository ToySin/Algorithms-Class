
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
int		isLeft(Node* node);
int		isRight(Node* node);

void	expandExternal(Node *node);

void	insertItem(Tree *t);
void	searchItem(Tree *t);
void	deleteItem(Tree *t);

void	postRenewalHeight(Node *node);
void	renewalHeight(Node *node);

void	searchAndFixAfterInsertion(Tree *t, Node *node);
Node	*restructure(Node *z);

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
			
			case 'd':
				deleteItem(tree);
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

int		isLeft(Node *node)
{
	if (isRoot(node))
		return 0;
	return node->parent->left == node;
}

int		isRight(Node *node)
{
	if (isRoot(node))
		return 0;
	return node->parent->right == node;
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
	renewalHeight(temp);
	searchAndFixAfterInsertion(t, temp);
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

void	deleteItem(Tree *t)
{
	Node	*temp = t->root;
	Node	*succ;
	int		key;

	scanf("%d", &key);
	getchar();
	while (isInternal(temp))
	{
		if (temp->key == key)
		{
			printf("%d\n", temp->key);
			if (isInternal(temp->left) && isInternal(temp->right))
			{
				succ = //inOrderSucc();
				temp->key = succ->key;
				//reduceExternal(succ);
				searchAndFixAfterDelete(succ);
				return;
			}
			else if (isInternal(temp->left))
			{
				temp->left->parent = temp->parent;
				if (isLeft(temp))
					temp->parent->left = temp->left;
				else if (isRight(temp))
					temp->parent->right = temp->left;
				succ = temp->parent;
				free(temp->right);
				free(temp);
			}
			else if (isInternal(temp->right))
			{
				temp->right->parent = temp->parent;
				if (isLeft(temp))
					temp->parent->left = temp->right;
				else if (isRight(temp))
					temp->parent->right = temp->right;
				succ = temp->parent;
				free(temp->left);
				free(temp);
			}
			else
			{
				succ = temp->parent;
				reduceExternal(temp);
			}
			searchAndFixAfterDelete(succ);
			return;
		}
	}
}

void	renewalHeight(Node *node)
{
	node->height = node->left->height > node->right->height
		? node->left->height + 1 : node->right->height + 1;
	if (!isRoot(node))
		renewalHeight(node->parent);
}

void	postRenewalHeight(Node *node)
{
	if (isInternal(node->left))
		postRenewalHeight(node->left);
	if (isInternal(node->right))
		postRenewalHeight(node->right);
	node->height = node->left->height > node->right->height
		? node->left->height + 1 : node->right->height + 1;
}

void	searchAndFixAfterInsertion(Tree *t, Node *node)
{
	Node	*z, *zp;

	z = node;
	while (1)
	{
		if (isRoot(z) && isBalanced(z))
			return;
		else if (!isBalanced(z))
			break;
		z = z->parent;
	}
	zp = z->parent;
	if (isRoot(z))
	{
		t->root = restructure(z);
		t->root->parent = NULL;
	}
	else if (isLeft(z))
	{
		z->parent->left = restructure(z);
		zp->left->parent = zp;
	}
	else if (isRight(z))
	{
		z->parent->right = restructure(z);
		zp->right->parent = zp;
	}
	postRenewalHeight(t->root);
}

void	searchAndFixAfterDelete(Tree *t, Node *node)
{

}

Node	*restructure(Node *z)
{
	Node	*x, *y;
	Node	*inorderRank[3];
	Node	*T[4];
	Node	*temp;
	int		min = 0;
	int		t_idx, i_idx;

	// set x, y, z
	y = z->left->height > z->right->height ? z->left : z->right;
	x = y->left->height > y->right->height ? y->left : y->right;
	inorderRank[0] = x;
	inorderRank[1] = y;
	inorderRank[2] = z;

	// set a, b, c
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

	// set T[0] ~ T[3]
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

	// restruct
	/**
	 * 				b
	 * 		a				c
	 * 	T0		T1		T2		T3
	 */
	inorderRank[1]->left = inorderRank[0];
	inorderRank[0]->parent = inorderRank[1];
	inorderRank[1]->right = inorderRank[2];
	inorderRank[2]->parent = inorderRank[1];
	inorderRank[0]->left = T[0];
	T[0]->parent = inorderRank[0];
	inorderRank[0]->right = T[1];
	T[1]->parent = inorderRank[0];
	inorderRank[2]->left = T[2];
	T[2]->parent = inorderRank[2];
	inorderRank[2]->right = T[3];
	T[3]->parent = inorderRank[2];
	
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