#include <stdio.h>
#include <stdlib.h>

struct Vertex
{
	int	adj_v;
	int	weight;
	int	dist;
	struct Vertex	*link;
};

struct Graph
{
	struct Vertex	vertices[101];
	int	v_size;
};


struct Vertex	*get_vertex(int v2, int w)
{
	struct Vertex	*vertex;

	if (!(vertex = (struct Vertex *)malloc(sizeof(struct Vertex))))
		return (NULL);
	vertex->adj_v = v2;
	vertex->weight = w;
	return (vertex);
}

void	insert_inc(struct Vertex *v1, struct Vertex *v2)
{
	while (v1->link)
	{
		if (v2->weight < v1->link->weight)
			break ;
		v1 = v1->link;
	}
	v2->link = v1->link;
	v1->link = v2;
}

int	is_all_visited(int *visited, int n)
{
	for (int i = 1; i <= n; i++)
		if (!visited[i])
			return (0);
	return (1);
}

void	Prim_Jarnik(struct Graph *graph)
{
	int	visited[101];

	for (int i = 1; i <= graph->v_size; i++)
		visited[i] = 0;

	while (!is_all_visited(visited, graph->v_size))
	{

	}
}

int	main()
{
	struct Graph g;
	struct Vertex	*temp;
	int n, m;
	int v1, v2, w;

	scanf("%d %d", &n, &m);
	g.v_size = n;
	for (int i = 1; i <= n; i++)
	{
		g.vertices[i].link = NULL;
		g.vertices[i].dist = 20000;
	}
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d %d", &v1, &v2, &w);
		temp = get_vertex(v2, w);
		insert_inc(&g.vertices[v1], temp);
	}
	Prim_Jarnik(&g);
	return (0);
}
