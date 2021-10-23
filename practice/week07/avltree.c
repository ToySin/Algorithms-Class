
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

int		isExternal(Node *node);
int		isInternal(Node *node);
int		isBalanced(Node *node);

void	expandExternal(Node *node);

void	insertItem(Tree *t);
void	searchItem(Tree *t);

void	searchAndFixAfterInsertion(Node *node);
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

void	expandExternal(Node *node)
{
	node->left = getNode();
	node->left->parent = node;
	node->right = getNode();
	node->right->parent = node;
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


void	getInorderRank(Node *rank, Node *x, Node *y, Node *z)
{
	
}


Node	*restructure(Node *x, Node *y, Node *z)
{
	Node	inorder[3];
	Node	T[4];

	// get inorder[3];

	// if inorder[3] and left or right is not inorder[3]
	// postorder rank T[0..3]
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
