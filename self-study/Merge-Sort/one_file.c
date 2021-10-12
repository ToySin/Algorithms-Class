#include <stdlib.h>
#include <stdio.h>

typedef struct Node
{
	int			data;
	struct Node	*next;
}Node;

typedef struct List
{
	Node	*header;
	Node	*end;
	int		size;
}List;

Node	*getNode()
{
	Node	*node;
	if (!(node = (Node *)malloc(sizeof(Node))))
		return NULL;
	node->next = NULL;
	return node;
}

void	initList(List *list)
{
	list->header = getNode();
	list->end = list->header;
	list->size = 0;
}

List	merge(List *left, List *right)
{
	List	list;
	Node	*l = left->header->next, *r = right->header->next;

	initList(&list);
	while (l && r)
	{
		if (l->data < r->data)
		{
			list.end->next = l;
			list.end = l;
			l = l->next;
		}
		else
		{
			list.end->next = r;
			list.end = r;
			r = r->next;
		}
	}
	while (l)
	{
		list.end->next = l;
		list.end = l;
		l = l->next;
	}
	while (r)
	{
		list.end->next = r;
		list.end = r;
		r = r->next;
	}
	return list;
}

List	mergeSort(List *list)
{
	List	left, right;
	Node	*temp = list->header;

	if (list->size == 1)
		return *list;
	
	initList(&left);
	initList(&right);

	for (int i = 0; i < list->size / 2; i++)
		temp = temp->next;
	left.header->next = list->header->next;
	left.end = temp;
	left.size = list->size / 2;
	right.header->next = temp->next;
	right.end = list->end;
	right.size = list->size - left.size;

	temp->next = NULL;

	left = mergeSort(&left);
	right = mergeSort(&right);
	return merge(&left, &right);
}

void	append(List *list)
{
	Node	*node = getNode();
	int		data;

	scanf("%d", &data);
	node->data = data;
	list->end->next = node;
	list->end = node;
	list->size++;
}

void	print(List *list)
{
	Node	*temp = list->header->next;

	while (temp)
	{
		printf(" %d", temp->data);
		temp = temp->next;
	}
	printf("\n");
}

int	main()
{
	List	list;
	int		N;

	initList(&list);
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		append(&list);
	print(&list);
	list = mergeSort(&list);
	print(&list);
	free(&list);
	return 0;
}