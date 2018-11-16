#include <iostream>
#include "node.h"
using namespace std;
void printWheel(Node*);

void play(Node *start, int m)
{
	Node *current = start;
	printWheel(start);
	while (current != current->next) // Stops when wheel has only one node
	{
		int x = m - 1;
		while (x--)
			current = current->next;

		Node *goner = current->next;
		current->next = goner->next;
		current = goner->next;
		cout << goner->number << " is going for sure!\n";
		delete goner;
		printWheel(current);
	}
	cout << "The only one remaining is: " << current->number <<endl;
}
