#include <stdio.h>
#include <stdlib.h>

void	swap(int *a, int *b)
{
	int	temp = *a;
	*a = *b;
	*b = temp;
}

int	main()
{
	int	*arr;
	int	N;

	scanf("%d", &N);
	if (!(arr = (int *)malloc(sizeof(int))))
		return 0;
	for (int i = 0; i < N; i++)
		scanf("%d", arr + i);
	


	free(arr);
	return 0;
}