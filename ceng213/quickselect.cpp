#include <iostream>
#include <vector>

using namespace std;

void print(vector<int> &v)
{
	cout << "[";
	for (int i = 0; i < v.size()-1; i++)
		cout <<v[i] << ", ";
	cout << v[v.size()-1] <<"]\n";
}
int median3(vector<int> &v, int left, int right)
{
	int center = (left+right)/2;

	if (v[left] > v[center])
		std::swap(v[left], v[center]);
	if (v[left] > v[right])
		std::swap(v[left], v[right]);
	if (v[center] > v[right])
		std::swap(v[center], v[right]);

	std::swap(v[center], v[right-1]);
	return v[right-1];
}


int quick(vector<int> &v, int start, int end, int k)
{
	if (start >= end)
		return v[start];
	int pvt = median3(v, start, end);

	int i = start, j = end - 1;
	while (1)
	{
		while (v[++i] < pvt);
		while (v[--j] > pvt);
		if (i < j)
			std::swap(v[i], v[j]);
		else break;
	}
	std::swap(v[i], v[end-1]);
	if (k == i - start)
		return v[k];
	else if (k < i - start)
		return quick(v, start, i-1, k);
	else
		return quick(v, i+1, end, k+start-i);
}

int quick(vector<int> &v, int k)
{
	return quick(v, 0, v.size() - 1, k);
}

int main()
{
	vector<int> v {9, 11, 11, 0, 20, 9, 15, 16, 6, 14, 2, 11, 1, 16, 0, 4, 13, 18, 15, 3};
	cout << quick(v, 0) <<endl;
}
