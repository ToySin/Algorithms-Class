#include <stdio.h>
#include <stdlib.h>

typedef struct Vertex
{
	// 정점의 이름
	int				v_name;
	// 인접리스트 형태로 구현
	struct Vertex	*inc;
}					Vertex;

// 그래프의 전체적인 구성은 다음과 같습니다.
// 각 정점에 대한 접근은 오로지 인덱스로만 접근합니다.(정점 자체를 저장하지 않음)
// Vertex *vertices[]는 인덱스로 접근한 각 정점의 인접 정점을 저장합니다.
// 헤더는 없으며 연결된 정점이 없으면 NULL입니다.(초기화)
typedef struct Graph
{
	int		v_size;
	// 정점의 방문정보를 저장하는 배열
	int		visited[100];
	Vertex	*vertices[100];
	// 정점에 속한 간선의 수를 저장하는 배열
	int		inc_count[100];
}			Graph;

// 인접 정점을 연결하기 위해 할당
Vertex	*get_vertex()
{
	Vertex	*node = (Vertex *)malloc(sizeof(Vertex));
	node->inc = NULL;
	return (node);
}

void	init_graph(Graph *graph)
{
	graph->v_size = 0;
	for (int i = 0; i < 100; i++)
	{
		graph->vertices[i] = NULL;
		graph->inc_count[i] = 0;
	}
}

// 각 정점에 대한 접근은 인덱스로만 접근합니다.
void	insert_vertex(Graph *graph)
{
	graph->v_size++;
}

void	insert_edge(Graph *graph, int u, int v)
{
	Vertex	*temp;

	// 둘다 있는 정점인 경우
	if (graph->v_size < u || graph->v_size < v)
		return ;

	// u인덱스 위치에 v정점을 연결하는 작업
	temp = get_vertex();
	temp->v_name = v;
	temp->inc = graph->vertices[u - 1];
	graph->vertices[u - 1] = temp;
	graph->inc_count[u - 1]++;

	// v인덱스 위치에 u정점을 연결하는 작업
	temp = get_vertex();
	temp->v_name = u;
	temp->inc = graph->vertices[v - 1];
	graph->vertices[v - 1] = temp;
	graph->inc_count[v - 1]++;
}

int	rDFS(Graph *graph, int v)
{
	int		v_idx;
	Vertex	*temp;
	int		cycle_flag;

	v_idx = v - 1;
	graph->visited[v_idx] = 1;
	temp = graph->vertices[v_idx];
	cycle_flag = 1;
	while (temp)
	{
		// 만약 방문할 곳이 없는데, inc_count가 2 이상이면 사이클이다.
		// inc_count가 1인 경우는 leaf인 경우이다.
		if (!graph->visited[temp->v_name - 1])
		{
			if (!rDFS(graph, temp->v_name))
				return (0);
			cycle_flag = 0;
		}
		temp = temp->inc;
	}
	if (cycle_flag && graph->inc_count[v_idx] > 1)
		return (0);
	return (1);
}

int	DFS(Graph *graph)
{
	// 실행전에 방문정보를 초기화한다.
	for (int i = 0; i < graph->v_size; i++)
		graph->visited[i] = 0;
	return (rDFS(graph, 1));
}

// DFS로 방문정보만 업데이트 해주면 된다.
// 사이클을 탐색해야되는 위의 함수와는 차이가 있다.
// 위의 함수는 방문정보를 확인 후 재귀를 실행했지만,
// 이 함수는 방문 후 방문정보를 확인하고 리턴한다.
void	rcount_island(Graph *graph, int v)
{
	int		v_idx;
	Vertex	*temp;

	v_idx = v - 1;
	if (graph->visited[v_idx])
		return ;
	graph->visited[v_idx] = 1;
	temp = graph->vertices[v_idx];
	while (temp)
	{
		rcount_island(graph, temp->v_name);
		temp = temp->inc;
	}
}

// 기본적으로 DFS형태로 동작하는 함수이다.
// 다만 한번의 DFS가 끝난 이후, 전체 정점에서 방문하지 않은 정점이 있을 경우
// 그 정점에서 다시 DFS를 시작한다.
// 방문정보는 기존의 정보를 유지하면서 실행한다.
int	count_island(Graph *graph)
{
	int	island;

	for (int i = 0; i < graph->v_size; i++)
		graph->visited[i] = 0;
	island = 0;
	for (int i = 0; i < graph->v_size; i++)
	{
		if (!graph->visited[i])
		{
			rcount_island(graph, i + 1);
			island++;
		}
	}
	return (island);
}

