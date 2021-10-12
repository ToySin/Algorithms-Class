#ifndef __MERGE_SORT_H__
#define __MERGE_SORT_H__

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

Node	*getNode();
void	initList(List *list);

List	mergeSort(List *list);
List	merge(List *left, List *right);

void	append(List *list);
void	print(List *list);

void	freeList(List *list);

#endif