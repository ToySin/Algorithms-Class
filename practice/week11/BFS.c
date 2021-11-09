#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 100

typedef struct QNode
{
	int value;
	struct QNode	*link;
}QNode;

typedef struct Queue
{
	QNode	*front;
	QNode	*rare;
}Queue;

typedef struct Graph
{
	int	n;
	int	adj_matrix[MAX_VERTEX][MAX_VERTEX];
}Graph;

void	initQueue(Queue *q)
{
	q->front = NULL;
	q->rare = NULL;
}

int		isQueueEmpty(Queue *q)
{
	return (q->front == NULL) || (q->rare == NULL);
}

void	enQueue(Queue *q, int v)
{
	QNode	*node = (QNode *)malloc(sizeof(QNode));
	node->value = v;
	node->link = NULL;
	if (isQueueEmpty(q))
		q->rare = node;
	else
		q->front->link = node;
	q->front = node;
}

int		deQueue(Queue *q)
{
	int	temp = q->rare->value;
	QNode	*q_temp = q->rare;
	q->rare = q->rare->link;
	if (isQueueEmpty(q))
		q->front = NULL;
	free(q_temp);
	return temp;
}

void	initGraph(Graph *g)
{
	for (int i = 0; i < MAX_VERTEX; i++)
		for (int j = 0; j < MAX_VERTEX; j++)
			g->adj_matrix[i][j] = 0;
}

void	insertEdge(Graph *g)
{
	int	u, v;

	scanf("%d %d", &u, &v);
	g->adj_matrix[u - 1][v - 1] = 1;
	g->adj_matrix[v - 1][u - 1] = 1;
}

void	BFS(Graph *g, int s)
{
	Queue q;
	int	visited[MAX_VERTEX];
	int	v;

	for (int i = 0; i < g->n; i++)
		visited[i] = 0;

	initQueue(&q);
	enQueue(&q, s);
	while (!isQueueEmpty(&q))
	{
		v = deQueue(&q);
		visited[v - 1] = 1;
		printf("%d\n", v);
		for (int i = 0; i < g->n; i++)
		{
			if (g->adj_matrix[v - 1][i] && !visited[i])
			{
				enQueue(&q, i + 1);
				visited[i] = 1;
			}
		}
	}
}

int	main()
{
	Graph	graph;
	int n, m, s;

	scanf("%d %d %d", &n, &m, &s);
	initGraph(&graph);
	graph.n = n;
	for (int i = 0; i < m; i++)
		insertEdge(&graph);
	BFS(&graph, s);
	return 0;
}