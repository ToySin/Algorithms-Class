#include <stdio.h>
#include <stdlib.h>

typedef struct Kab
{
	int	a;
	int	b;
}Kab;

void	swap(int *a, int *b)
{
	int	temp = *a;
	*a = *b;
	*b = temp;
}

int	findPivot(int left, int right)
{
	return (left + right) / 2;
}

Kab	inplacePartition(int *arr, int pivot, int left, int right)
{
	Kab k;
	int	p = arr[pivot];

	swap(&arr[pivot], &arr[right]);
	k.a = left;
	k.b = right - 1;
	while (k.a <= k.b)
	{
		while (k.a <= k.b && arr[k.a] <= p)
			k.a++;
		while (k.a <= k.b && p <= arr[k.b])
			k.b--;
		if (k.a < k.b)
			swap(&arr[k.a], &arr[k.b]);
	}
	swap(&arr[k.a], &arr[right]);
	for (k.b++; arr[k.b] == p; k.b++);
	return k;
}

void	inplaceQuickSort(int *arr, int left, int right)
{
	Kab k;

	if (left >= right)
		return;
	k = inplacePartition(arr, (left + right) / 2, left, right);
	inplaceQuickSort(arr, left, k.a - 1);
	inplaceQuickSort(arr, k.b, right);
}

void	print(int *arr, int N)
{
	for (int i = 0; i < N; i++)
		printf(" %d", arr[i]);
	printf("\n");
}

int	main()
{
	int	*arr;
	int	N;

	scanf("%d", &N);
	if (!(arr = (int *)malloc(sizeof(int) * N)))
		return 0;
	for (int i = 0; i < N; i++)
		scanf("%d", arr + i);
	print(arr, N);
	inplaceQuickSort(arr, 0, N - 1);
	print(arr, N);
	free(arr);
	return 0;
}