#include "node.h"

Node *constructWheel(int n)
{
	Node *start = new Node(1);
	Node *current= start;

	for (int i = 2; i < n; i++)
	{
		current->next = new Node(i);
		current = current->next;
	}
	current->next = new Node(n, start);
	return start;
}
