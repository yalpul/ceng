/*
 * Given two lists
 * prints the ones at indices indicated by P
 * from L
 */

#include <iostream>
#include <vector>

using namespace std;

void printLots(const vector<int> & L, const vector<int> & P)
{
	for (auto i : P)
		cout << L[i] <<endl;
}
	
int main()
{
	vector<int> L {1,2,3,4,5,6,7,8}, P {2,3,4,5};
	printLots(L, P);
}
