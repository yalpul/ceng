#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

static constexpr int maxval = std::numeric_limits<int>::max();

vector<vector<int>> matrix_chain(const vector<int> &p, vector<vector<int>> &s_out)
{
	int n = p.size();
	vector<vector<int>> m(n, vector<int>(n,0));
	vector<vector<int>> s(n-1, vector<int>(n,0));

	for (int l = 2; l < n; l++) // chain length
		for (int i = 1; i < n - l + 1; i++)
		{
			int j = i + l - 1;
			m[i][j] = maxval;
			for (int k = i; k < j; k++)
			{
				int q  = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j];
				if (q < m[i][j])
				{
					m[i][j] = q;
					s[i][j] = k;
				}
			}
		}
	s_out = s;
	return m;
}

void print_pars(const vector<vector<int>>& s, int i, int j)
{
	if (i == j)
		cout << i;
	else
	{
		cout << '(';
		print_pars(s, i, s[i][j]);
		print_pars(s, s[i][j]+1, j);
		cout << ')';
	}
}

int main()
{
	vector<int> p = {7,5,2,4,3};
	vector<vector<int>> s;
	vector<vector<int>> m = matrix_chain(p, s);
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 7; j++)
			cout << m[i][j] << ",";
		cout << endl;
	}
	print_pars(s, 0, p.size()-1);



}
