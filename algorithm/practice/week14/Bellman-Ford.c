#include <stdio.h>

typedef struct Edge
{
	int	start;
	int	end;
	int	weight;
}		Edge;

void	BellmanFord(Edge *edges, int n, int m, int s)
{
	int	dist[100];
	int	start, end, weight;

	s -= 1;
	for (int i = 0; i < n; i++)
		dist[i] = 30000;
	dist[s] = 0;
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < m; j++)
		{
			start = edges[j].start - 1;
			end = edges[j].end - 1;
			weight = edges[j].weight;
			if (dist[start] != 30000 && dist[end] > dist[start] + weight)
				dist[end] = dist[start] + weight;
		}
	}
	for (int i = 0; i < n; i++)
		if (i != s && dist[i] != 30000)
			printf("%d %d\n", i + 1, dist[i]);
}

int main()
{
	int		n, m, s;
	Edge	edge[1000];

	scanf("%d %d %d", &n, &m, &s);
	for (int i = 0; i < m; i++)
		scanf("%d %d %d", &(edge[i].start), &(edge[i].end), &(edge[i].weight));
	BellmanFord(edge, n, m, s);
	return (0);
}

/*
5 7 1
1 2 1
1 4 5
5 1 -2
3 5 3
3 4 1
1 3 2
3 2 -3
*/

/*
4 5 1
1 2 1
2 3 -2
3 1 2
3 4 1
1 4 5
*/

