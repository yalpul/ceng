#include <iostream>
#include <random>
#include <time.h>


int randint(int min, int max)
{
	int range = max - min + 1;
	return rand() % range + min;
}

int n = 1600000;

using namespace std;

int main()
{
	int a[n], i;

	for (int i = 0; i < n; i++)
		a[i] = i + 1;

	for (int i = 1; i < n; i++)
		swap(a[i], a[randint(0, i)]);


	for (i = 0; i < n; i++)
		cout << a[i] << ", ";
	
	cout <<endl;
}
	
