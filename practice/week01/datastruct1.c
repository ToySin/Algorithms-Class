#include <stdlib.h>
#include <stdio.h>

typedef char Elem;

typedef struct Node {
	Elem elem;
	struct Node* prev;
	struct Node* next;
} Node;

typedef struct List {
	Node* header;
	Node* trailer;
	int size;
} List;

Node* getnode() {
	Node* node = (Node*)malloc(sizeof(Node));
	node->prev = NULL;
	node->next = NULL;
	return node;
}

List* createList() {
	List* list = (List*)malloc(sizeof(List));
	list->header = getnode();
	list->trailer = getnode();
	list->header->next = list->trailer;
	list->trailer->prev = list->header;
	list->size = 0;
	return list;
}

void travel_list(List* list) {
	Node* pnode = list->header;

	while (pnode != list->trailer) {
		//�۾�
		pnode = pnode->next;
	}
}

void add(List* list, Elem e, int r) {
	if ((r < 0) || (r > list->size + 1)) {
		printf("invalid position\n");
		return;
	}

	Node* pnode = list->header;
	Node* new_node = getnode();
	new_node->elem = e;

	for (int i = 0; i < r; i++) pnode = pnode->next;

	new_node->next = pnode;
	new_node->prev = pnode->prev;
	pnode->prev->next = new_node;
	pnode->prev = new_node;
	list->size++;
}

Elem delete(List* list, int r) {
	if ((r < 0) || (r > list->size)) {
		printf("invalid position\n");
		return;
	}
	Node* pnode = list->header;
	Elem rst;

	for (int i = 0; i < r; i++) pnode = pnode->next;

	rst = pnode->elem;
	pnode->prev->next = pnode->next;
	pnode->next->prev = pnode->prev;
	list->size--;

	free(pnode);

	return rst;
}

Elem get(List* list, int r) {
	if ((r < 0) || (r > list->size)) {
		printf("invalid position\n");
		return '\0';
	}
	Node* pnode = list->header;
	for (int i = 0; i < r; i++) pnode = pnode->next;
	return pnode->elem;
}

void print_list(List* list) {
	Node* pnode = list->header;
	for (int i = 0; i < list->size; i++) {
		pnode = pnode->next;
		printf("%c", pnode->elem);
	}
	printf("\n");
}

void free_list(List* list) {
	Node* pnode = list->header;
	Node* temp = list->header;

	while (pnode) {
		pnode = pnode->next;
		free(temp);
		temp = pnode;
	}
	free(list);
}

int main() {
	List* list;
	list = createList();
	int N;
	char oper, alp;
	int rank;

	scanf("%d", &N);
	
	for (int i = 0; i < N; i++) {
		getchar();
		scanf("%c", &oper);

		switch (oper) {
		case 'A':
			scanf("%d %c", &rank, &alp);
			add(list, alp, rank);
			break;
		case 'D':
			scanf("%d", &rank);
			delete(list, rank);	
			break;
		case 'G':
			scanf("%d", &rank);
			Elem temp = get(list, rank);
			if (temp) printf("%c\n", temp);			
			break;
		case 'P':
			print_list(list);
			break;
		default:
			break;
		}
	}

	free_list(list);

	return 0;
}