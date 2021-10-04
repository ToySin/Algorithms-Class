#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	int num;
	struct Node* left;
	struct Node* right;
} Node;

typedef struct Tree {
	Node* root;
} Tree;

Node* getnode() {
	Node* node = (Node*)malloc(sizeof(Node));
	node->left = NULL;
	node->right = NULL;
	return node;
}

Tree* initTree() {
	Tree* tree = (Tree*)malloc(sizeof(Tree));
	tree->root = NULL;
	return tree;
}

Node* pre_travel(Node* root, int target) {
	if (root == NULL) return NULL;
	if (root->num == target) return root;
	Node* l = pre_travel(root->left, target);
	if (l) return l;
	Node* r = pre_travel(root->right, target);
	if (r) return r;
}

void pre_print(Node* root) {
	if (root == NULL) return;
	printf("%d ", root->num);
	pre_print(root->left);
	pre_print(root->right);
}

void add(Tree* tree, int par, int left, int right) {
	if (tree->root == NULL) {
		Node* node = getnode();
		node->num = par;
		tree->root = node;
	}

	Node* parent = pre_travel(tree->root, par);
	if (left) {
		Node* node = getnode();
		node->num = left;
		parent->left = node;
	}
	if (right) {
		Node* node = getnode();
		node->num = right;
		parent->right = node;
	}
}

void travel_user(Tree* tree, char* str) {
	Node* pnode = tree->root;
	while ((*str) != '\0') {
		if ((*str) == 'R') {
			printf(" %d", pnode->num);
			pnode = pnode->right;
		}
		else if ((*str) == 'L') {
			printf(" %d", pnode->num);
			pnode = pnode->left;
		}
		str++;
	}
	printf(" %d", pnode->num);
	printf("\n");
}

void free_tree(Node* par) {
	if (par->left) free_tree(par->left);
	if (par->right) free_tree(par->right);
	free(par);
}

void pre_add_sol(Node** parent) {
	int par, left, right;
	scanf("%d %d %d", &par, &left, &right);

	(*parent) = getnode();
	(*parent)->num = par;

	Node** parent_left = &((*parent)->left);
	Node** parent_right = &((*parent)->right);

	if (left) pre_add_sol(parent_left);
	if (right) pre_add_sol(parent_right);
}

void pre_add(Tree* tree, int N) {
	Node** root = &(tree->root);
	pre_add_sol(root);
}

int main() {
	Tree* tree = initTree();
	int N, par, left, right;
	char oper[101];

	/*
	add(tree, 5, 3, 9);
	add(tree, 3, 8, 15);
	add(tree, 8, 0, 2);
	add(tree, 2, 0, 0);
	add(tree, 15, 0, 0);
	add(tree, 9, 7, 10);
	add(tree, 7, 12, 0);
	add(tree, 12, 0, 0);
	add(tree, 10, 0, 0);

	travel_user(tree, "RLL");
	travel_user(tree, "LL");
	travel_user(tree, "LR");
	*/

	
	scanf("%d", &N);

	/*
	for (int i = 0; i < N; i++) {
		scanf("%d %d %d", &par, &left, &right);
		add(tree, par, left, right);
	}
	*/

	pre_add(tree, N);

	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%s", oper);
		getchar();
		travel_user(tree, oper);
	}

	free_tree(tree->root);

	return 0;
}

