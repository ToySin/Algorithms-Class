#include <stdio.h>
#include <stdlib.h>

typedef struct Vertex
{
	int vname;
	int weight;
	int dist;
	struct Vertex *link;
}Vertex;

typedef struct Graph
{
	Vertex v[100];
	int vsize;
}Graph;

Vertex *get_vertex()
{
	Vertex *node = (Vertex *)malloc(sizeof(Vertex));

	node->link = 0;
	return (node);
}

void insert_edge(Graph *g, int v1, int v2, int weight)
{
	Vertex *node = get_vertex();

	node->vname = v2;
	node->weight = weight;
	node->link = g->v[v1 - 1].link;
	g->v[v1 - 1].link = node;
}

Vertex *get_min_vertex(Graph *g, int *visited, int n)
{
	int min_idx = 0;

	for (int i = 0; i < n; i++)
	{
		if (visited[i])
			continue ;
		else if (visited[min_idx])
			min_idx = i;
		else if (g->v[min_idx].dist > g->v[i].dist)
			min_idx = i;
	}
	return (&g->v[min_idx]);
}

int PrimJarnik(Graph *g)
{
	int visited[100];
	Vertex *curr;
	Vertex *curr_inc;
	int weight;

	for (int i = 0; i < g->vsize; i++)
	{
		g->v[i].dist = 30000;
		visited[i] = 0;
	}
	g->v[0].dist = 0;
	weight = 0;
	for (int i = 0; i < g->vsize; i++)
	{
		curr = get_min_vertex(g, visited, g->vsize);
		curr_inc = curr->link;
		printf(" %d", curr->vname);
		visited[curr->vname - 1] = 1;
		while (curr_inc)
		{
			if (visited[curr_inc->vname - 1] == 0)
				if (g->v[curr_inc->vname - 1].dist > curr_inc->weight)
					g->v[curr_inc->vname - 1].dist = curr_inc->weight;
			curr_inc = curr_inc->link;
		}
	}
	for (int i = 1; i < g->vsize; i++)
		weight += g->v[i].dist;
	printf("\n%d", weight);
}

int main()
{
	Graph g;
	int n, m;
	int v1, v2, w;

	scanf("%d %d", &n, &m);
	g.vsize = n;
	for (int i = 0; i < n; i++)
	{
		g.v[i].vname = i + 1;
		g.v[i].link = NULL;
	}
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d %d", &v1, &v2, &w);
		insert_edge(&g, v1, v2, w);
		insert_edge(&g, v2, v1, w);
	}
	PrimJarnik(&g);
	//free
	return (0);
}
