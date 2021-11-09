#include <stdio.h>
#include <stdlib.h>

/**
 * @brief
 * 트리의 외부노드와 내부노드를 구별하는 방법
 * 양 쪽 자식이 모두 존재하면 내부노드
 * 양 쪽 자식이 모두 존재하지 않으면(NULL) 외부노드
 * expandExternal(Node *)에서 양쪽 자식이 모두 확장되므로
 * 한 쪽 자식만 존재하는 경우는 없다.
 */

typedef struct Node
{
	int	key;
	int height;
	struct Node	*parent;
	struct Node	*left;
	struct Node	*right;
}Node;

typedef struct Tree
{
	Node	*root;
}Tree;

Node	*getNode();
Tree	*initTree();

/**
 * @brief 
 * 질의 메소드
 * @param node 
 * @return int 
 */
int		isRoot(Node *node);
int		isExternal(Node *node);
int		isInternal(Node *node);
int		isBalanced(Node *node);
int		isLeft(Node* node);
int		isRight(Node* node);

/**
 * @brief 
 * 외부노드를 내부노드로 확장하는 메소드
 * @param node 
 */
void	expandExternal(Node *node);

/**
 * @brief 
 * 자신과 부모를 묶어서 삭제하는 메소드
 * @param node 
 */
void	reduceExternal(Node *node);

/**
 * @brief 
 * 기본 동작 메소드
 * @param t 
 */
void	insertItem(Tree *t);
void	searchItem(Tree *t);
void	deleteItem(Tree *t);

/**
 * @brief 
 * 높이갱신 메소드 - 두가지버전
 * 1. postRenewalHeight(Node *), 불균형 개조 후 전체 node의 높이를 갱신하는 메소드
 * 2. renewalHeight(Node *), 최근 삽입 된 node부터 root까지의 경로상의 node의 높이를 갱신하는 메소드
 * @param node 
 */
void	postRenewalHeight(Node *node);
void	renewalHeight(Node *node);

/**
 * @brief 
 * 트리의 불균형을 찾아서 개조하는 메소드
 */
void	searchAndFixAfterInsertion(Tree *t, Node *node);
void	searchAndFixAfterDelete(Tree *t, Node *node);
Node	*restructure(Node *z);

/**
 * @brief 
 * 중위순회 계승자를 찾아서 반환하는 메소드
 * @param node 
 * @return Node* 
 */
Node	*inOrderSucc(Node *node);

void	printPreorder(Tree *t);
void	preorder(Node *node);

void	freeTree(Tree *t);
void	freeNode(Node *node);

int	main()
{
	Tree	*tree = initTree();
	char	oper;
	
	while (1)
	{
		scanf("%c", &oper);
		if (oper == 'q')
			break;
		switch (oper)
		{
			case 'i':
				insertItem(tree);
				break;
			
			case 's':
				searchItem(tree);
				break;

			case 'd':
				deleteItem(tree);
				break;
			
			case 'p':
				printPreorder(tree);
				break;
		}
	}
	freeTree(tree);
	return 0;
}

Node	*getNode()
{
	Node	*node = (Node *)malloc(sizeof(Node));
	
	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;
	return node;
}

Tree	*initTree()
{
	Tree	*tree = (Tree *)malloc(sizeof(Tree));

	tree->root = getNode();
	return tree;
}

int		isRoot(Node *node)
{
	return !node->parent;
}

int		isExternal(Node *node)
{
	return (!(node->left) && !(node->right));
}

int		isInternal(Node *node)
{
	return (node->left || node->right);
}

/**
 * @brief
 * delta는 왼쪽과 오른쪽 자식의 높이 차이값이다.
 * delta의 절대값이 2이상 인 경우 불균형하다고 판단한다.
 * @param node 
 * @return int 
 */
int		isBalanced(Node *node)
{
	int	delta = node->left->height - node->right->height;

	return (-2 < delta) && (delta < 2);
}

int		isLeft(Node *node)
{
	if (isRoot(node))
		return 0;
	return node->parent->left == node;
}

int		isRight(Node *node)
{
	if (isRoot(node))
		return 0;
	return node->parent->right == node;
}

void	expandExternal(Node *node)
{
	node->left = getNode();
	node->left->parent = node;
	node->left->height = 0;
	node->right = getNode();
	node->right->parent = node;
	node->right->height = 0;
}

void	reduceExternal(Node *node)
{
	
	free(node->parent);
	free(node);
}

