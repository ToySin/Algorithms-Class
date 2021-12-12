#include <stdio.h>
#include <stdlib.h>

int		get_min_idx(int *dist, int *visited, int n)
{
	int	min_idx;

	min_idx = 0;
	for (int i = 0; i < n; i++)
	{
		if (visited[min_idx])
			min_idx = i;
		if (visited[i] == 0)
			if (dist[min_idx] > dist[i])
				min_idx = i;
	}
	return (min_idx);
}

void	Prim(int adj[100][100], int n)
{
	int	dist[100];
	int	parent[100];
	int	visited[100];

	int	curr;
	int	count;
	int	weight;

	for (int i = 0; i < n; i++)
	{
		dist[i] = 20000;
		parent[i] = 20000;
		visited[i] = 0;
	}
	count = 0;
	weight = 0;
	dist[0] = 0;
	while (count < n)
	{
		curr = get_min_idx(dist, visited, n);
		visited[curr] = 1;
		printf(" %d", curr + 1);

		for (int i = 0; i < n; i++)
		{
			if (adj[curr][i])
			{
				if (adj[curr][i] < dist[i])
				{
					dist[i] = adj[curr][i];
					parent[i] = curr;
				}
			}
		}
		if (count)
			weight += adj[parent[curr]][curr];
		count += 1;
	}
	printf("\n%d", weight);
}

int	main(void)
{
	int	adj[100][100];
	int	n, m;
	int	v1, v2, w;

	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d %d", &v1, &v2, &w);
		adj[v1 - 1][v2 - 1] = w;
		adj[v2 - 1][v1 - 1] = w;
	}
	Prim(adj, n);
	return (0);
}
