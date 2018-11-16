/*
 * Shaker Sort Algorithm
 * Optimized to remember
 * the indexes of sorted parts at the edges
 */
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

template <class T>
void shaker(std::vector<T> &v)
{
	int begin_i = 0, end_i = v.size() - 1;
	int new_bi = end_i, new_ei = begin_i;
	bool swpd = false;

	while (begin_i < end_i)
	{
		for (int i = begin_i; i < end_i; i++)
			if (v[i] > v[i+1])
			{
				std::swap(v[i], v[i+1]);
				swpd = true;
				new_ei = i;
			}

		// Breaks the loop when it is already sorted
		if (!swpd)
			break;
		swpd = false;

		// Ending index becomes the right-most unsorted index
		// The items at indexes greater than end_i are already sorted
		end_i = new_ei;

		for (int i = end_i - 1; i >= begin_i; i--)
			if (v[i] > v[i+1])
			{
				std::swap(v[i], v[i+1]);
				swpd = true;
				new_bi = i;
			}

		// Breaks the loop when it is already sorted
		if (!swpd)
			break;

		// The left side of beginning index is already sorted
		begin_i = new_bi + 1;
	}
}

int main(int argc, char* argv[])
{
	std::vector<int> v;
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
		std::cin >> s;
		v.resize(s);
		for (int i = 0; i < s; i++)
			std::cin >> v[i];
	}
	clock_t t = clock();
	shaker(v);
	std::cout << clock() - t << " CPU Ticks\n";
}
