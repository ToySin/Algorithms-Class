#include <stdio.h>
#include <stdlib.h>

int		hashFunction(int key, int M)
{
	return key % M;
}

int		hashRefunction(int key, int q)
{
	return q - (key % q);
}

void	insertItem(int *table, int M, int q)
{
	int	key;
	int	hash_code;
	int delta_offset;

	scanf("%d", &key);
	getchar();
	hash_code = hashFunction(key, M);
	delta_offset = hashRefunction(key, q);
	while (table[hash_code] != 0)
	{
		hash_code = (hash_code + delta_offset) % M;
		printf("C");
	}
	table[hash_code] = key;
	printf("%d\n", hash_code);
}

void	searchItem(int *table, int M, int q)
{
	int	key;
	int	hash_code;
	int	delta_offset;
	int	end_cnt = 0;

	scanf("%d", &key);
	getchar();
	hash_code = hashFunction(key, M);
	delta_offset = hashRefunction(key, q);
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
		hash_code = (hash_code + delta_offset) % M;
		end_cnt++;
	}
}

void	printTable(int *table, int M)
{
	for (int i = 0; i < M; i++)
		printf(" %d", table[i]);
	printf("\n");
}

int main()
{
	int		M, n, q;
	int		*table;
	char	operator = 'i';

	scanf("%d %d %d", &M, &n, &q);
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
				insertItem(table, M, q);
				break;
			case 's':
				searchItem(table, M, q);
				break;
			case 'p':
				printTable(table, M);
				break;
		}
	}
	printTable(table, M);

	free(table);
	return 0;
}