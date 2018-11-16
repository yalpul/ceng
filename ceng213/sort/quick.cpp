#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

void insertion(vector<int> &v, int start, int stop)
{
	for (int i = start + 1; i <= stop; i++)
	{
		int tmp = v[i], j = i;
		
		while (j > start && tmp < v[j-1])
			v[j] = v[j-1], j--;

		v[j] = tmp;
	}
}

int median3(vector<int> &v, int start, int stop)
{
	int center = (start+stop)/2;

	if (v[center] < v[start])
		std::swap(v[center], v[start]);
	if (v[stop] < v[start])
		std::swap(v[stop], v[start]);
	if (v[stop] < v[center])
		std::swap(v[stop], v[center]);

	std::swap(v[center], v[stop-1]);
	return v[stop-1];
}

void quicksort(vector<int> &v, int start, int stop)
{
	if (stop - start < 5)
	{
		insertion(v, start, stop);
		return;
	}

	int pvt = median3(v, start, stop);

	int i =  start, j = stop - 1;

	while (1)
	{
		while (v[++i] < pvt);
		while (v[--j] > pvt);
		if (i < j)
			std::swap(v[i], v[j]);
		else break;
	}

	std::swap(v[stop-1], v[i]);

	quicksort(v, start, i-1);
	quicksort(v, i+1, stop);
}

void quicksort(vector<int> &v)
{
	quicksort(v, 0, v.size()-1);
}

int main(int argc, char* argv[])
{
	srand(time(0));
	int s = atoi(argv[1]);
	vector<int> v(s);
	for (int i = 0; i < s; i++)
		v[i] = rand() % s;
	quicksort(v);
	for (auto x:v)
		cout << x <<endl;
}
