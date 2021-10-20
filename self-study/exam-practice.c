#include <stdio.h>
#include <stdlib.h>

void upheap(Node *leaf)
{
	if (leaf == root)
		return;
	if (leaf->v > leaf->parent->v)
	{
		swap(leaf->v, leaf->parent->v);
		upheap(leaf->parent);
	}
}

void downheap(Node *root, int cur, int max)
{
	if (root->left == NULL)
		return;
	if (cur * 2 <= max)
		greater = root->left->v;
	if (cur * 2 + 1 <= max)
		if (greater < root->right->v)
			greater = root->right->v;
	if (greater > root->v)
		swap(greater, root->v);
		if (root->right->v)
}