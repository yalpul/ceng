// bottom up dynamic algorithm for rod cutting problem
// with printing solution
#include <iostream>
#include <vector>
#include <cstdlib>

using std::vector;
using std::cout;;
using std::endl;

void rod(int n, const vector<int> &p)
{
	vector<int> r(n+1);
	vector<int> s(n+1);

	for (int i = 1; i <= n; i++)
	{
		int max = 0;
		for (int j = 1; j <= i; j++)
		{
			int val = p[j] + r[i-j];
			if (val > max)
			{
				max = val;
				s[i] = j;
			}
		}
		r[i] = max;
	}

	while (n > 0)
	{
		cout << s[n] << " " << p[s[n]] << endl;
		n = n - s[n];
	}
}

int main(int argc, char **argv)
{
	vector<int> p = {0,1,5,8,9,10,17,17,20,24,30};
	rod(atoi(argv[1]), p);
}
