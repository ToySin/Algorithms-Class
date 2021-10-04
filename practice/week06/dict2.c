#include <stdio.h>
#include <stdlib.h>

int	searchKey(int *dict, int key, int start, int end);

int	main(void)
{
	int *dict;
	int	n, k;

	scanf("%d %d", &n, &k);
	if (!(dict = (int *)malloc(sizeof(int) * n)))
		return (0);
	for (int i = 0; i < n; i++)
		scanf("%d", &dict[i]);
	printf("%d", searchKey(dict, k, 0, n - 1));
	free(dict);
}

int	searchKey(int *dict, int key, int start, int end)
{
	int	mid;
	int max_n = end;

	while (start <= end)
	{
		mid = (start + end) / 2;	
		if (dict[mid] == key)
			return (mid);
		else if (dict[mid] > key)
			end = mid - 1;
		else
			start = mid + 1;
	}
	return (start > max_n ? max_n + 1 : start);
}