#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

static unsigned long compCount = 0, moveCount = 0;

// Shellsort algorithm using Ciura's increments
template <typename T>
void shell(vector<T> &v)
{
	// Initial gap is half of container size and it gets divided by 2.2 in each pass
	int inc = v.size() / 2;
	while (inc)
	{
		for (int i = inc; i < v.size(); i++)
		{
			int j = i;
			T tmp = v[i]; 
			 
			// Modified insertion sort routine 
			while (j >= inc && (++compCount && tmp < v[j-inc]))
				v[j] = v[j-inc], j -= inc, ++moveCount;
			v[j] = tmp;
		}
		if (inc == 2)
			inc = 1;
		else
			inc /= 2.2;
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
	shell(v);
	cout << clock() - t << " CPU ticks\n"
	     << compCount << " comparisons made\n"
	     << moveCount << " move operations made\n";
}
