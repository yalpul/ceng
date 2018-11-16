/*
 * construct complete tree
 * from sorted vector in O(N) time
 */

#include <iostream>
#include <cstdlib>
#include <vector>
struct Node
{
	int data;
	Node *left, *right, *parent;
};

void inorder(Node *n)
{
	if (!n)
		return;
	inorder(n->left);
	std::cout << n->data << " ";
	inorder(n->right);
}

Node *leftmost(Node *n)
{
	while(n->left)
		n = n->left;
	return n;
}

Node *rightmost(Node *n)
{
	while(n->right)
		n = n->right;
	return n;
}

Node *succ(Node *n)
{
	if (n->right)
		return leftmost(n->right);
	
	Node *p = n->parent;
	while (p && n == p->right)
	{
		n = p;
		p = p->parent;
	}
	return p;
}

Node *empty_bst(int size)
{
	Node *n = new Node[size];

	int i;
	for (i = 0; i < (size-2)/2; i++)
	{
		n[i].left = &n[2*i+1];
		n[i].right = &n[2*(i+1)];
		n[i].parent = &n[(i-1)/2];
	}
	n[i].left = &n[2*i+1];
	n[i].right = size % 2 ? &n[2*(i+1)] : NULL;
	n[i].parent = &n[(i-1)/2];
	for (i++; i < size; i++)
	{
		n[i].parent = &n[(i-1)/2];
		n[i].left = NULL;
		n[i].right = NULL;
	}
	n[0].parent = NULL;
	
	return n;
}

Node *construct_bst(std::vector<int>& vec)
{
	Node *n = empty_bst(vec.size());

	Node *left = leftmost(n);
	Node *right = rightmost(n);

	Node *t = left;
	int i = 0;
	while (t != right)
	{
		t->data = vec[i++];
		t = succ(t);
	}
	t->data = vec[i];

	return n;
}

int main(int argc, char **argv)
{
	int num = atoi(argv[1]);
	std::vector<int> vec(num);
	for (int i = 0; i < num; i++)
		vec[i] = i;

	Node *root = construct_bst(vec);
	//inorder(root);
	delete[] root;
}
