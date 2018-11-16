/*
 * Quicksort Algorithm 
 * using Hoare's partition scheme
 * choice of pivot with Median-of-3 
 */

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

inline int leftchild(int i)
{
	return 2*i + 1;
}

template <class T>
void percdown(vector<T> &v, int i, int size, int start)
{
	T tmp = v[i+start];
	int child;

	while ((child = leftchild(i)) < size)
	{
		if (child != size - 1 && v[child+1+start] > v[child+start])
			child++;
		if (v[child+start] > tmp)
			v[i+start] = v[child+start];
		else break;
		i = child;
	}
	v[i+start] = tmp;
}

template <class T>
void hsort(vector<T> &v, int start, int stop)
{
	for (int i = (stop-start+1) / 2 - 1; i >= 0; i--)
		percdown(v, i, stop-start+1, start);
	for (int i = stop - start; i > 0; i--)
		std::swap(v[start], v[i+start]), percdown(v, 0, i, start);
}
// Using Insertion Sort for sizes smaller than 10
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

/*
 * Puts the first, the last and middle item into order 
 * puts pivot to the right-most place 
 * to prevent interfering with the partitioning routine
 */
int median3(vector<int> &v, int start, int stop)
{
	// This aims to avoid overflows
	int center = start - (start-stop) / 2;

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
	if (stop - start < 10)
	{
		hsort(v, start, stop);
		return;
	}

	int pvt = median3(v, start, stop);

	int i =  start, j = stop - 1;

	// Actual partitioning
	while (true)
	{
		while (v[++i] < pvt);
		while (v[--j] > pvt);
		if (i < j)
			std::swap(v[i], v[j]);
		else break;
	}

	// Put pivot back in place
	std::swap(v[stop-1], v[i]);

	// Recursively apply quicksort to sub-partitions
	quicksort(v, start, i-1);
	quicksort(v, i+1, stop);
}

// Driver to actual function
void quicksort(vector<int> &v)
{
	quicksort(v, 0, v.size()-1);
}

int main(int argc, char* argv[])
{
	vector<int> v;
	if (argc == 2)
	{
		srand(time(0));
		int s = atoi(argv[1]);
		v.resize(s);
	
		for (int i = 0; i < s; i++)
			v[i] = rand() % s;
	}
	else
	{
		int s;
		cin >> s;
		v.resize(s);
		for (int i = 0; i < s; i++)
			cin >> v[i];
	}
	clock_t t = clock();
	quicksort(v);
	cout << clock() - t << " CPU ticks\n";
	for (int i= 0; i < v.size(); i++)
		cout << v[i] << endl;
}
