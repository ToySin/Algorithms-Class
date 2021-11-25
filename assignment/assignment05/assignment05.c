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
	int		visited[100];
	Vertex	*vertices[100];
	int		inc_count[100];
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
	{
		graph->vertices[i] = NULL;
		graph->inc_count[i] = 0;
	}
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
	graph->inc_count[u - 1]++;

	temp = get_vertex();
	temp->v_name = u;
	temp->inc = graph->vertices[v - 1];
	graph->vertices[v - 1] = temp;
	graph->inc_count[v - 1]++;
}

int	rDFS(Graph *graph, int v)
{
	int		v_idx;
	Vertex	*temp;
	int		cycle_flag;

	v_idx = v - 1;
	graph->visited[v_idx] = 1;
	temp = graph->vertices[v_idx];
	cycle_flag = 1;
	while (temp)
	{
		// 방문하기전에 이미 방문했는지를 본다.
		// 만약 방문할 곳이 없는데, inc_count가 2 이상이면
		// 사이클이다.
		// flag 하나 세워서 중간에 한번이라도 재귀 안돌면
		// 마지막 가서 검사?
		if (!graph->visited[temp->v_name - 1])
		{
			if (!rDFS(graph, temp->v_name))
				return (0);
			cycle_flag = 0;
		}
		temp = temp->inc;
	}
	if (cycle_flag && graph->inc_count[v_idx] > 1)
		return (0);
	return (1);
}

int	DFS(Graph *graph)
{
	for (int i = 0; i < graph->v_size; i++)
		graph->visited[i] = 0;
	return (rDFS(graph, 1));
}

void	rcount_island(Graph *graph, int v)
{
	int		v_idx;
	Vertex	*temp;

	v_idx = v - 1;
	if (graph->visited[v_idx])
		return ;
	graph->visited[v_idx] = 1;
	temp = graph->vertices[v_idx];
	while (temp)
	{
		rcount_island(graph, temp->v_name);
		temp = temp->inc;
	}
}

int	count_island(Graph *graph)
{
	int	island;

	for (int i = 0; i < graph->v_size; i++)
		graph->visited[i] = 0;
	island = 0;
	for (int i = 0; i < graph->v_size; i++)
	{
		if (!graph->visited[i])
		{
			rcount_island(graph, i + 1);
			island++;
		}
	}
	return (island);
}

int	get_max(int *arr, int n)
{
	int	max_idx;

	max_idx = 0;
	for (int i = 0; i < n; i++)
		if (arr[max_idx] < arr[i])
			max_idx = i;
	return (arr[max_idx]);
}

int	get_eccentricity(Graph *graph)
{
	Vertex	*temp;
	int		leaf_parent_index_list[100];
	int		leaf_count;
	int		eccentricity;

	eccentricity = 0;
	while (get_max(graph->inc_count, graph->v_size) > 1)
	{
		leaf_count = 0;
		for (int i = 0; i < graph->v_size; i++)
		{
			if (graph->inc_count[i] == 1)
			{
				temp = graph->vertices[i];
				while (temp)
				{
					if (graph->inc_count[temp->v_name - 1])
					{
						leaf_parent_index_list[leaf_count] = temp->v_name - 1;
						leaf_count++;
					}
					temp = temp->inc;
				}
				graph->inc_count[i] = 0;
			}
		}
		for (int j = 0; j < leaf_count; j++)
			if (graph->inc_count[leaf_parent_index_list[j]] > 1)
				graph->inc_count[leaf_parent_index_list[j]]--;
		eccentricity++;
	}
	leaf_count = -1;
	for (int i = 0; i < graph->v_size; i++)
	{
		if (graph->inc_count[i])
		{
			leaf_count++;
			printf("%d ", i + 1);
		}
	}
	if (leaf_count)
		eccentricity++;
	printf("\n%d", eccentricity);
	return (eccentricity);
}

int	main()
{
	Graph	graph;
	int		n, m;
	int		u, v;

	scanf("%d %d", &n, &m);
	init_graph(&graph);
	graph.v_size = n;
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d", &u, &v);
		insert_edge(&graph, u, v);
	}

	if (DFS(&graph))
	{
		for (int i = 0; i < graph.v_size; i++)
			if (!graph.visited[i])
			{
				printf("%d", count_island(&graph));
				return (0);
			}
		get_eccentricity(&graph);
		return (0);
	}
	else
	{
		printf("%d", count_island(&graph));
		return (0);
	}
}

/* cycle
9 8
6 4
8 7
3 1
3 4
1 6
3 2
5 7
4 2
*/

/* eccentricity
9 8
8 5
1 4
3 7
6 4
4 3
9 6
1 2
6 8
*/
