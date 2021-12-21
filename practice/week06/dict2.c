#include <stdio.h>
#include <stdlib.h>

void	createDict(int **pdict, int n);
void	insertKey(int *dict, int n);
int		searchKey(int *dict, int key, int start, int end);

int	main(void)
{
	int *dict;
	int	n, k;

	scanf("%d %d", &n, &k);
	createDict(&dict, n);
	for (int i = 0; i < n; i++)
		insertKey(dict, i);
	printf("%d", searchKey(dict, k, 0, n - 1));
}

void	createDict(int **pdict, int n)
{
	if (!(*pdict = (int *)malloc(sizeof(int) * n)))
		return;
}

void	insertKey(int *dict, int n)
{
	int key;

	scanf("%d", &key);
	
	for (int i = n; i >= 0; i--)
	{
		if (!i)
			dict[0] = key;
		else if (dict[i - 1] <= key)
		{
			dict[i] = key;
			break;
		}
		else
			dict[i] = dict[i - 1];
	}
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