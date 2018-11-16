#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

static unsigned long compCount = 0, moveCount = 0;

using namespace std;
/*
 * Insertion Sort Algorithm
 * Places every item to its proper place
 * in an already sorted partition
 */
template <typename T>
void insertion(vector<T> &v)
{
	for (int i = 1; i < v.size(); i++)
	{
		T tmp = v[i], j; ++moveCount;

		for (j = i; j > 0 && (++compCount && tmp < v[j-1]); j--)
			v[j] = v[j-1], ++moveCount;
		v[j] = tmp; ++moveCount;
	}
}

int main(int argc, char *argv[])
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
	insertion(v);
	cout << clock() - t << " CPU ticks\n"
	     << compCount << " comparisons made\n"
			 << moveCount << " move operations made\n";
}

