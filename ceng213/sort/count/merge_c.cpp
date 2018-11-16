#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

static unsigned long compCount = 0, moveCount = 0;

template <typename T>
void merge(vector<T> &v, vector<T> &t, int start, int center, int stop)
{
	int leftEnd = center - 1;
	int tp = start;
	int elements = stop - start + 1;

	while (start <= leftEnd && center <= stop)
		if (++compCount && v[start] <= v[center])
			t[tp++] = v[start++], ++moveCount;
		else
			t[tp++] = v[center++], ++moveCount;

	// Merge the remaining items
	while (start <= leftEnd)
		t[tp++] = v[start++], ++moveCount;

	while (center <= stop)
		t[tp++] = v[center++], ++moveCount;

	// Copy back to original container
	for (int i = 0; i < elements; i++, stop--)
		v[stop] = t[stop];
	moveCount += elements;
}

template <typename T>
void mergesort(vector<T> &v, vector<T> &t, int start, int stop)
{
	if (stop <= start)
		return;
	
	// Aims to avoid a possible overflow
	int center = start - (start - stop)/2;

	mergesort(v, t, start, center);
	mergesort(v, t, center+1, stop);

	merge(v, t, start, center+1, stop);
}

template <typename T>
void mergesort(vector<T> &v)
{	
	vector<T> t(v.size());
	mergesort(v, t, 0, v.size()-1);
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
	mergesort(v);
	cout << clock() - t << " CPU ticks\n"
	     << compCount << " comparisons made\n"
	     << moveCount << " move operations made\n";
}
