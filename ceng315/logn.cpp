#include <iostream>
#include <vector>

using namespace std;

int find(const vector<int>& vec, int start, int end, int key)
{
	int mid = (start + end) / 2;
	int num = vec[mid];
	if (num == key && vec[mid-1] != key)
		return mid;
	if (num >= key)
		return find(vec, start, mid-1, key);
	else
		return find(vec, mid+1, end, key);
}

int findr(const vector<int>& vec, int start, int end, int key)
{
	int mid = (start + end) / 2;
	int num = vec[mid];
	if (num == key && vec[mid+1] != key)
		return mid;
	if (num > key)
		return findr(vec, start, mid-1, key);
	else
		return findr(vec, mid+1, end, key);
}

int main()
{
	vector<int> vec = {1,2,3,4,4,4,5,6,7};
	int key = 4;

	int idx = find(vec, 0, vec.size()-1, key);
	cout << idx << endl;
	idx = findr(vec, 0, vec.size()-1, key);
	cout << idx << endl;
	return 0;
}
