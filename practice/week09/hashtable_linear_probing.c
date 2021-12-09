#include <stdio.h>
#include <stdlib.h>

int		hashFunction(int key, int M)
{
	return key % M;
}

void	insertItem(int *table, int M)
{
	int	key;
	int	hash_code;

	scanf("%d", &key);
	getchar();
	hash_code = hashFunction(key, M);
	while (table[hash_code] != 0)
	{
		hash_code = (hash_code + 1) % M;
		printf("C");
	}
	table[hash_code] = key;
	printf("%d\n", hash_code);
}

void	searchItem(int *table, int M)
{
	int	key;
	int	hash_code;
	int	end_cnt = 0;

	scanf("%d", &key);
	getchar();
	hash_code = hashFunction(key, M);
	while (1)
	{
		if ((end_cnt >= M) || (table[hash_code] == 0))
		{
			printf("-1\n");
			return;
		}
		if (key == table[hash_code])
		{
			printf("%d %d\n", hash_code, key);
			return;
		}
		hash_code = (hash_code + 1) % M;
		end_cnt++;
	}
}

int main()
{
	int		M, n;
	int		*table;
	char	operator = 'i';

	scanf("%d %d", &M, &n);
	if (!(table = (int *)malloc(sizeof(int) * M)))
		return 0;
	for (int i = 0; i < M; i++)
		table[i] = 0;

	while (operator != 'e')
	{
		scanf("%c", &operator);
		switch (operator)
		{
			case 'i':
				insertItem(table, M);
				break;
			case 's':
				searchItem(table, M);
				break;
		}
	}

	free(table);
	return 0;
}
