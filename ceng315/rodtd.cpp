// 2^n time because of recursion and recomputations
#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

int rod(const vector<int> &p, int n)
{
	if (n==0)
		return 0;
	int max = -1;
	for (int i = 1; i <= n; i++)
		max = std::max(max, p[i] + rod(p, n-i));
	
	return max;
}

int main()
{
	vector<int> p = {0,1,5,8,9,10,17,17,20,24,30};
	cout << rod(p, 10) << endl;
}
