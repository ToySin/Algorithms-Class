#include "priority_queue.h"


QNode	*getQNode()
{
	QNode	*node;
	if (!(node = (QNode *)malloc(sizeof(QNode))))
		return NULL;
	node->key = -1;
	node->elem = 0;
	node->link = NULL;
	return node;
}

PQueue	*createPQueue()
{
	PQueue	*pq;
	if (!(pq = (PQueue *)malloc(sizeof(PQueue))))
		return NULL;
	pq->front = NULL;
	pq->rare = NULL;
	return pq;
}

void	PQ_insertItem(PQueue *pq, int key, Elem elem)
{

}

Elem	PQ_removeMin(PQueue *pq)
{

}

int		PQ_size(PQueue *pq)
{
	int		cnt = 0;
	QNode	*temp = pq->front;

	while (temp != pq->rare)
	{
		cnt++;
		temp = temp->link;
	}
	return cnt + 1;
}

bool	PQ_isEmpty(PQueue *pq)
{
	return pq->front;
}

Elem	PQ_minElement(PQueue *pq)
{
	return pq->front->elem;
}

int		PQ_minKey(PQueue *pq)
{
	return pq->front->key;
}

void	PQ_emptyPQueueException()
{
	
}