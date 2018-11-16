#include <iostream>
#include <vector>

using namespace std;

void putinplace(vector<int> &v, int i, int j)
{
	if (v[i] > v[j])
		swap(v[i], v[j]);
}

void sort4(vector<int> &v)
{
	putinplace(v,0,2);
	putinplace(v,1,3);
	putinplace(v,0,1);
	putinplace(v,2,3);
	putinplace(v,1,2);
}

int main()
{
	int  a,b,c,d;
	cin >> a >> b >> c >> d;

	vector<int> v {a,b,c,d};

	sort4(v);

	for (auto x:v)
		cout << x;
	cout <<endl;
}
