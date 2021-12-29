#include <stdio.h>
#include <stdlib.h>

struct Edge;

typedef struct Inc
{
	struct Edge* e;
	struct Inc* link;
}Inc;

typedef struct Vertex
{
	int v_name;
	struct Vertex* list;
}Vertex;

typedef struct Edge
{
	int start;
	int end;
	int weight;
}Edge;

typedef struct Graph
{
	Vertex v[100];
	int vsize;
	Edge e[1000];
	int esize;
}Graph;

void insert_edge(Graph* g, Edge* e)
{
	Inc* node = (Inc*)malloc(sizeof(Inc));

	node->e = e;
	node->link = g->v[e->start - 1].list;
	g->v[e->start - 1].list = node;

	node = (Inc*)malloc(sizeof(Inc));
	node->e = e;
	node->link = g->v[e->end - 1].list;
	g->v[e->end - 1].list = node;
}

void print_v_weight(Graph* g)
{
	Inc* temp;
	int weight;

	for (int i = 0; i < g->vsize; i++)
	{
		temp = g->v[i].list;
		weight = 0;
		while (temp)
		{
			weight += temp->e->weight;
			temp = temp->link;
		}
		printf("%d %d\n", i + 1, weight);
	}
}

void free_graph(Graph* g)
{
	Inc* temp;
	Inc* dtemp;

	for (int i = 0; i < g->vsize; i++)
	{
		temp = g->v[i].list;
		while (temp)
		{
			dtemp = temp;
			temp = temp->link;
			free(dtemp);
		}
	}
}

int main()
{
	Graph g;
	int n, m;

	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++)
	{
		g.v[i].v_name = i + 1;
		g.v[i].list = NULL;
	}
	g.vsize = n;
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d %d", &g.e[i].start, &g.e[i].end, &g.e[i].weight);
		insert_edge(&g, &g.e[i]);
	}
	g.esize = m;
	print_v_weight(&g);
	free_graph(&g);
	return (0);
}
