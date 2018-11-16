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

static unsigned long compCount = 0, moveCount = 0;

// Using Insertion Sort for sizes smaller than 10
void insertion(vector<int> &v, int start, int stop)
{
	for (int i = start + 1; i <= stop; i++)
	{
		int tmp = v[i], j = i; ++moveCount;
		
		while (j > start && (++compCount && tmp < v[j-1]))
			v[j] = v[j-1], j--, ++moveCount;

		v[j] = tmp; ++moveCount;
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
		std::swap(v[center], v[start]), moveCount += 2;
	if (v[stop] < v[start])
		std::swap(v[stop], v[start]), moveCount += 2;
	if (v[stop] < v[center])
		std::swap(v[stop], v[center]), moveCount += 2;

	compCount += 3;
	std::swap(v[center], v[stop-1]), moveCount += 2;
	return v[stop-1];
}

void quicksort(vector<int> &v, int start, int stop)
{
	if (stop - start < 10)
	{
		insertion(v, start, stop);
		return;
	}

	int pvt = median3(v, start, stop);

	int i =  start, j = stop - 1;

	// Actual partitioning
	while (true)
	{
		while (v[++i] < pvt)
			++compCount;
		while (v[--j] > pvt)
			++compCount;
		if (i < j)
			std::swap(v[i], v[j]), moveCount += 2;
		else break;
	}

	// Put pivot back in place
	std::swap(v[stop-1], v[i]), moveCount += 2;

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
			v[i] = rand();
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
	cout << clock() - t << " CPU ticks\n"
	     << compCount << " comparisons made\n"
			 << moveCount << " move operations made\n";
}
