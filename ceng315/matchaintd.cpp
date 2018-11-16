#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

static constexpr int maxval = std::numeric_limits<int>::max();

int matchain(vector<vector<int>> &m, const vector<int> &p, int i, int j)
{
	if (m[i][j] < maxval)
		return m[i][j];
	if (i == j)
		return m[i][j] = 0;
	for (int k = i; k < j; k++)
	{
		int q = matchain(m, p, i, k) + matchain(m, p, k+1, j) + p[i-1]*p[k]*p[j];
		if (q < m[i][j])
			m[i][j] = q;
	}
	return m[i][j];
}

int initmatchain(const vector<int> &p)
{
	int n = p.size();
	vector<vector<int>> m(n, vector<int>(n, maxval));
	return matchain(m, p, 1, n-1);
}

int main()
{
	vector<int> p = {7,5,2,4,3};
	int  m = initmatchain(p);
	cout << m << endl;
}
