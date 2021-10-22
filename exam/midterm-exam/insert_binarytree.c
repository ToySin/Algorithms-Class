#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node* left;
    struct Node* right;
}Node;

typedef struct Tree
{
    Node* root;
}Tree;

Node* getNode()
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->left = NULL;
    node->right = NULL;
    return node;
}

Tree* createTree()
{
    Tree* t = (Tree*)malloc(sizeof(Tree));
    t->root = getNode();
    return t;
}

int isExternal(Node* node)
{
    return !(node->left) && !(node->right);
}

void    expandExternal(Node* node)
{
    node->left = getNode();
    node->right = getNode();
}

void    insertItem(Tree* t, int elem)
{
    Node* p = t->root;

    while (!isExternal(p))
    {
        if (elem < p->data)
            p = p->left;
        else
            p = p->right;
    }
    p->data = elem;
    expandExternal(p);
    return;
}

void    printPreorder(Node* node)
{
    if (isExternal(node))
        return;
    printf("%d ", node->data);
    printPreorder(node->left);
    printPreorder(node->right);
}

void    freeNode(Node* node)
{
    if (isExternal(node))
    {
        free(node);
        return;
    }
    freeNode(node->left);
    freeNode(node->right);
    free(node);
}

void    freeTree(Tree* t)
{
    freeNode(t->root);
    free(t);
}


int main() {
    int n, elem;
    Tree* t;

    scanf("%d", &n);
    t = createTree();

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &elem);
        insertItem(t, elem);
    }
    printPreorder(t->root);

    freeTree(t);
    return 0;
}