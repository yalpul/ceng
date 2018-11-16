#include <iostream>
#include <random>

#include <time.h>

using namespace std;

int randint(int min, int max)
{
	int range = max - min + 1;
	return rand() % range + min;
}

int n = 800000;
int main()
{
	srand(time(NULL));
	int a[n], rnum, i;
	bool used[n];

	for (i = 0; i < n; i++)
		used[i] = false;

	for (i = 0; i < n; i++)
	{
		do rnum = randint(1, n);
		 while (used[rnum-1]);

		a[i] = rnum;
		used[rnum-1] = true;
	}

	for (i = 0; i < n; i++)
		cout << a[i] << ", ";
	
	cout <<endl;
}