void	insertItem(Tree *t)
{
	Node	*temp = t->root;
	int		key;

	scanf("%d", &key);
	getchar();
	while (isInternal(temp))
	{
		if (key < temp->key)
			temp = temp->left;
		else
			temp = temp->right;
	}
	/**
	 * @brief 
	 * temp가 key의 삽입 위치가 되는 node이다.
	 * temp는 외부노드이므로 key 삽입 후 내부노드르 확장해주고
	 * 그로인한 높이 변화를 temp부터 root까지 갱신해준다.
	 * 이후 temp의 삽입으로 인한 높이 불균형이 발생하였는지 검사 및 개조한다.
	 */
	temp->key = key;
	expandExternal(temp);
	renewalHeight(temp);
	searchAndFixAfterInsertion(t, temp);
}

void	searchItem(Tree *t)
{
	Node	*temp = t->root;
	int	key;

	scanf("%d", &key);
	getchar();
	while (isInternal(temp))
	{
		if (temp->key == key)
		{
			printf("%d\n", temp->key);
			return;
		}
		else if (temp->key > key)
			temp = temp->left;
		else
			temp = temp->right;
	}
	printf("X\n");
}

void	deleteItem(Tree *t)
{
	Node	*temp = t->root;
	Node	*succ;
	int		key;

	scanf("%d", &key);
	getchar();
	while (isInternal(temp))
	{
		if (temp->key == key)
		{
			printf("%d\n", temp->key);

			/**
			 * @brief
			 * temp가 삭제해야 할 대상 노드이다.
			 * 1. 양쪽 자식이 모두 있는 경우, 중위순회 계승자를 통해 삭제한다.
			 * 2. 한쪽 자식만 있는 경우, 그 자식을 그대로 연결한다.
			 * 3. 양쪽 자식이 없는 경우, 단순하게 외부 노드로 바꾼다.
			 * 2, 3번의 경우에서 temp가 root인 경우를 따로 처리한다.
			 * 이후 높이를 갱신하고 균형을 맞춘다.
			 */
			if (isInternal(temp->left) && isInternal(temp->right))
			{
				succ = inOrderSucc(temp);
				temp->key = succ->key;
				if (isLeft(succ))
					succ->parent->left = succ->right;
				if (isRight(succ))
					succ->parent->right = succ->right;
				succ->right->parent = succ->parent;
				renewalHeight(succ->parent);
				searchAndFixAfterDelete(t, succ->parent);
				reduceExternal(succ->left);
			}
			else if (isInternal(temp->left))
			{
				if (isRoot(temp))
				{
					t->root = temp->left;
					temp->left->parent = NULL;
					renewalHeight(t->root);
					reduceExternal(temp->right);
					return;
				}
				if (isLeft(temp))
					temp->parent->left = temp->left;
				else if (isRight(temp))
					temp->parent->right = temp->left;
				temp->left->parent = temp->parent;
				renewalHeight(temp->parent);
				searchAndFixAfterDelete(t, temp->parent);
				reduceExternal(temp->right);
			}
			else if (isInternal(temp->right))
			{
				if (isRoot(temp))
				{
					t->root = temp->right;
					temp->right->parent = NULL;
					renewalHeight(t->root);
					reduceExternal(temp->left);
					return;
				}
				if (isLeft(temp))
					temp->parent->left = temp->right;
				else if (isRight(temp))
					temp->parent->right = temp->right;
				temp->right->parent = temp->parent;
				renewalHeight(temp->parent);
				searchAndFixAfterDelete(t, temp->parent);
				reduceExternal(temp->left);
			}
			else
			{
				if (isRoot(temp))
				{
					t->root = temp->right;
					reduceExternal(temp->left);
					return;
				}
				if (isLeft(temp))
					temp->parent->left = temp->left;
				else if (isRight(temp))
					temp->parent->right = temp->left;
				temp->left->parent = temp->parent;
				renewalHeight(temp->parent);
				searchAndFixAfterDelete(t, temp->parent);
				reduceExternal(temp->right);
			}
			return;
		}
		else if (key < temp->key)
			temp = temp->left;
		else if (temp->key < key)
			temp = temp-> right;
	}
	printf("X\n");
}

/**
 * @brief 
 * node의 높이는 양 쪽 자식의 높이 중 높은 것 + 1으로 갱신한다.
 * 현재 노드가 루트가 아니라면 부모노드로 가서 반복한다.(root node까지 갱신 후 종료)
 * @param node 
 */
void	renewalHeight(Node *node)
{
	node->height = node->left->height > node->right->height
		? node->left->height + 1 : node->right->height + 1;
	if (!isRoot(node))
		renewalHeight(node->parent);
}

/**
 * @brief 
 * 불균형 개조 후 높이 갱신을 위해 존재한다.
 * 후위순회로 구현했다.(양 쪽 자식의 높이가 갱신된 후 본인의 높이를 갱신 할 수 있기 때문에)
 * @param node 
 */
