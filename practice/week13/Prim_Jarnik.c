#include <stdio.h>
#include <stdlib.h>

int	main()
{
	int	adj_matrix[100][100];
	int	mst[100];
	int	visited[100];

	int	n, m;
	int	v1, v2, weight;
	int	row, col;
	int min_row, min_col;

	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			adj_matrix[i][j] = 0;
		mst[i] = 0;
		visited[i] = 0;
	}
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d %d", &v1, &v2, &weight);
		adj_matrix[v1 - 1][v2 - 1] = weight;
		adj_matrix[v2 - 1][v1 - 1] = weight;
	}

	weight = 0;
	mst[0] = 0;
	visited[0] = 1;
	for (int i = 0; i < n - 1; i++)
	{
		min_row = 0;
		min_col = 0;
		for (row = 0; row <= i; row++)
		{
			for (col = 0; col < n; col++)
			{
				if (visited[col])
					continue;
				if (adj_matrix[mst[row]][col])
				{
					if (min_row == 0 && min_col == 0)
						min_row = mst[row];
					if (min_col == 0)
						min_col = col;
					if (adj_matrix[min_row][min_col] > adj_matrix[mst[row]][col])
					{
						min_row = mst[row];
						min_col = col;
					}
				}
			}
		}
		weight += adj_matrix[min_row][min_col];
		mst[i + 1] = min_col;
		visited[min_col] = 1;
	}

	for (int i = 0; i < n; i++)
		printf(" %d", mst[i] + 1);
	printf("\n%d", weight);
}
