#include <iostream>
#include "node.h"
using namespace std;

Node *constructWheel(int n);
void printWheel(Node *start);
void play(Node *start, int m);

int main()
{
	int N, M;
	cout << "What is N: ";
	cin >> N;
	cout << "What is M: ";
	cin >> M;

	Node *start = constructWheel(N);
	
	play(start, M);
}
