#ifndef _NODE_H_
#define _NODE_H_

struct Node{
	int number;
	struct Node *next;
	Node(int n = 0, Node *nextptr = nullptr)
	: number(n), next(nextptr) {}
};

#endif
