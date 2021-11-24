#include <stdio.h>
#include <stdlib.h>

typedef struct Vertex
{
	int				v_name;
	struct Vertex	*inc;
}					Vertex;

typedef struct Graph
{
	int		v_size;
	Vertex	*vertices[100];
}			Graph;

Vertex	*get_vertex()
{
	Vertex	*node = (Vertex *)malloc(sizeof(Vertex));
	node->inc = NULL;
	return (node);
}

void	init_graph(Graph *graph)
{
	graph->v_size = 0;
	for (int i = 0; i < 100; i++)
		graph->vertices[i] = NULL;
}

void	insert_vertex(Graph *graph)
{
	graph->v_size++;
}

void	insert_edge(Graph *graph, int u, int v)
{
	Vertex	*temp;

	if (graph->v_size < u || graph->v_size < v)
		return ;

	temp = get_vertex();
	temp->v_name = v;
	temp->inc = graph->vertices[u - 1];
	graph->vertices[u - 1] = temp;

	temp = get_vertex();
	temp->v_name = u;
	temp->inc = graph->vertices[v - 1];
	graph->vertices[v - 1] = temp;
}

int	DFS(Graph *graph)
{

}

int	main()
{
	Graph	graph;
	int		n, m;
	int		u, v;

	scanf("%d %d", &n, &m);

	graph.v_size = n;
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d", &u, &v);
		insert_edge(&graph, u, v);
	}
}
