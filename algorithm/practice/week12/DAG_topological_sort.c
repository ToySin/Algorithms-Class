#include <stdio.h>
#include <stdlib.h>

struct Vertex;
struct Edge;
struct Inc;

typedef struct Node
{
	struct Vertex *vertex;
	struct Node *link;
} Node;

typedef struct Queue
{
	Node *front;
	Node *rare;
} Queue;

Node *get_node()
{
	Node *node = (Node *)malloc(sizeof(Node));
	node->vertex = NULL;
	node->link = NULL;
	return node;
}

int is_queue_empty(Queue *q)
{
	return !q->front || !q->rare;
}

void enqueue(Queue *q, struct Vertex *v)
{
	Node *new_node = get_node();

	new_node->vertex = v;
	if (is_queue_empty(q))
	{
		q->front = new_node;
		q->rare = new_node;
	}
	else
	{
		q->rare->link = new_node;
		q->rare = new_node;
	}
}

struct Vertex *dequeue(Queue *q)
{
	struct Vertex *temp = q->front->vertex;
	Node *d_temp = q->front;

	q->front = q->front->link;
	if (q->front == NULL)
		q->rare = NULL;
	free(d_temp);
	return temp;
}


typedef struct Vertex
{
	char vname;
	struct Inc *in_list;
	struct Inc *out_list;
	int in_degree;
	int topological_order;
} Vertex;

typedef struct Edge
{
	Vertex *vs;
	Vertex *vd;
} Edge;

typedef struct Inc
{
	Edge *edge;
	struct Inc *link;
} Inc;

typedef struct Graph
{
	Vertex *vertices;
	int vsize;
	Edge *edges;
	int esize;
} Graph;

Inc *get_inc();
void set_vertices(Graph *g);
void input_in_edge(Vertex *vertex, Edge *in_edge);
void input_out_edge(Vertex *vertex, Edge *out_edge);
void set_edges(Graph *g);
void build_graph(Graph *g);

int search_and_get_vertex_index(Graph *g, char vname)
{
	for (int i = 0; i < g->vsize; i++)
		if (g->vertices[i].vname == vname)
			return i;
	return -1;
}


Inc *get_inc()
{
	Inc *node = (Inc *)malloc(sizeof(Inc));
	node->edge = NULL;
	node->link = NULL;
	return node;
}

void set_vertices(Graph *g)
{
	scanf("%d", &g->vsize);
	g->vertices = (Vertex *)malloc(g->vsize * sizeof(Vertex));
	for (int i = 0; i < g->vsize; i++)
	{
		getchar();
		scanf("%c", &g->vertices[i].vname);
		g->vertices[i].in_list = get_inc();
		g->vertices[i].out_list = get_inc();
		g->vertices[i].in_degree = 0;
		g->vertices[i].topological_order = 0;
	}
}

void input_in_edge(Vertex *vertex, Edge *in_edge)
{
	Inc *node = get_inc();

	node->edge = in_edge;
	node->link = vertex->in_list->link;
	vertex->in_list->link = node;
	vertex->in_degree++;
}

void input_out_edge(Vertex *vertex, Edge *out_edge)
{
	Inc *node = get_inc();

	node->edge = out_edge;
	node->link = vertex->out_list->link;
	vertex->out_list->link = node;
}

void set_edges(Graph *g)
{
	char vs, vd;
	int vs_idx, vd_idx;
	
	scanf("%d", &g->esize);
	g->edges = (Edge *)malloc(g->esize * sizeof(Edge));
	for (int i = 0; i < g->esize; i++)
	{
		getchar();
		scanf("%c %c", &vs, &vd);
		vs_idx = search_and_get_vertex_index(g, vs);
		vd_idx = search_and_get_vertex_index(g, vd);
		g->edges[i].vs = &g->vertices[vs_idx];
		g->edges[i].vd = &g->vertices[vd_idx];
		input_out_edge(&g->vertices[vs_idx], &g->edges[i]);
		input_in_edge(&g->vertices[vd_idx], &g->edges[i]);
	}
}

void build_graph(Graph *g)
{
	set_vertices(g);
	set_edges(g);
}

void topological_sort(Graph *g)
{
	Queue queue;
	int label;
	Vertex *v_temp;
	Inc *inc_temp;
	char *topo_order = (char *)malloc(g->vsize * sizeof(char));

	queue.front = NULL;
	queue.rare = NULL;

	for (int i = 0; i < g->vsize; i++)
		if (g->vertices[i].in_degree == 0)
			enqueue(&queue, &g->vertices[i]);
	
	label = 1;
	while (!is_queue_empty(&queue))
	{
		v_temp = dequeue(&queue);
		topo_order[label - 1] = v_temp->vname;
		v_temp->topological_order = label++;
		inc_temp = v_temp->out_list->link;
		while (inc_temp)
		{
			inc_temp->edge->vd->in_degree--;
			if (inc_temp->edge->vd->in_degree == 0)
				enqueue(&queue, inc_temp->edge->vd);
			inc_temp = inc_temp->link;
		}
	}
	if (label <= g->vsize)
		printf("0");
	else
		for (int i = 0; i < g->vsize; i++)
			printf("%c ", topo_order[i]);
}

void free_inc_list(Inc *header)
{
	Inc *temp;

	while (header->link)
	{
		temp = header->link;
		header->link = temp->link;
		free(temp);
	}
	free(header);
}

void free_graph(Graph *g)
{
	for (int i = 0; i < g->vsize; i++)
	{
		free_inc_list(g->vertices[i].in_list);
		free_inc_list(g->vertices[i].out_list);
	}
	free(g->vertices);
	free(g->edges);
}

int main()
{
	Graph g;

	build_graph(&g);
	topological_sort(&g);
	free_graph(&g);
}