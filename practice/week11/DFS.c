#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 100

typedef struct Vertex
{
	int				value;
	struct Vertex	*link;
}Vertex;

typedef struct Graph
{
	int		n;
	int		visited[MAX_VERTEX];
	Vertex	*adj_list[MAX_VERTEX];
}Graph;

Vertex	*getVNode()
{
	Vertex	*node = (Vertex *)malloc(sizeof(Vertex));
	node->link = NULL;
	return node;
}

void	initGraph(Graph *g)
{
	g->n = 0;
	for (int i = 0; i < MAX_VERTEX; i++)
		g->adj_list[i] = NULL;
}

void	insertEdge(Graph *g)
{
	int	u, v;
	Vertex	*u_node = getVNode();
	Vertex	*v_node = getVNode();
	Vertex	*temp;

	scanf("%d %d", &u, &v);
	u_node->value = u;
	v_node->value = v;

	temp = g->adj_list[u - 1];
	while (temp->link)
	{
		if (v < temp->link->value)
			break;
		temp = temp->link;
	}
	v_node->link = temp->link;
	temp->link = v_node;

	temp = g->adj_list[v - 1];
	while (temp->link)
	{
		if (u < temp->link->value)
			break;
		temp = temp->link;
	}
	u_node->link = temp->link;
	temp->link = u_node;
}

void	rDFS(Graph *g, int v)
{
	Vertex	*temp;

	if (!(g->visited[v - 1]))
	{
		printf("%d\n", v);
		g->visited[v - 1] = 1;
		temp = g->adj_list[v - 1]->link;
		while (temp)
		{
			rDFS(g, temp->value);
			temp = temp->link;
		}
	}
}

void	DFS(Graph *g, int s)
{
	for (int i = 0; i < g->n; i++)
		g->visited[i] = 0;
	rDFS(g, s);
}

void	freeGraph(Graph *g)
{
	Vertex	*temp;
	Vertex	*f_temp;

	for (int i = 0; i < g->n; i++)
	{
		temp = g->adj_list[i];
		while (temp->link)
		{
			f_temp = temp->link;
			temp->link = f_temp->link;
			free(f_temp);
		}
		free(temp);
	}
}

int	main()
{
	Graph	graph;
	int n, m, s;

	scanf("%d %d %d", &n, &m, &s);
	initGraph(&graph);
	graph.n = n;
	for (int i = 0; i < graph.n; i++)
		graph.adj_list[i] = getVNode();
	for (int i = 0; i < m; i++)
		insertEdge(&graph);
	DFS(&graph, s);
	freeGraph(&graph);
	return 0;
}


/*

5 7 1
1 2 
1 4 
5 1
3 5
4 3
3 1
2 3

1
2
3
4
5

*/