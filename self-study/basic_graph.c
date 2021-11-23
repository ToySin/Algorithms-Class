#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int edgeId;
	struct node *next;
} Node;

typedef struct vertex
{
	int vname;
	Node *incid_list;
} Vertex;

typedef struct edge
{
	int ename;
	int vtx1, vtx2;
	int weight;
} Edge;

typedef struct graph
{
	Vertex *vertices;
	int	vsize;
	Edge *edges;
	int esize;
} Graph;

Node	*get_node(int eid, Node *next)
{
	Node *node = (Node *)malloc(sizeof(Node));
	node->edgeId = eid;
	node->next = next;
	return node;
}

int opposite(Graph *g, Node *node, int vs)
{
	Edge e = g->edges[node->edgeId];
	return (e.vtx1 == vs) ? e.vtx2 : e.vtx1;
}

void	set_edges_arr(Graph *g, int eid, int v1, int v2, int w)
{
	g->edges[eid].ename = eid;
	g->edges[eid].vtx1 = v1;
	g->edges[eid].vtx2 = v2;
	g->edges[eid].weight = w;
}

void 	insert_incid_node(Graph *g, int eid, int vs, int vd)
{
	Node *node = g->vertices[vs].incid_list;
	Node *new_node;

	while (node->next && opposite(g, node->next, vs) < vd)
		node = node->next;

	new_node = get_node(eid, node->next);
	node->next = new_node;
}

void	add_edge(Graph *g, int eid, int v1, int v2, int w)
{
	set_edges_arr(g, eid, v1, v2, w);

	insert_incid_node(g, eid, v1, v2);
	if (v1 != v2)
		insert_incid_node(g, eid, v2, v1);
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
	int	vsize, esize;

	vsize = 7;
	esize = 21;

	set_vertices(g, vsize);
	set_edges(g, esize);
}

void	print_adj_vertices(Graph *g, int vid)
{
	Node *node = g->vertices[vid].incid_list->next;

	printf("%d:", vid);
	while (node)
	{
		printf("[%d,", opposite(g, node, vid));
		printf(" %d] ", g->edges[node->edgeId].weight);
		node = node->next;
	}
	printf("\n");
}

void	print_graph(Graph *g)
{
	for (int i = 0; i < g->vsize; i++)
		print_adj_vertices(g, i);
}

void	free_incid_list(Node *node)
{
	Node *p;

	while (node)
	{
		p = node->next;
		free(node);
		node = p;
	}
}

void	free_graph(Graph *g)
{
	for (int i = 0; i < g->vsize; i++)
		free_incid_list(g->vertices[i].incid_list);
	free(g->vertices);
	free(g->edges);
}