void	postRenewalHeight(Node *node)
{
	if (isInternal(node->left))
		postRenewalHeight(node->left);
	if (isInternal(node->right))
		postRenewalHeight(node->right);
	node->height = node->left->height > node->right->height
		? node->left->height + 1 : node->right->height + 1;
}

void	searchAndFixAfterInsertion(Tree *t, Node *node)
{
	Node	*z, *zp;

	/**
	 * @brief 
	 * node는 가장 최근에 삽입 된 노드이다.
	 * node에서 root로 올라가면서 처음으로 발견된 불균형 노드가 z이다.
	 * zp는 z의 부모노드이다. 개선된 z부트리를 연결하기 위해 존재한다.
	 * 만약 z가 root까지 검사했을 때 균형잡혔다면 함수를 종료한다.
	 */
	z = node;
	while (1)
	{
		if (isRoot(z) && isBalanced(z))
			return;
		else if (!isBalanced(z))
			break;
		z = z->parent;
	}
	zp = z->parent;

	/**
	 * @brief
	 * z가 root인 경우에는 z를 개조 후
	 * 트리의 root에 개조 된 부트리를 연결하면 된다.
	 * 부트리의 root의 부모는 NULL로 설정하여
	 * 전체 트리의 root임을 갱신한다.
	 */
	if (isRoot(z))
	{
		t->root = restructure(z);
		t->root->parent = NULL;
	}

	/**
	 * @brief 
	 * z가 zp의 왼쪽 자식인 경우에는
	 * 개조 된 부트리를 부모의 왼쪽에 연결한다.
	 * zp->left->parent = zp로 개조 된 부트리의 부모가
	 * zp임을 갱신한다.
	 */
	else if (isLeft(z))
	{
		z->parent->left = restructure(z);
		zp->left->parent = zp;
	}

	/**
	 * @brief 
	 * z가 zp의 오른쪽 자식인 경우에 수행한다.
	 * 원리는 왼쪽 자식일때 수행하는 것과 같다.
	 */
	else if (isRight(z))
	{
		z->parent->right = restructure(z);
		zp->right->parent = zp;
	}

	/**
	 * @brief 
	 * 개조 된 트리의 node들의 높이를 갱신한다.
	 * 처음 renewalHeight(Node *)와 다른점은
	 * 지금은 node부터 root까지의 조상노드의 경로만 개선하면 되는 것이 아니라
	 * 특정 부트리의 회전으로 인해 조상노드로의 경로에서 벗어난 노드들의
	 * 높이도 변화했기 때문에 전체적으로 높이 갱신을 수행한다.
	 */
	postRenewalHeight(t->root);
}

/**
 * @brief 
 * 전체적인 동작 방식은 searchAndFixAfterInsertion과 비슷하다.
 * 하지만 한번의 개조로 전체 트리의 균형이 맞춰진다는 보장이 없다.
 * 따라서 삭제 된 node의 위치를 매개변수로 받아서
 * 개조 이후에도 root까지의 경로를 모두 확인한다.
 * @param t 
 * @param node 
 */
void	searchAndFixAfterDelete(Tree *t, Node *node)
{
	Node	*z, *zp;

	z = node;
	/**
	 * @brief 
	 * 1. return으로 탈출하는 경우는 root가 균형잡힌경우
	 * 2. z != NULL으로 탈출하는 경우는 root가 불균형이라 개조 한 경우
	 */
	while (z != NULL)
	{
		while (1)
		{
			if (isRoot(z) && isBalanced(z))
				return;
			else if (!isBalanced(z))
				break;
			z = z->parent;
		}
		zp = z->parent;

		if (isRoot(z))
		{
			t->root = restructure(z);
			t->root->parent = NULL;
		}
		else if (isLeft(z))
		{
			z->parent->left = restructure(z);
			zp->left->parent = zp;
		}
		else if (isRight(z))
		{
			z->parent->right = restructure(z);
			zp->right->parent = zp;
		}
		postRenewalHeight(t->root);

		/**
		 * @brief 
		 * 현재 zp는 개조 된 부트리의 부모이다.
		 * zp 아래의 부트리는 개조 완료되어 균형이 맞으므로
		 * zp부터 다시 검사하면서 root까지 올라간다.
		 */
		z = zp;
	}
}

/**
 * @brief 
 * 불균형이 일어난 부트리의 root를 전달받아 개조한다.
 * @param z 
 * @return Node* 
 */
