#include <stdio.h>
#include <stdlib.h>

int		searchKey(int *dict, int key, int start, int end);

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
	int mid = (end + start) / 2;

	if (start > end)
		return (end < 0 ? -1 : end);
	if (dict[mid] == key)
		return (mid);
	else if (dict[mid] > key)
		return (searchKey(dict, key, start, mid - 1));
	else
		return (searchKey(dict, key, mid + 1, end));
}