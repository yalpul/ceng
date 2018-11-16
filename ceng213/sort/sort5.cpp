#include <iostream>
#include <vector>

using namespace std;

void putinplace(vector<int> &v, int i, int j)
{
	if (v[i] > v[j])
		swap(v[i], v[j]);
}

void sort5(vector<int> &v)
{
	putinplace(v,0,1);
	putinplace(v,2,3);

	if (v[0] > v[2])
		swap(v[2], v[0]), swap(v[1],v[3]);
	
	int a = v[0], b = v[1], c = v[2], d = v[3], e = v[4];

	if (e > c)
		if (e > d)
			// put b in a,(c,d,e)
			if (b > d)
				if (b > e)
					v = vector<int>{a,c,d,e,b};
				else
					v = vector<int>{a,c,d,b,e};
			else
				if (b > c)
					v = vector<int>{a,c,b,d,e};
				else
					v = vector<int>{a,b,c,d,e};
		else
			// put b in a,(c,e,d)
			if (b > e)
				if (b > d)
					v = vector<int>{a,c,e,d,b};
				else
					v = vector<int>{a,c,e,b,d};
			else
				if (b > c)
					v = vector<int>{a,c,b,e,d};
				else
					v = vector<int>{a,b,c,e,d};
	else
		if (e > a)
			//put b in a,(e,c,d)
			if (b > c)
				if (b > d)
					v = vector<int>{a,e,c,d,b};
				else
					v = vector<int>{a,e,c,b,d};
			else
				if (b > e)
					v = vector<int>{a,e,b,c,d};
				else
					v =vector<int>{a,b,e,c,d};
		else
			//put b in e, (a,c,d)
			if (b > c)
				if (b > d)
					v = vector<int>{e,a,c,d,b};
				else
					v =vector<int>{e,a,c,b,d};
			else
				if (b > a)
					v = vector<int>{e,a,b,c,d};
				else
					v = vector<int>{e,b,a,c,d};
}

int main()
{
	int a,b,c,d,e;
	cin >> a >> b >> c >> d >> e;
	vector<int> v {a,b,c,d,e};
	sort5(v);
	for (auto x:v)
		cout << x;
	cout << endl;
}
