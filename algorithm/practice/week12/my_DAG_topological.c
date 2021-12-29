#include <stdio.h>
#include <stdlib.h>

typedef struct Vertex
{
	char			v_name;
	struct Vertex	*link;
}					Vertex;

typedef struct Graph
{
	Vertex	*vertices;
	int		v_size;
}			Graph;

int	main(void)
{
	Graph g;
	int		M;
	char	Vs, Vd;

	scanf("%d", &g.v_size);
	g.vertices = (Vertex *)malloc(sizeof(Vertex) * g.v_size);
	for (int i = 0; i < g.v_size; i++)
	{
		scanf("%c ", &g.vertices[i].v_name);
		g.vertices[i].link = NULL;
	}

	scanf("%d", &M);
	for (int i = 0; i < M; i++)
	{
		getchar();
		scanf("%c %c", &Vs, &Vd);
		g.vertices
	}
}
