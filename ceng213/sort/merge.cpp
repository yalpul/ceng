#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

template <typename T>
void merge(vector<T> &v, vector<T> &t, int start, int center, int stop)
{
	int leftEnd = center - 1;
	int tp = start;
	int elements = stop - start + 1;
	while (start <= leftEnd && center <= stop)
		if (v[start] <= v[center])
			t[tp++] = std::move(v[start++]);
		else
			t[tp++] = std::move(v[center++]);

	while (start <= leftEnd)
		t[tp++] = std::move(v[start++]);

	while (center <= stop)
		t[tp++] = std::move(v[center++]);

	for (int i = 0; i < elements; i++, stop--)
		v[stop] = std::move(t[stop]);
}

template <typename T>
void mergesort(vector<T> &v, vector<T> &t, int start, int stop)
{
	if (stop <= start)
		return;

	int center = (start + stop)/2;

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
	srand(time(0));
	int s = atoi(argv[1]);
	vector<int> v(s);
	for (int i = 0; i < s; i++)
		v[i] = rand();
	mergesort(v);
}
