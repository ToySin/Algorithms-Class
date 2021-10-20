#include <stdlib.h>
#include <string.h>

typedef struct HNode
{
	int data;
	struct HNode	*parent;
	struct HNode	*left;
	struct HNode	*right;
}HNode;

typedef struct Node
{
	int			binary;
	struct Node	*next;
}Node;

typedef struct Stack
{
	Node	*top;
}Stack;

Node	*getNode()
{
	Node	*node = (Node *)malloc(sizeof(Node));
	
	node->next = NULL;
	return node;
}

void	push(Stack *s, int n)
{
	Node	*node = getNode();
	node->binary = n;
	node->next = s->top;
	s->top = node;
}

int	pop(Stack *s)
{
	int	temp = s->top->binary;
	Node *tmp = s->top;
	
	s->top = s->top->next;
	free(tmp);
	return temp;
}

HNode	*findLastNode(HNode *root, int n)
{
	Stack s;
	s.top = NULL;

	while (n >= 2)
	{
		push(&s, n % 2);
		n /= 2;
	}

	while (s.top != NULL)
	{
		int	binary = pop(&s);
		if (binary) root = root->right;
		else root = root->left;
	}

	return root;
}