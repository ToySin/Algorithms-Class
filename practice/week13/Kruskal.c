#include <stdio.h>

typedef struct Edge
{
	int	v1;
	int	v2;
	int	weight;
}		Edge;

typedef struct Union
{
	int	vertices[100];
	int	size;
}		Union;

void	init_union(Union *u, int n)
{
	for (int i = 0; i < n; i++)
		u->vertices[i] = i + 1;
	u->size = n;
}

int	is_one_union(Union *u)
{
	for (int i = 0; i < u->size; i++)
		if (u->vertices[i] != 1)
			return (0);
	return (1);
}

int	is_in_same_union(Union *u, int v1, int v2)
{
	return (u->vertices[v1 - 1] == u->vertices[v2 - 1]);
}

void	union_vertex(Union *u, int v1, int v2)
{
	int	dest_union;
	int	src_union;

	if (u->vertices[v1 - 1] < u->vertices[v2 - 1])
	{
		dest_union = u->vertices[v1 - 1];
		src_union = u->vertices[v2 - 1];
	}
	else
	{
		dest_union = u->vertices[v2 - 1];
		src_union = u->vertices[v1 - 1];
	}
	for (int i = 0; i < u->size; i++)
		if (u->vertices[i] == src_union)
			u->vertices[i] = dest_union;
}

int	main()
{
	int		n, m, total;
	Edge 	edges[1000];
	Union	u;

	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++)
		scanf("%d %d %d", &edges[i].v1, &edges[i].v2, &edges[i].weight);

	for (int i = 0; i < m - 1; i++)
	{
		for (int j = 0; j < m - i - 1; j++)
		{
			if (edges[j].weight > edges[j + 1].weight)
			{
				Edge	temp = edges[j];
				edges[j] = edges[j + 1];
				edges[j + 1] = temp;
			}
		}
	}
	init_union(&u, n);
	m = 0;
	total = 0;
	while (!is_one_union(&u))
	{
		if (!is_in_same_union(&u, edges[m].v1, edges[m].v2))
		{
			union_vertex(&u, edges[m].v1, edges[m].v2);
			printf("%d\n", edges[m].weight);
			total += edges[m].weight;
		}
		m++;
	}
	printf("\n%d", total);
	return (0);
}


/*
6 9
1 2 3
1 3 20
2 4 25
2 5 17
3 4 34
3 5 1
3 6 12
4 5 5
5 6 37
*/


/*
5 7
1 2 75
1 4 95
1 3 51
2 4 9
4 3 19
4 5 42
3 5 31
*/
