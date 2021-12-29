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

typedef struct QNode
{
	Node			*node;
	struct QNode	*link;
}					QNode;

typedef struct Queue
{
	QNode	*front;
	QNode	*rare;
}			Queue;

Node	*getNode();

Node	*rBuildHeap(int n, int cur, Queue *q);
Node	*BuildHeap(int n);
void	downHeap(Node *node);
void	printHeap(Node *node);

QNode	*getQNode();
void	enQueue(Queue *q, Node *node);
Node	*deQueue(Queue *q);
int		isEmptyQueue(Queue *q);

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
	heap->root = BuildHeap(n);
	printHeap(heap->root);
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

Node	*rBuildHeap(int n, int cur, Queue *q)
{
	Node	*parent, *left, *right;
	int		temp = 1;

	left = NULL;
	right = NULL;
	
	if (cur == 1)
	{
		parent = getNode();
		scanf("%d", &(parent->key));
		enQueue(q, parent);
	}
	parent = deQueue(q);
	if (cur * 2 <= n)
	{
		left = getNode();
		scanf("%d", &(left->key));
		parent->left = left;
		enQueue(q, left);
	}
	if (cur * 2 + 1 <= n)
	{
		right = getNode();
		scanf("%d", &(right->key));
		parent->right = right;
		enQueue(q, right);
	}
	if (n >= cur + 1)
		rBuildHeap(n, cur + 1, q);
	downHeap(parent);
	return parent;
}

Node	*BuildHeap(int n)
{
	Queue	q;
	q.front = NULL;
	q.rare = NULL;
	
	return rBuildHeap(n, 1, &q);
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

void	printHeap(Node *node)
{
	Queue	*q = (Queue *)malloc(sizeof(Queue));
	Node	*temp;
	
	if (q == NULL)
		return;
	q->front = NULL;
	q->rare = NULL;
	enQueue(q, node);
	while (!isEmptyQueue(q))
	{
		temp = deQueue(q);
		printf(" %d", temp->key);
		if (temp->left)
			enQueue(q, temp->left);
		if (temp->right)
			enQueue(q, temp->right);
	}
	free(q);
}


QNode	*getQNode()
{
	QNode	*node = (QNode *)malloc(sizeof(QNode));
	if (node == NULL)
		return 0;
	node->link = NULL;
	return node;
}

void	enQueue(Queue *q, Node *node)
{
	QNode	*qn = getQNode();
	qn->node = node;
	if (isEmptyQueue(q))
	{
		q->front = qn;
		q->rare = qn;
	}
	else
	{
		q->rare->link = qn;
		q->rare= qn;
	}
}

Node	*deQueue(Queue *q)
{
	Node *temp = q->front->node;
	QNode *tmp = q->front;
	q->front = q->front->link;
	if (q->front == NULL)
		q->rare = NULL;
	free(tmp);
	return temp;
}

int	isEmptyQueue(Queue *q)
{
	return !(q->front);
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