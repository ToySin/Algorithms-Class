#include <stdio.h>

int	is_visited_all(int *visited, int n)
{
	for (int i = 0; i < n; i++)
		if (!visited[i])
			return (0);
	return (1);
}

int	get_min_idx(int *dist, int *visited, int n)
{
	int	min_idx;

	min_idx = 0;
	for (int i = 0; i < n; i++)
	{
		if (visited[i])
			continue ;
		else if (visited[min_idx])
			min_idx = i;
		else if (dist[min_idx] > dist[i])
			min_idx = i;
	}
	return (min_idx);
}

void	Dijkstra(int adj[100][100], int n, int s)
{
	int	dist[100];
	int	visited[100];
	int	curr;
	int	new_dist;


	for (int i = 0; i < n; i++)
	{
		dist[i] = 10000;
		visited[i] = 0;
	}
	dist[s - 1] = 0;
	while (!is_visited_all(visited, n))
	{
		curr = get_min_idx(dist, visited, n);
		visited[curr] = 1;
		for (int i = 0; i < n; i++)
		{
			if (!adj[curr][i])
				continue ;
			new_dist = dist[curr] + adj[curr][i];
			if (new_dist < dist[i])
				dist[i] = new_dist;
		}
	}
	for (int i = 0; i < n; i++)
		if (i != (s - 1) && dist[i] != 10000)
			printf("%d %d\n", i + 1, dist[i]);
}

int main()
{
	int	adj_matrix[100][100];
	int	n, m, s;
	int	v1, v2, w;

	scanf("%d %d %d", &n, &m, &s);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			adj_matrix[i][j] = 0;
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d %d", &v1, &v2, &w);
		adj_matrix[v1 - 1][v2 - 1] = w;
		adj_matrix[v2 - 1][v1 - 1] = w;
	}
	Dijkstra(adj_matrix, n, s);
	return (0);
}

/*
5 7 1
1 2 1
1 4 5
5 1 10
3 5 3
4 3 1
3 1 2
2 3 2
*/

/*
8 12 7
1 2 1
2 4 2
4 7 7
3 6 1
6 1 4
7 6 9
7 8 1
1 3 2
2 7 5
1 4 1
2 5 2
7 5 2
*/

/*
5 3 2
1 2 1
1 3 1
1 4 1
*/
