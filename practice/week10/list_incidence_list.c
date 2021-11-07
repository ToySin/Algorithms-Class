#include <stdio.h>
#include <stdlib.h>


struct Graph;
struct Vertex;
struct Edge;
struct Inc;


typedef struct Vertex
{
	int	v;
	struct Vertex	*link;
	struct Inc	*header;
}Vertex;

typedef struct Edge
{
	int u;
	int v;
	int weight;
	struct Edge	*link;
}Edge;

typedef struct Inc
{
	struct Edge	*edge;
	struct Inc	*link;
}Inc;

typedef struct Graph
{
	Vertex	*vertex;
	Edge	*edge;
}Graph;

Vertex	*getVertexNode();
Edge	*getEdgeNode();
Inc		*getIncNode();

Vertex	*getVertex(Graph *g, int v);
Edge	*getEdge(Graph *g, int u, int v);
Edge	*getPrevEdge(Graph *g, int u, int v);
int		getDesVertex(int v, Edge *e);

Graph	*createGraph();
void	insertVertex(Graph *g, int v);
void	insertEdge(Graph *g, int u, int v, int weight);
void	insertInc(Graph *g, int u, int v);
void	deleteVertex(Graph *g, int v);
void	deleteEdge(Graph *g, int u, int v);
void	deleteInc(Graph *g, Vertex *v_node, Edge *e_node);

void	searchVertexAndPrintEdges(Graph *g);
void	searchEdgeAndFixWeight(Graph *g);

void	freeGraph(Graph *g);

Vertex	*getVertexNode()
{
	Vertex	*node = (Vertex *)malloc(sizeof(Vertex));
	node->header = NULL;
	node->link = NULL;
	return node;
}

Edge	*getEdgeNode()
{
	Edge	*node = (Edge *)malloc(sizeof(Edge));
	node->link = NULL;
	return node;
}

Inc		*getIncNode()
{
	Inc	*node = (Inc *)malloc(sizeof(Inc));
	node->edge = NULL;
	node->link = NULL;
	return node;
}

Vertex	*getVertex(Graph *g, int v)
{
	Vertex	*temp = g->vertex;

	while (temp != NULL)
	{
		if (temp->v == v)
			return temp;
		temp = temp->link;
	}
	return NULL;
}

Edge	*getEdge(Graph *g, int u, int v)
{
	Edge	*temp = g->edge;

	while (temp != NULL)
	{
		if (temp->u == u && temp->v == v)
			return temp;
		if (temp->u == v && temp->v == u)
			return temp;
		temp = temp->link;
	}
	return NULL;
}

Edge	*getPrevEdge(Graph *g, int u, int v)
{
	Edge	*temp = g->edge;

	if (temp->u == u && temp->v == v)
		return temp;
	if (temp->u == v && temp->v == u)
		return temp;

	while (temp->link != NULL)
	{
		if (temp->link->u == u && temp->link->v == v)
			return temp;
		if (temp->link->u == v && temp->link->v == u)
			return temp;
		temp = temp->link;
	}
	return NULL;
}

int		getDesVertex(int v, Edge *e)
{
	return (e->u == v) ? (e->v) : (e->u);
}

Graph	*createGraph()
{
	Graph	*g = (Graph *)malloc(sizeof(Graph));
	g->vertex = getVertexNode();
	g->edge = getEdgeNode();
	return g;
}

void	insertVertex(Graph *g, int v)
{
	Vertex	*node = getVertexNode();
	node->v = v;
	node->header = getIncNode();
	node->link = g->vertex->link;
	g->vertex->link = node;
}

void	insertEdge(Graph *g, int u, int v, int weight)
{
	Vertex	*u_node = getVertex(g, u);
	Vertex	*v_node = getVertex(g, v);
	Edge	*node = getEdgeNode();
	
	if (u_node == NULL || v_node == NULL)
	{
		printf("\nVertex is not exist\n");
		return;
	}
	node->u = u;
	node->v = v;
	node->weight = weight;
	node->link = g->edge->link;
	g->edge->link = node;
	
	insertInc(g, u, v);
}

