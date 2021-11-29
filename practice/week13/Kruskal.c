#include <stdio.h>
#include <stdlib.h>

// priority-queue에 edge-list ascending으로 넣고
// dequeue하면서 union-set에 vertex add하기,
// vertex의 양 끝점 모두가 union-set 안에 있으면 cycle이니까 out

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

int		is_in_union(Union *u, int vertex)
{
	for (int i = 0; i < u->size; i++)
		if (u->vertices[i] == vertex)
			return (1);
	return (0);
}

void	insert_union(Union *u, int vertex)
{
	u->vertices[u->size++] = vertex;
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

	m = 0;
	total = 0;
	while (u.size < n)
	{
		if (!is_in_union(&u, edges[m].v1) && !is_in_union(&u, edges[m].v2))
		{
			insert_union(&u, edges[m].v1);
			insert_union(&u, edges[m].v2);
			printf(" %d", edges[m].weight);
			total += edges[m].weight;
		}
		else if (!is_in_union(&u, edges[m].v1))
		{
			insert_union(&u, edges[m].v1);
			printf(" %d", edges[m].weight);
			total += edges[m].weight;
		}
		else if (!is_in_union(&u, edges[m].v2))
		{
			insert_union(&u, edges[m].v2);
			printf(" %d", edges[m].weight);
			total += edges[m].weight;
		}
		m++;
	}
	printf("\n%d", total);
	return (0);
}
