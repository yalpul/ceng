#include <iostream>

struct Node
{
	Node(int a=0, Node *l=0, Node *r=0)
	: num(a), left(l), right(r) {}

	int num;
	Node *left, * right;
};

inline int max(int l, int r)
{
	return l > r ? l : r;
}
void interchange(Node *r)
{
	if (r)
	{
		Node *t = r->right;
		r->right = r->left;
		r->left = t;
		interchange(r->right), interchange(r->left);
	}
}
void inorder(Node *r)
{
	if (r)
	{
		inorder(r->left);
		std::cout << r->num << std::endl;
		inorder(r->right);
	}
}

int height(Node *root)
{
	if (root)
		return 1 + max(height(root->left), height(root->right));
	return -1;
}

int count(Node *r)
{
	if (!r)
		return 0;
	if (!r->left && !r->right)
		return 1;
	return count(r->left) + count(r->right);
}
int main()
{
	Node root, r1,r2,r11,r12,r21,r22;
	root.left = &r1, root.right = &r2;
	r1.left = &r11, r1.right = &r12;
	r2.left = &r21, r2.right = &r22;
	root.num = 4, r1.num = 3, r2.num = 2;
	r11.num = 1, r12.num = 9, r21.num = 7, r22.num = 8;
	std::cout << count(&root) << std::endl;
}
