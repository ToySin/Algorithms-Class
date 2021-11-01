#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX 6

typedef struct vertexNode
{
	int	value;
}vNode;

typedef struct edgeNode
{
	int				weight;
	int				u;
	int				v;
}eNode;

typedef struct Graph
{
	int 	n;
	vNode	vertex[MAX_VERTEX];
	eNode	edge[MAX_VERTEX * (MAX_VERTEX + 1) / 2];
	eNode	adj_matrix[MAX_VERTEX][MAX_VERTEX];
}Graph;

vNode	*getVNode();
eNode	*getENode();
Graph	*createGraph();

int		getIndexofMatrix(Graph *g, int v);

void	insertVertex(Graph *g, int value);
void	insertEdge(Graph *g, int u, int v, int weight);

void	searchVertexAndPrintEdges(Graph *g);

vNode	*getVNode()
{
	vNode	*node = (vNode *)malloc(sizeof(vNode));
	return node;
}

eNode	*getENode()
{
	eNode	*node = (eNode *)malloc(sizeof(eNode));
	return node;
}

Graph	*createGraph()
{
	Graph	*graph = (Graph *)malloc(sizeof(Graph));
	graph->n = 0;
	for (int i = 0; i < MAX_VERTEX; i++)
		for (int j = 0; j < MAX_VERTEX; j++)
			graph->adj_matrix[i][j] = 0;
	return graph;
}

int		getIndexofMatrix(Graph *g, int v)
{
	for (int i = 0; i < MAX_VERTEX; i++)
	{
		if (g->vertex[i].value == v)
			return i;
	}
	return -1;
}

void	insertVertex(Graph *g, int value)
{
	vNode	node;
	node.value = value;
	g->vertex[g->n++] = node;
}

void		insertEdge(Graph *g, int u, int v, int weight)
{
	eNode	node;
	node.u = u;
	node.v = v;
	node.weight = weight;

	g->adj_matrix[u][v] = &node;
	g->adj_matrix[v][u] = &node;
}

void		searchVertexAndPrintEdges(Graph *g)
{
	int		value;
	vNode	*temp;

	scanf("%d", &value);
	getchar();
	
	value = getIndexofMatrix(g, value);
	if (value == -1)
		return;

	for (int i = 0; i < MAX_VERTEX; i++)
		if (g->adj_matrix[value][i] != NULL)
			printf(" %d %d", g->vertex[i], g->adj_matrix[value][i]->weight);
	printf("\n");
}

int	main()
{
	Graph	*graph;
	char	operator = 'a';

	graph = createGraph();
	
	for (int i = 0; i < 6; i++)
		insertVertex(graph, i + 1);

	insertEdge(graph, 1, 2, 1);
	insertEdge(graph, 1, 3, 1);
	insertEdge(graph, 1, 4, 1);
	insertEdge(graph, 1, 6, 2);
	insertEdge(graph, 2, 3, 1);
	insertEdge(graph, 3, 5, 4);
	insertEdge(graph, 5, 5, 4);
	insertEdge(graph, 5, 6, 3);

	for (int i = 0; i < MAX_VERTEX; i++)
		printf(" %d %d\n", graph->vertex[i], getIndexofMatrix(graph, i + 1));
	printf("\n");

	for (int i = 0; i < MAX_VERTEX; i++)
	{
		for (int j = 0; j < MAX_VERTEX; j++)
			printf(" %d", graph->adj_matrix[i][j] == NULL ? 0 : graph->adj_matrix[i][j]->weight);
		printf("\n");
	}

	while (operator != 'q')
	{
		scanf("%c", &operator);
		switch (operator)
		{
		case 'a':
			searchVertexAndPrintEdges(graph);
			break;
		
		case 'm':

			break;
		}
	}

	// freeeeeeeeeeeee
	
	return 0;
}