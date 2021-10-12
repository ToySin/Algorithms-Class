#include "merge_sort.h"

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
	return 0;
}