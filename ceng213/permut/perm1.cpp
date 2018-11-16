#include <iostream>
#include <random>
#include <time.h>
using namespace std;
int n = 8192;
int randint(int min, int max)
{
	int range = max - min + 1;
	return rand() % range + min;
}
bool contains(int * const a, int num)
{
	for (int i = 0; i < n; i++)
		if (a[i] == num)
			return true;
	return false;
}

int main()
{
	srand(time(NULL));
	int a[n], i;
	for (i = 0; i < n; i++)
		a[i] = 0;
	int rnum;
	for (i = 0; i < n; i++)
	{
		do rnum = randint(1, n);
			while (contains(a, rnum));
		a[i] = rnum;
	}

	for (i = 0; i < n; i++)
		cout << a[i] << ", ";
	
	cout <<endl;
}
