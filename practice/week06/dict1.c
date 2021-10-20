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
	dict = (int *)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++)
		insertKey(dict, i);
	printf("%d", searchKey(dict, k, 0, n - 1));
	free(dict);
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
	int mid = (end + start) / 2;

	if (start > end)
		return (end <= 0 ? -1 : end);
	if (dict[mid] == key)
		return (mid);
	else if (dict[mid] > key)
		return (searchKey(dict, key, start, mid - 1));
	else
		return (searchKey(dict, key, mid + 1, end));
}