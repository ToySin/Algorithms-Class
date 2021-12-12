#include <stdio.h>

int	vertices[101];
int	union_size;

struct Edge
{
	int	v1;
	int	v2;
	int	weight;
};

void	union_vertex(int v1, int v2)
{
	int	target_union = vertices[v2];
	for (int i = 1; i <= union_size; i++)
		if (vertices[i] == target_union)
			vertices[i] = vertices[v1];
}

int	is_one_union()
{
	for (int i = 1; i < union_size; i++)
		if (vertices[i] != vertices[i + 1])
			return (0);
	return (1);
}

void	Kruskal(struct Edge *edges)
{
	int weight = 0;
	int idx = 0;

	for (int i = 1; i <= union_size; i++)
		vertices[i] = i;
	while (!is_one_union())
	{
		if (vertices[edges[idx].v1] != vertices[edges[idx].v2])
		{
			union_vertex(edges[idx].v1, edges[idx].v2);
			printf(" %d", edges[idx].weight);
			weight += edges[idx].weight;
		}
		idx += 1;
	}
	printf("\n%d", weight);
}

int	main(void)
{
	struct Edge	edges[1000];
	int	n, m;

	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++)
		scanf("%d %d %d", &edges[i].v1, &edges[i].v2, &edges[i].weight);

	for (int i = 0; i < m - 1; i++)
	{
		for (int j = 0; j < m - 1 - i; j++)
		{
			if (edges[j].weight > edges[j + 1].weight)
			{
				struct Edge	temp = edges[j];
				edges[j] = edges[j + 1];
				edges[j + 1] = temp;
			}
		}
	}
	union_size = n;
	Kruskal(edges);
	return (0);
}
