// with memoization
#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

int n = 10;
vector<int> m(n);
int rod(const vector<int> &p, int n)
{
	if (n==0)
		return 0;
	int max = -1;
	for (int i = 1; i <= n; i++)
	{
		if (m[n-i] == 0)
			m[n-i] = rod(p, n-i);
		max = std::max(max, p[i] + m[n-i]);
	}
	
	return m[n] = max;
}

int main()
{
	vector<int> p = {0,1,5,8,9,10,17,17,20,24,30};
	cout << rod(p, n) << endl;
}
