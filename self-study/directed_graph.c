#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
	int	edgeId;
	struct Node *next;
} Node;

typedef struct Vertex
{
	int vname;
	Node *incid_list;
} Vertex;

typedef struct Edge
{
	int ename;
	int	vtx1;
	int	vtx2;
	int	weight;
} Edge;

typedef struct Graph
{
	Vertex *vertices;
	int vsize;
	Edge *edges;
	int esize;
} Graph;

Node *get_node(int eid, Node *next)
{
	Node *node = (Node *)malloc(sizeof(Node));
	node->edgeId = eid;
	node->next = next;
	return node;
}

int	opposite(Graph *g, Node *node, int vs)
{
	Edge e = g->edges[node->edgeId];
	return (e.vtx1 == vs) ? e.vtx2 : e.vtx1;
}

void	set_edge_arr(Graph *g, int eid, int v1, int v2, int w)
{
	g->edges[eid].ename = eid;
	g->edges[eid].vtx1 = v1;
	g->edges[eid].vtx2 = v2;
	g->edges[eid].weight = w;
}

void	insert_incid_node(Graph *g, int eid, int vs, int vd)
{
	Node *node = g->vertices[vs].incid_list;
	Node *new_node;

	new_node = get_node(eid, node->next);
	node->next = new_node;
}

void	add_edge(Graph *g, int eid, int vs, int vd, int w)
{
	set_edge_arr(g, eid, vs, vd, w);
	insert_incid_node(g, eid, vs, vd);
}

void	set_vertices(Graph *g, int vsize)
{
	g->vertices = (Vertex *)malloc(vsize * sizeof(Vertex));
	g->vsize = vsize;

	for (int i = 0; i < vsize; i++)
	{
		g->vertices[i].vname = i;
		g->vertices[i].incid_list = get_node(-1, NULL);
	}
}

void	set_edges(Graph *g, int esize)
{
	g->edges = (Edge *)malloc(esize * sizeof(Edge));
	g->esize = esize;

	for (int i = 0; i < esize; i++)
	{
		g->edges[i].ename = -1;
		g->edges[i].vtx1 = -1;
		g->edges[i].vtx2 = -1;
	}
}

void	build_graph(Graph *g)
{
	scanf("%d", &g->vsize);
	g->vertices = (Vertex *)malloc(sizeof(Vertex) * g->vsize);
	for (int i = 0; i < g->vsize; i++)
	{
		
	}
}