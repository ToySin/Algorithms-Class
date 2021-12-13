#include <stdio.h>
#include <stdlib.h>

int u[100];

struct Edge
{
	int start;
	int end;
	int weight;
};

void merge(int start, int end, int n)
{
	int target = end;

	for (int i = 0; i < n; i++)
		if (u[i] == target)
			u[i] = start;
}

void Kruskal(struct Edge *e, int n, int m)
{
	int weight;

	for (int i = 0; i < n; i++)
		u[i] = i;
	weight = 0;
	for (int i = 0; i < m; i++)
	{
		if (u[e[i].start - 1] != u[e[i].end - 1])
		{
			merge(u[e[i].start - 1], u[e[i].end - 1], n);
			printf(" %d", e[i].weight);
			weight += e[i].weight;
		}
	}
	printf("\n%d", weight);
}

int main()
{
	struct Edge e[1000];

	int n, m;

	scanf("%d %d", &n, &m);
	for (int i = 0; i < m; i++)
		scanf("%d %d %d", &e[i].start, &e[i].end, &e[i].weight);
	for (int i = 0; i < m - 1; i++)
	{
		for (int j = 0; j < m - 1 - i; j++)
		{
			if (e[j].weight > e[j + 1].weight)
			{
				struct Edge temp = e[j];
				e[j] = e[j + 1];
				e[j + 1] = temp;
			}
		}
	}
	Kruskal(e, n, m);
	return (0);
}
