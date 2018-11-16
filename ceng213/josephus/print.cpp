#include <iostream>
#include "node.h"
using namespace std;

void printWheel(Node *start)
{
	Node *first = start->next;

	cout << start->number << ", ";
	while (first != start)
	{

		cout << first->number << ", ";
		first = first->next;
	}
	cout << endl;
}
