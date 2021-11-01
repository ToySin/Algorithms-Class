#include <stdio.h>
#include <stdlib.h>

struct vertexNode;
struct edgeNode;
struct incidenceEdgeNode;

typedef struct vertexNode
{
	int							value;
	struct incidenceEdgeNode	*inc_edges;
	struct vertexNode			*link;
}vNode;

typedef struct edgeNode
{
	int				weight;
	vNode			*u;
	vNode			*v;
	struct edgeNode	*link;
}eNode;

typedef struct incidenceEdgeNode
{
	eNode	*edge;
	struct incidenceEdgeNode	*link;
}incENode;

typedef struct Graph
{
	vNode	*vertex;
	eNode	*edge;
}Graph;

vNode		*getVNode();
eNode		*getENode();
incENode	*getIcnENode();
Graph		*createGraph();
vNode		*getUNode(vNode *v, eNode *e);

int			numVertices();
int			numEdges();
vNode		vertices();
eNode		edges();

void		insertVertex(Graph *g, int value);
void		insertEdge(Graph *g, int u, int v, int weight);
void		insertIncENode(vNode *v, eNode *e);
vNode		*searchVertex(Graph *g, int value);
eNode		*searchEdge(Graph *g, int u, int v);

void		searchVertexAndPrintEdges(Graph *g);

vNode	*getVNode()
{
	vNode	*node = (vNode *)malloc(sizeof(vNode));
	node->inc_edges = getIncENode();
	node->link = NULL;
	return node;
}

eNode	*getENode()
{
	eNode	*node = (eNode *)malloc(sizeof(eNode));
	node->u = NULL;
	node->v = NULL;
	node->link = NULL;
	return node;
}

incENode	*getIcnENode()
{
	incENode	*node = (incENode *)malloc(sizeof(incENode));
	node->edge = NULL;
	node->link = NULL;
}

Graph		*createGraph()
{
	Graph	*graph = (Graph *)malloc(sizeof(Graph));
	graph->vertex = getVNode();
	graph->edge = getENode();
	return graph;
}

vNode		*getUNode(vNode *v, eNode *e)
{
	return e->u == v ? e->v : e->u;
}

void		insertVertex(Graph *g, int value)
{
	vNode	*node = getVNode();
	node->value = value;
	node->link = g->vertex;
	g->vertex = node;
}

void		insertEdge(Graph *g, int u, int v, int weight)
{
	eNode	*node = getENode();
	vNode	*v_u = searchVertex(g, u);
	vNode	*v_v = searchVertex(g, v);
	node->u = v_u;
	node->v = v_v;
	node->weight = weight;
	node->link = g->edge;
	g->edge = node;

	// incidence Edges
	insertIncENode(v_u, node);
	insertIncENode(v_v, node);
}

void		insertIncENode(vNode *v, eNode *e)
{
	incENode	*node = getIcnENode();
	incENode	*temp = v->inc_edges;

	node->edge = e;
	
	while (temp->link != NULL)
	{
		if (getUNode(v, temp->link->edge)->value > getUNode(v, node->edge)->value)
		{
			node->link = temp->link;
			temp->link = node;
			break;
		}
		temp = temp->link;
	}
	if (temp->link == NULL)
	{
		node->link = temp->link;
		temp->link = node;
	}
}

vNode		*searchVertex(Graph *g, int value)
{
	vNode	*temp = g->vertex;

	while (temp != NULL)
	{
		if (temp->value == value)
			return temp;
		temp = temp->link;
	}

	return NULL;
}

eNode		*searchEdge(Graph *g, int u, int v)
{
	vNode	*v_u = searchVertex(g, u);
	eNode	*temp = v_u->inc_edges;

	while (temp != NULL)
	{
		if (temp->v->value == v)
			return temp;
		temp = temp->link;
	}

	return temp;
}

void		searchVertexAndPrintEdges(Graph *g)
{
	int			value;
	vNode	*temp;
	incENode	*inc_temp;

	scanf("%d", &value);
	getchar();
	temp = searchVertex(g, value);
	inc_temp = temp->inc_edges;

	while (inc_temp->link != NULL)
	{
		printf(" %d %d", getUNode(temp, inc_temp->link->edge), 
			inc_temp->link->edge->weight);
		inc_temp = inc_temp->link;
	}
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