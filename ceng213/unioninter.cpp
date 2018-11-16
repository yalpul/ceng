/*
 * Union and intersection of two sorted arrays
 */

#include <iostream>
#include <vector>

using namespace std;

vector<int> unionoftwo(vector<int> l1, vector<int> l2)
{
	vector<int> v;

	for (int i = 0, j = 0; i < l1.size() && j < l2.size(); )
		if (l1[i] < l2[j])
			v.push_back(l1[i++]);
		else if (l1[i] > l2[j])
			v.push_back(l2[j++]);
		else
			v.push_back((j++, l1[i++]));
	return v;
}

vector<int> intersection(vector<int> l1, vector<int> l2)
{
	vector<int> v;

	for (int i = 0, j = 0; i < l1.size() && l2.size(); )
		if (l1[i] < l2[j])
			i++;
		else if (l1[i] > l2[j])
			j++;
		else
			v.push_back((j++, l1[i++]));

	return v;
}
int main()
{
	vector<int> v1 {0,1,2,3,4,7}, v2 {2,3,5,6,8};

	vector<int> r = intersection(v1,v2);

	for(auto x : r)
		cout << x << " ";
	cout << endl;
}
