// bottom up dynamic algorithm for rod cutting problem
#include <iostream>
#include <vector>

using std::vector;
using std::cout;;
using std::endl;

int rod(int n, const vector<int> &p)
{
	vector<int> r(n+1);

	for (int i = 1; i <= n; i++)
	{
		int max = 0;
		for (int j = 1; j <= i; j++)
		{
			int val = p[j] + r[i-j];
			max = val > max ? val : max;
		}
		r[i] = max;
	}
	return r[n];
}

int main()
{
	vector<int> p = {0,1,5,8,9,10,17,17,20,24,30};
	cout << rod(10, p) << endl;
}
