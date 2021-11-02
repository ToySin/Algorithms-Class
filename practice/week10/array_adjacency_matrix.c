#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTEX 6


struct Graph;
struct Vertex;
struct Edge;

typedef struct Edge
{
	int u;
	int v;
	int weight;
}Edge;

typedef struct Graph
{
	int	vertex[MAX_VERTEX];
	int	vertex_n;
	int	adjMatrix[MAX_VERTEX][MAX_VERTEX];
	struct Edge	edge[MAX_VERTEX * (MAX_VERTEX + 1) / 2];
	int	edge_n;
}Graph;



Graph	*createGraph();
void	insertVertex(Graph *g, int v);
void	insertEdge(Graph *g, int u, int v, int weight);
void	deleteVertex(Graph *g, int v);
void	deleteEdge(Graph *g, int u, int v);

int		getIndexOfVertex(Graph *g, int v);
int		getIndexOfEdge(Graph *g, int u, int v);

void	searchVertexAndPrintEdges(Graph *g);
void	searchEdgeAndFixWeight(Graph *g);


Graph	*createGraph()
{
	Graph	*g = (Graph *)malloc(sizeof(Graph));
	g->vertex_n = 0;
	g->edge_n = 0;
	for (int i = 0; i < MAX_VERTEX; i++)
		for (int j = 0; j < MAX_VERTEX; j++)
			g->adjMatrix[i][j] = -1;
	return g;
}

void	insertVertex(Graph *g, int v)
{
	if ((g->vertex_n + 1) > MAX_VERTEX)
	{
		printf("\nGraph is Full\n");
		return;
	}
	g->vertex[g->vertex_n++] = v;
}

void	insertEdge(Graph *g, int u, int v, int weight)
{
	int	u_idx = getIndexOfVertex(g, u);
	int	v_idx = getIndexOfVertex(g, v);
	
	if (u_idx == -1 || v_idx == -1)
	{
		printf("\nVertex is not exist\n");
		return;
	}

	g->edge[g->edge_n].u = u;
	g->edge[g->edge_n].v = v;
	g->edge[g->edge_n].weight = weight;

	g->adjMatrix[u_idx][v_idx] = g->edge_n;
	g->adjMatrix[v_idx][u_idx] = g->edge_n++;
}

void	deleteEdge(Graph *g, int u, int v)
{
	int	edge_index = getIndexOfEdge(g, u, v);
	int	u_idx, v_idx;

	if (edge_index == -1)
	{
		printf("-1\n");
		return;
	}
	u_idx = getIndexOfVertex(g, g->edge[edge_index].u);
	v_idx = getIndexOfVertex(g, g->edge[edge_index].v);
	g->adjMatrix[u_idx][v_idx] = -1;
	g->adjMatrix[v_idx][u_idx] = -1;
	for (int i = edge_index; i < g->edge_n - 1; i++)
	{
		g->edge[i] = g->edge[i + 1];
		u_idx = getIndexOfVertex(g, g->edge[i].u);
		v_idx = getIndexOfVertex(g, g->edge[i].v);
		g->adjMatrix[u_idx][v_idx]--;
		if (u_idx != v_idx)
			g->adjMatrix[v_idx][u_idx]--;
	}
	g->edge_n--;
}

int		getIndexOfVertex(Graph *g, int v)
{
	for (int i = 0; i <= g->vertex_n; i++)
		if (g->vertex[i] == v)
			return i;
	return -1;
}

int		getIndexOfEdge(Graph *g, int u, int v)
{
	u = getIndexOfVertex(g, u);
	v = getIndexOfVertex(g, v);
	return g->adjMatrix[u][v];
}

void	searchVertexAndPrintEdges(Graph *g)
{
	int	value;
	int	vertex_index;
	int	u, v, w;

	scanf("%d", &value);
	getchar();
	vertex_index = getIndexOfVertex(g, value);

	if (vertex_index == -1)
	{
		printf("-1\n");
		return;
	}

	for (int i = 0; i < g->vertex_n; i++)
	{
		if (g->adjMatrix[vertex_index][i] == -1)
			continue;
		u = g->edge[g->adjMatrix[vertex_index][i]].u;
		v = g->edge[g->adjMatrix[vertex_index][i]].v;
		w = g->edge[g->adjMatrix[vertex_index][i]].weight;
		printf(" %d %d", u == value ? v : u, w);
	}
	printf("\n");
}

void	searchEdgeAndFixWeight(Graph *g)
{
	int	u, v, weight;
	int	edge_index;

	scanf("%d", &u);
	scanf("%d", &v);
	scanf("%d", &weight);
	getchar();
	edge_index = getIndexOfEdge(g, u, v);
	if (getIndexOfVertex(g, u) == -1 || getIndexOfVertex(g, v) == -1)
	{
		printf("-1\n");
		return;
	}
	else if (edge_index == -1)
		insertEdge(g, u, v, weight);
	else if (weight == 0)
		deleteEdge(g, u, v);
	else
		g->edge[edge_index].weight = weight;
}

int	main()
{
	Graph	*graph;
	char	operator = 'a';

	graph = createGraph();
	
	for (int i = 0; i < MAX_VERTEX; i++)
		insertVertex(graph, i + 1);

	insertEdge(graph, 1, 2, 1);
	insertEdge(graph, 1, 3, 1);
	insertEdge(graph, 1, 4, 1);
	insertEdge(graph, 1, 6, 2);
	insertEdge(graph, 2, 3, 1);
	insertEdge(graph, 3, 5, 4);
	insertEdge(graph, 5, 5, 4);
	insertEdge(graph, 5, 6, 3);

	while (operator != 'q')
	{
		/*
		for (int i = 0; i < MAX_VERTEX; i++)
			printf(" %d %d\n", graph->vertex[i], getIndexOfVertex(graph, i + 1));
		printf("\n");

		for (int i = 0; i < graph->edge_n; i++)
		{
			printf(" %d %d %d\n", graph->edge[i].u, graph->edge[i].v, graph->edge[i].weight);
		}

		for (int i = 0; i < MAX_VERTEX; i++)
		{
			for (int j = 0; j < MAX_VERTEX; j++)
				printf(" %d", graph->adjMatrix[i][j]);
			printf("\n");
		}
		*/
		scanf("%c", &operator);
		switch (operator)
		{
		case 'a':
			searchVertexAndPrintEdges(graph);
			break;
		
		case 'm':
			searchEdgeAndFixWeight(graph);
			break;
		}
	}

	// freeeeeeeeeeeee
	
	return 0;
}