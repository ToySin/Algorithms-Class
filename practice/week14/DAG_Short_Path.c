#include <stdio.h>
#include <stdlib.h>

int front = -1;
int rear = -1;
int queue[100];

void enqueue(int v)
{
	rear = (rear + 1) % 100;
	queue[rear] = v;
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
	Vertex vertices[100];
	int vsize;
}Graph;

Vertex *get_vertex()
{
	Vertex *node = (Vertex *)malloc(sizeof(Vertex));

	node->in_degree = 0;
	node->out_list = NULL;
	return (node);
}

void print_graph_info(Graph *g)
{
	for (int i = 0; i < g->vsize; i++)
	{
		printf("v_name: %d\n", g->vertices[i].v_name);
		printf("in_degree: %d\n", g->vertices[i].in_degree);
		printf("\n");
	}
}

int *DAG(Graph *g)
{
	Vertex *curr;
	Vertex *curr_out;
	int *topo = (int *)malloc(sizeof(int) * g->vsize);
	int topo_idx = 0;

	for (int i = 0; i < g->vsize; i++)
		if (g->vertices[i].in_degree == 0)
			enqueue(g->vertices[i].v_name);
	while (front != rear)
	{

		//print_graph_info(g);

		curr = &g->vertices[dequeue() - 1];
		curr_out = curr->out_list;
		topo[topo_idx++] = curr->v_name;
		while (curr_out)
		{
			g->vertices[curr_out->v_name - 1].in_degree--;
			if (g->vertices[curr_out->v_name - 1].in_degree == 0)
				enqueue(curr_out->v_name);
			curr_out = curr_out->out_list;
		}
	}
	if (topo_idx < g->vsize)
		printf("0");
	else
		for (int i = 0; i < g->vsize; i++)
			printf(" %d", topo[i]);
	printf("\n");
	return (topo);
}

void DAGPath(Graph *g)
{
	int *topo = DAG(g);
	int dist[100];
	Vertex *curr;
	Vertex *curr_out;

	for (int i = 0; i < g->vsize; i++)
		dist[i] = 30000;

	dist[topo[0] - 1] = 0;
	for (int i = 0; i < g->vsize - 1; i++)
	{

		for (int i = 0; i < g->vsize; i++)
			printf(" %d", dist[i]);
		printf("\n");

		curr = &g->vertices[topo[i] - 1];
		curr_out = curr->out_list;
		while (curr_out)
		{
			if (dist[curr_out->v_name - 1] > dist[curr->v_name - 1] + curr_out->weight)
				dist[curr_out->v_name - 1] = dist[curr->v_name - 1] + curr_out->weight;
			curr_out = curr_out->out_list;
		}
	}
	for (int i = 0; i < g->vsize; i++)
		printf(" %d", dist[i]);
	free(topo);
}

int main()
{
	Graph g;
	Vertex *temp;
	int n, m;
	int start, end, weight;

	scanf("%d %d", &n, &m);
	for (int i = 0; i < n; i++)
	{
		g.vertices[i].v_name = i + 1;
		g.vertices[i].in_degree = 0;
		g.vertices[i].out_list = NULL;
	}
	g.vsize = n;
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d %d", &start, &end, &weight);
		temp = get_vertex();
		temp->v_name = end;
		temp->weight = weight;
		temp->out_list = g.vertices[start - 1].out_list;
		g.vertices[start - 1].out_list = temp;
		g.vertices[end - 1].in_degree += 1;
	}
	DAGPath(&g);
	return (0);
}

/*
8 11
1 2 5
1 4 7
3 1 2
3 2 -3
3 4 6
4 5 2
5 6 4
5 7 -5
5 8 3
8 7 2
6 7 1
*/
