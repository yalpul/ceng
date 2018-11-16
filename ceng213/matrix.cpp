#include <iostream>

using namespace std;

bool contains(int *a, int n, int x)
{
	int i = 0, j = n - 1;
	while (*(a + i*n + j) != x)
	{
		/* Assert that we are in the boundaries */
		if (i > n-1 || j < 0)
			return false;

		if (*(a + n*i + j) < x)
			i++;
		else
			j--;
	}
	return true;
}

int main()
{
	int a[][4] = {{1,2,3,4},
							 {2,4,6,8},
							 {3,6,9,12},
							 {4,8,12,16}};
	
	int x;
	cin >> x;

	cout << contains(reinterpret_cast<int*>(a), 4, x) <<endl;
}
