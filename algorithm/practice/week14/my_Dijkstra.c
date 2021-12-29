#include <stdio.h>
#include <stdlib.h>

struct Edge
{
	int	v1;
	int	v2;
	int	weight;
};

int	front = -1;
int	rear = -1;
int	queue[1000];

int	is_empty(void)
{
	return (front == rear);
}

int	enqueue(int v)
{
	rear = (rear + 1) % 1000;
	queue[rear] = v;
}

int	dequeue(void)
{
	front = (front + 1) % 1000;
	return (queue[front]);
}

void	Dijkstra(int n, int s)
{
	int	dist[100];
	int	curr_v;

	for (int i = 0; i < n; i++)
		dist[i] = 20000;
	dist[s - 1] = 0;
	enqueue(s);
	while (!is_empty())
	{
		curr_v = dequeue();
		// for each adj_v adj_info of curr_v
			if (dist[adj_v] > dist[curr_v] + weight(cu->adj_v)))
				dist[adj_v] = dist[curr_v] + weight~~;
			enqueue(adj_v);
	}
}

int	main(void)
{
	struct Edge	edges[1000];
	int			n, m, s;

	scanf("%d %d %d", &n, &m, &s);
	for (int i = 0; i < m; i++)
		scanf("%d %d %d", &edges[i].v1, &edges[i].v2, &edges[i].weight);
}
