#include <stdio.h>
#include <stdlib.h>

int front = -1;
int rear = -1;
int queue[100];

void enqueue(int vname)
{
	rear = (rear + 1) % 100;
	queue[rear] = vname;
}

int dequeue()
{
	front = (front + 1) % 100;
	return (queue[front]);
}

typedef struct Vertex
{
	int v_name;
	int weight;
	int in_degree;
	struct Vertex *out_list;
}Vertex;

typedef struct Graph
{
	Vertex v[100];
	int vsize;
}Graph;

void insert_edge(Graph *g, int start, int end, int weight)
{
	Vertex *node = (Vertex *)malloc(sizeof(Vertex));

	node->v_name = end;
	node->weight = weight;
	node->out_list = g->v[start - 1].out_list;
	g->v[start - 1].out_list = node;
	g->v[end - 1].in_degree += 1;
}

int *DAG(Graph *g)
{
	int topo[100];
	int topo_idx = 0;
	Vertex *curr;
	Vertex *curr_out;

	for (int i = 0; i < g->vsize; i++)
		if (g->v[i].in_degree == 0)
			enqueue(i + 1);
	while (front != rear)
	{
		curr = &g->v[dequeue() - 1];
		curr_out = curr->out_list;
		topo[topo_idx++] = curr->v_name - 1;
		while (curr_out)
		{
			g->v[curr_out->v_name - 1].in_degree -= 1;
			if (g->v[curr_out->v_name - 1].in_degree == 0)
				enqueue(curr_out->v_name);
			curr_out = curr_out->out_list;
		}
	}
	if (topo_idx < g->vsize)
		printf("0"); // cycle
	else
		for (int i = 0; i < g->vsize; i++)
			printf(" %d", topo[i]);
	return (topo);
}

void DAGShortPath(Graph *g)
{
	int topo[100] = DAG(g);
	int dist[100];
	Vertex *curr_out;

	for (int i = 0; i < g->vsize; i++)
		dist[i] = 30000;

	dist[topo[0]] = 0;
	for (int i = 0; i < g->vsize - 1; i++)
	{
		curr_out = g->v[topo[i]].out_list;
		while (curr_out)
		{
			if (dist[curr_out->v_name - 1] > dist[topo[i]] + curr_out->weight)
				dist[curr_out->v_name - 1] = dist[topo[i]] + curr_out->weight;
			curr_out = curr_out->out_list;
		}
	}
	for (int i = 0; i < g->vsize; i++)
		printf(" %d", dist[i]);
}

int main()
{
	Graph g;
	int n, m;
	int start, end, weight;

	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++)
	{
		g.v[i].v_name = i + 1;
		g.v[i].out_list = NULL;
		g.v[i].in_degree = 0;
	}
	g.vsize = n;
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d %d", &start, &end, &weight);
		insert_edge(&g, start, end, weight);
	}
	DAGShortPath(&g);
	// free graph;
	return (0);
}
