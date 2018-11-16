#include <iostream>
#include <vector>
#include <cstring>

using std::vector;
using std::cout;
using std::endl;
using std::string;

vector<vector<int>> lcs(const char *s1, const char *s2)
{
	int s1_len = strlen(s1);
	int s2_len = strlen(s2);

	vector<vector<int>> c(s1_len+1, vector<int>(s2_len+1, 0));

	for (int i = 1; i <= s1_len; i++)
		for (int j = 1; j <= s2_len; j++)
			if (s1[i-1] == s2[j-1])
				c[i][j] = c[i-1][j-1] + 1;
			else if (c[i-1][j] >= c[i][j-1])
				c[i][j] = c[i-1][j];
			else
				c[i][j] = c[i][j-1];
	return c;
}

int main()
{
	const char *s1 = "ABCBDAB";
	const char *s2 = "BDCABA";
	vector<vector<int>> c = lcs(s1, s2);
	for (int j = 0; j < c.size(); j++)
	{
		for (int i = 0; i < c[j].size(); i++)
			cout << c[j][i] << ",";
		cout << endl;
	}
	cout << endl;
}
