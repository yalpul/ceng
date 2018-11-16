/*
 * construct complete tree
 * from sorted vector O(N)
 */
 
#include <iostream>
#include <cstdlib>
#include <vector>
struct Node
{
	int data;
	Node *left, *right;
};

void free_tree(Node *n)
{
	if (n)
	{
		free_tree(n->left);
		free_tree(n->right);
		delete n;
	}
}
		
void inorder(Node *n)
{
	if (!n)
		return;
	inorder(n->left);
	std::cout << n->data << " ";
	inorder(n->right);
}

int smear(int x)
{
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;
	return x;
}

Node *util_construct_bst(const std::vector<int>& vec, int low, int high)
{
	int size = high - low;
	int root = low + smear(size)/2;
	if (size <= 0)
		return NULL;
	else if (size == 1)
	{
		Node *node = new Node;
		node->data = vec[low];
		node->left = node->right = NULL;
		return node;
	}

	Node *left = util_construct_bst(vec, low, root);
	Node *right = util_construct_bst(vec, root+1, high);
	Node *node = new Node;
	node->left = left;
	node->right = right;
	node->data = vec[root];
	return node;
}

Node *construct_bst(const std::vector<int>& vec)
{
	return util_construct_bst(vec, 0, vec.size());
}

int main(int argc, char **argv)
{
	int num = atoi(argv[1]);
	std::vector<int> vec(num);
	for (int i = 0; i < num; i++)
		vec[i] = i;
	
	Node *n = construct_bst(vec);
	//inorder(n);
	free_tree(n);
}
