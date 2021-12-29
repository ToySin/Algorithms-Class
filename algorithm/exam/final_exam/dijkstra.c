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
}

Vertex* get_min_vertex(Graph* g, int *dist, int *visited)
{
	int min_idx = 0;

	for (int i = 0; i < g->vsize; i++)
	{
		if (visited[i])
			continue;
		else if (visited[min_idx])
			min_idx = i;
		else if (dist[min_idx] > dist[i])
			min_idx = i;
	}
	return (&g->v[min_idx]);
}

void Dijkstra(Graph* g)
{
	int dist[100];
	int visited[100];
	Vertex* curr;
	Inc* curr_out;

	for (int i = 0; i < g->vsize; i++)
	{
		dist[i] = 100;
		visited[i] = 0;
	}
	dist[0] = 0;
	for (int i = 0; i < g->vsize; i++)
	{
		curr = get_min_vertex(g, dist, visited);
		curr_out = curr->list;
		visited[curr->v_name - 1] = 1;
		while (curr_out)
		{
			if (visited[curr_out->e->end - 1] == 0)
				if (dist[curr_out->e->end - 1] > dist[curr->v_name - 1] + 1)
					dist[curr_out->e->end - 1] = dist[curr->v_name - 1] + 1;
			curr_out = curr_out->link;
		}
	}
	for (int i = 0; i < g->vsize; i++)
		printf("%d %d\n", i + 1, dist[i]);
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
	Dijkstra(&g);
	free_graph(&g);
	return (0);
}
