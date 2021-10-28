#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
	int			key;
	struct Node	*next;
}Node;

Node	*getNode()
{
	Node	*node;
	if (!(node = (Node *)malloc(sizeof(Node))))
		return NULL;
	node->next = NULL;
	return node;
}

void	initHashTable(Node **table, int M)
{
	*table = (Node *)malloc(sizeof(Node) * M);
	for (int i = 0; i < M; i++)
		(*table)[i].next = NULL;
}

int		hashFunction(int key, int M)
{
	return key % M;
}

void	insertItem(Node *table, int M)
{
	int		key;
	int		hash_code;
	Node	*node = getNode();

	scanf("%d", &key);
	getchar();
	hash_code = hashFunction(key, M);
	node->key = key;
	node->next = table[hash_code].next;
	table[hash_code].next = node;
}

int		searchItem(Node *table, int M)
{
	int		key;
	int		hash_code;
	Node	*temp;

	scanf("%d", &key);
	getchar();
	hash_code = hashFunction(key, M);
	temp = table[hash_code].next;
	hash_code = 0;
	while (temp != NULL)
	{
		hash_code++;
		if (temp->key == key)
			return hash_code;
		temp = temp->next;
	}
	hash_code = 0;
	return hash_code;
}

int		deleteItem(Node *table, int M)
{
	int		key;
	int		hash_code;
	Node	*temp;
	Node	*wdnode;

	scanf("%d", &key);
	getchar();
	hash_code = hashFunction(key, M);
	temp = &table[hash_code];
	hash_code = 0;
	while (temp->next != NULL)
	{
		hash_code++;
		wdnode = temp->next;
		if (wdnode->key == key)
		{
			temp->next = wdnode->next;
			free(wdnode);
			return hash_code;
		}
		temp = temp->next;
	}
	hash_code = 0;
	return hash_code;
}

void	printTable(Node *table, int M)
{
	Node	*temp;

	for (int i = 0; i < M; i++)
	{
		if (table[i].next != NULL)
		{
			temp = table[i].next;
			while (temp != NULL)
			{
				printf(" %d", temp->key);
				temp = temp->next;
			}
		}
	}
	printf("\n");
}

void	freeTable(Node *table, int M)
{
	Node	*temp;
	Node	*dtemp;

	for (int i = 0; i < M; i++)
	{
		temp = table[i].next;
		while (temp != NULL)
		{
			dtemp = temp;
			temp = temp->next;
			free(dtemp);
		}
	}
	free(table);
}

int main()
{
	int		M;
	Node	*table;
	char	operator = 'i';

	scanf("%d", &M);
	getchar();
	initHashTable(&table, M);

	while (operator != 'e')
	{
		scanf("%c", &operator);
		getchar();
		switch(operator)
		{
			case 'i':
				insertItem(table, M);
				break;
			case 's':
				printf("%d\n", searchItem(table, M));
				break;
			case 'd':
				printf("%d\n", deleteItem(table, M));
				break;
			case 'p':
				printTable(table, M);
				break;
		}
	}

	freeTable(table, M);
	return 0;
}