void	insertInc(Graph *g, int u, int v)
{
	Vertex	*u_node = getVertex(g, u);
	Vertex	*v_node = getVertex(g, v);
	Inc		*u_inc = getIncNode();
	Inc		*v_inc = getIncNode();
	Inc		*temp;
	int		value;

	u_inc->edge = g->edge->link;
	v_inc->edge = g->edge->link;
	
	temp = u_node->header;
	while (temp->link != NULL)
	{
		value = getDesVertex(u, temp->link->edge);
		if (getDesVertex(u, u_inc->edge) < value)
		{
			u_inc->link = temp->link;
			temp->link = u_inc;
			break;
		}
		temp = temp->link;
	}
	if (temp->link == NULL)
	{
		u_inc->link = NULL;
		temp->link = u_inc;
	}

	if (u != v)
	{
		temp = v_node->header;
		while (temp->link != NULL)
		{
			value = getDesVertex(v, temp->link->edge);
			if (getDesVertex(v, v_inc->edge) < value)
			{
				v_inc->link = temp->link;
				temp->link = v_inc;
				break;
			}
			temp = temp->link;
		}
	}
	if (temp->link == NULL)
	{
		v_inc->link = NULL;
		temp->link = v_inc;
	}
}

void	deleteVertex(Graph *g, int v)
{
	Vertex	*v_node = g->vertex;
	Vertex	*v_temp;
	Inc		*temp;

	while (v_node->link != NULL)
	{
		if (v_node->link->v == v)
			break;
		v_node = v_node->link;
	}
	if (v_node == NULL)
		return;
	
	temp = v_node->link->header;

	while (temp->link != NULL)
		deleteEdge(g, temp->link->edge->u, temp->link->edge->v);
	free(temp);

	v_temp = v_node->link;
	v_node->link = v_node->link->link;
	free(v_temp);
}

void	deleteEdge(Graph *g, int u, int v)
{
	Edge	*e_node = g->edge;
	Edge	*temp;
	Vertex	*u_node, *v_node;

	while (e_node->link != NULL)
	{
		if (e_node->link->u == u && e_node->link->v == v)
			break;
		if (e_node->link->u == v && e_node->link->v == u)
			break;
		e_node = e_node->link;
	}
	if (e_node == NULL)
		return;

	u_node = getVertex(g, e_node->link->u);
	v_node = getVertex(g, e_node->link->v);
	
	deleteInc(g, u_node, e_node->link);
	deleteInc(g, v_node, e_node->link);

	temp = e_node->link;
	e_node->link = e_node->link->link;
	free(temp);
}

void	deleteInc(Graph *g, Vertex *v_node, Edge *e_node)
{
	Inc	*temp = v_node->header;
	Inc *rm;

	while (temp->link != NULL)
	{
		if (temp->link->edge == e_node)
		{
			rm = temp->link;
			temp->link = temp->link->link;
			free(rm);
			return;
		}
		temp = temp->link;
	}
}

void	searchVertexAndPrintEdges(Graph *g)
{
	int		value;
	Vertex	*v_node;
	Inc		*temp;

	scanf("%d", &value);
	getchar();
	v_node = getVertex(g, value);

	if (v_node == NULL)
	{
		printf("-1\n");
		return;
	}

	temp = v_node->header->link;
	while (temp != NULL)
	{
		printf(" %d %d", getDesVertex(value, temp->edge), temp->edge->weight);
		temp = temp->link;
	}
	printf("\n");
}

void	searchEdgeAndFixWeight(Graph *g)
{
	int		u, v, weight;
	Edge	*e_node;

	scanf("%d", &u);
	scanf("%d", &v);
	scanf("%d", &weight);
	getchar();
	e_node = getEdge(g, u, v);
	if (getVertex(g, u) == NULL || getVertex(g, v) == NULL)
	{
		printf("-1\n");
		return;
	}
	else if (e_node == NULL)
		insertEdge(g, u, v, weight);
	else if (weight == 0)
		deleteEdge(g, u, v);
	else
		e_node->weight = weight;
}

void	freeGraph(Graph *g)
{
	while (g->vertex->link != NULL)
		deleteVertex(g, g->vertex->link->v);
	
	free(g->vertex);
	free(g->edge);
	free(g);
}

int	main()
{
	Graph	*graph;
	char	operator = 'a';

	graph = createGraph();
	
	for (int i = 1; i < 7; i++)
		insertVertex(graph, i);

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
	freeGraph(graph);
	return 0;
}
test for gitcat