Node	*restructure(Node *z)
{
	Node	*x, *y;
	Node	*inorderRank[3];
	Node	*T[4];
	Node	*temp;
	int		min = 0;
	int		t_idx, i_idx;

	/**
	 * @brief 
	 * z의 높이가 더 높은 자식이 y, 같은 원리로 y의 자식 x를 선정한다.
	 * 이후 중위순위 배열에 x, y, z를 넣는다.
	 * 90->100점 나온 이유 - 양쪽 자식의 높이가 같은 경우
	 * 오른자식을 선택 -> 왼자식을 선택으로 변경 후 100점
	 */
	y = z->left->height >= z->right->height ? z->left : z->right;
	x = y->left->height >= y->right->height ? y->left : y->right;
	inorderRank[0] = x;
	inorderRank[1] = y;
	inorderRank[2] = z;

	/**
	 * @brief 
	 * 이진트리에서 중위순회란 오름차순 순서대로 읽는 것과 같다.
	 * 따라서 선정된 x, y, z의 오름차순 정렬 순서가 a, b, c가 된다.
	 */
	for (int i = 1; i < 3; i++)
		if (inorderRank[min]->key > inorderRank[i]->key)
			min = i;
	temp = inorderRank[min];
	inorderRank[min] = inorderRank[0];
	inorderRank[0] = temp;
	if (inorderRank[1]->key > inorderRank[2]->key)
	{
		temp = inorderRank[1];
		inorderRank[1] = inorderRank[2];
		inorderRank[2] = temp;
	}

	/**
	 * @brief 
	 * a, b, c의 순서가 오름차순이므로
	 * a, b, c의 각각의 부트리의 오름차순 순서도
	 * a->left a->right b->left ... c->right 순서가 된다.
	 * 따라서 a, b, c에서도 왼쪽, 오른쪽 자식 순으로 확인해보며
	 * 그 부트리가 a, b, c중 해당하지 않는다면 순서대로 T[0] ~ T[3]로 선정한다.
	 */
	t_idx = 0;
	i_idx = 0;
	while (t_idx < 4)
	{
		for (int i = 0; i < 3; i++)
			if (inorderRank[i_idx]->left == inorderRank[i])
				break;
			else if (i == 2)
				T[t_idx++] = inorderRank[i_idx]->left;
		for (int i = 0; i < 3; i++)
			if (inorderRank[i_idx]->right == inorderRank[i])
				break;
			else if (i == 2)
				T[t_idx++] = inorderRank[i_idx]->right;
		i_idx++;
	}

	/**
	 * 				b
	 * 		a				c
	 * 	T0		T1		T2		T3
	 */

	/**
	 * @brief 
	 * 위와 같은 형태로 구조를 개조한다.
	 * 이미 주어진 노드와 부트리를 단순히 연결해주기만 한다.
	 */
	inorderRank[1]->left = inorderRank[0];
	inorderRank[0]->parent = inorderRank[1];
	inorderRank[1]->right = inorderRank[2];
	inorderRank[2]->parent = inorderRank[1];
	inorderRank[0]->left = T[0];
	T[0]->parent = inorderRank[0];
	inorderRank[0]->right = T[1];
	T[1]->parent = inorderRank[0];
	inorderRank[2]->left = T[2];
	T[2]->parent = inorderRank[2];
	inorderRank[2]->right = T[3];
	T[3]->parent = inorderRank[2];
	
	/**
	 * @brief 
	 * 개조된 부트리의 root를 반환한다.
	 * 반환 된 부트리의 root는 전체 트리에서 어떤 노드의 자식으로 연결된다.
	 */
	return inorderRank[1];
}

Node	*inOrderSucc(Node *node)
{
	Node	*succ = node->right;

	while (isInternal(succ->left))
		succ = succ->left;
	return succ;
}

void	printPreorder(Tree *t)
{
	preorder(t->root);
	printf("\n");
}

void	preorder(Node *node)
{
	if (isExternal(node))
		return;
	printf(" %d", node->key);
	preorder(node->left);
	preorder(node->right);
}

void	freeTree(Tree *t)
{
	freeNode(t->root);
	free(t);
}

void	freeNode(Node *node)
{
	if (isInternal(node->left))
		freeNode(node->left);
	if (isInternal(node->right))
		freeNode(node->right);
	free(node);
}

/*
두번이상 개조 일어나는 코드 - 오류 찾음
i 50
i 30 
i 75
i 10
i 40
i 60
i 80
i 20
i 55
i 65
i 95
i 70
p
 50 30 10 20 40 75 60 55 65 70 80 95
d 40
40
p
 60 50 20 10 30 55 75 65 70 80 95
d 60
60
p
 65 50 20 10 30 55 75 70 80 95
p
 75 50 20 10 30 55 80 95 - 여기까지 정상임
*******************************************
					75
			50				80
	20			55				95
 10		30
*******************************************
d 75 -> 양쪽 자식 모두 내부노드일때 루트노드인 경우
75
p
 80 95 8001256 95
*/
