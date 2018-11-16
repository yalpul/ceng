#include <iostream>
#include <vector>

using namespace std;

int main()
{
	int n, k;
	cin >> n;

	vector<int> v;

	for (int i = 0; i < n; i++)
	{
		cin >> k;
		v.push_back(k);
	}

	sort(v.begin(), v.end(), [](int a, int b) -> bool {return a < b;});

	cout << v[n/2] <<endl;

	return 0;
}
