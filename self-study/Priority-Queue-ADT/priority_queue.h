#ifndef __PRIORITY_QUEUE_H__
#define __PRIORITY_QUEUE_H__

#include <stdlib.h>
#include <stdbool.h>


typedef char Elem;

typedef struct QNode
{
	int				key;
	Elem			elem;
	struct QNode	*link;
}QNode;

typedef struct PQueue
{
	QNode	*front;
	QNode	*rare;
}PQueue;


QNode	*getQNode();
PQueue	*createPQueue();

void	PQ_insertItem(PQueue *pq, int key, Elem elem);
Elem	PQ_removeMin(PQueue *pq);

int		PQ_size(PQueue *pq);
bool	PQ_isEmpty(PQueue *pq);

Elem	PQ_minElement(PQueue *pq);
int		PQ_minKey(PQueue *pq);

void	PQ_emptyPQueueException();

#endif