// inc_count 배열에서 최대값을 반환하기 위한 함수이다.
int	get_max(int *arr, int n)
{
	int	max_idx;

	max_idx = 0;
	for (int i = 0; i < n; i++)
		if (arr[max_idx] < arr[i])
			max_idx = i;
	return (arr[max_idx]);
}

// 중심을 출력하고 이심률을 구해서 리턴하는 함수이다.
// 정점이 한개인 경우엔 이심률이 0이라고 가정하였다.
int	get_eccentricity(Graph *graph)
{
	Vertex	*temp;
	int		leaf_parent_index_list[100];
	int		leaf_count;
	int		eccentricity;

	// 마지막에는 정점이 하나 남거나, 두개가 남는다.
	// 인접 정점의 수가 1이 최대가 될때가 끝이 난 상황이다.
	// 매번 시행마다 잎의 개수가 다를 수 있으므로 따로 leaf_count를 세어준다.
	// 잎 위치에 있는 정점들을 제거하는 가정을 하면서

	// 1. inc_count가 1인 잎들만 조사한다.
	// 3. 그 잎들의 부모 위치의 정점을 leaf_parent_index_list에
	//		인덱스 값으로 저장한다.
	// 4. 제거 된 잎들은 inc_count가 0으로 고정된다.
	//
	// inc_count의 개수를 하나씩 줄여나간다.
	eccentricity = 0;
	while (get_max(graph->inc_count, graph->v_size) > 1)
	{
		leaf_count = 0;
		for (int i = 0; i < graph->v_size; i++)
		{
			if (graph->inc_count[i] == 1)
			{
				temp = graph->vertices[i];

				while (temp)
				{
					// 잎을 실제로 제거한 것이 아니기 때문에
					// 1-2-3-... 으로 연결 된 그래프가 있다면
					// 1을 먼저 제거하면 (1)-2-3-... 에서 2가 잎이 되는데
					// (1)은 이미 제거 되었으므로 조사 대상에서 제외합니다.
					if (graph->inc_count[temp->v_name - 1])
					{
						leaf_parent_index_list[leaf_count] = temp->v_name - 1;
						leaf_count++;
					}
					temp = temp->inc;
				}
				graph->inc_count[i] = 0;
			}
		}
		// 이번 조사에서 얻은 정보로 inc_count를 갱신합니다.
		// 다만 값을 줄이는 도중 해당 정점의 inc_count가 1이 되면
		// 더이상 줄이지 않습니다. 1-2-1 같은 경우에는 위 조건이 없을 시
		// 0-0-0이 됩니다. 0-1-0의 형태로 만들어 주기 위함입니다. (중심이 1개)
		for (int j = 0; j < leaf_count; j++)
			if (graph->inc_count[leaf_parent_index_list[j]] > 1)
				graph->inc_count[leaf_parent_index_list[j]]--;
		eccentricity++;
	}
	leaf_count = -1;
	for (int i = 0; i < graph->v_size; i++)
	{
		if (graph->inc_count[i])
		{
			leaf_count++;
			printf("%d ", i + 1);
		}
	}
	// 중심이 두개라면 이심률을 1 더해줍니다.
	// 중심 서로를 거쳐가는 경로 +1
	if (leaf_count)
		eccentricity++;
	return (eccentricity);
}

int	main()
{
	Graph	graph;
	int		n, m;
	int		u, v;

	scanf("%d %d", &n, &m);
	init_graph(&graph);
	graph.v_size = n;
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d", &u, &v);
		insert_edge(&graph, u, v);
	}

	// 사이클 여부를 먼저 검사합니다.
	// 사이클이 없으면 1이 리턴됩니다.
	if (DFS(&graph))
	{
		// 방문하지 않은 정점이 있는지 확인합니다.
		for (int i = 0; i < graph.v_size; i++)
			if (!graph.visited[i])
			{
				// 사이클은 없지만, 인접요소가 2개 이상인 경우 동작합니다.
				printf("%d", count_island(&graph));
				return (0);
			}
		// 트리 구조인 경우 동작합니다.
		printf("%d", get_eccentricity(&graph));
		return (0);
	}
	else
	{
		// 사이클이 있는 경우 동작합니다.
		printf("%d", count_island(&graph));
		return (0);
	}
}

/* cycle
9 8
6 4
8 7
3 1
3 4
1 6
3 2
5 7
4 2
*/

/* eccentricity
9 8
8 5
1 4
3 7
6 4
4 3
9 6
1 2
6 8
*/
