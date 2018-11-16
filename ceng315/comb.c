#include <stdio.h>


int combinations(int n, int k)
{
	if (k > n-k)
		k = n-k;
	printf("(%d %d)\n", n, k);
	if (k == 0)
		return n;
	return n / k * combinations(n-1, k-1);
}

int main()
{
	combinations(24,20);
	return 0;
}
