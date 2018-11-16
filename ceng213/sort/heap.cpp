#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using std::vector;
using std::cout;
using std::cin;
using std::endl;

inline int leftchild(int i)
{
	return 2*i + 1;
}

template <class T>
void percdown(vector<T> &v, int i, int size)
{
	T tmp = v[i];
	int child;

	while ((child = leftchild(i)) < size)
	{
		if (child != size - 1 && v[child+1] > v[child])
			child++;
		if (v[child] > tmp)
			v[i] = v[child];
		else break;
		i = child;
	}
	v[i] = tmp;
}

template <class T>
void hsort(vector<T> &v)
{
	for (int i = v.size() / 2 - 1; i >= 0; i--)
		percdown(v, i, v.size());
	for (int i = v.size() - 1; i > 0; i--)
		std::swap(v[0], v[i]), percdown(v, 0, i);
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
	hsort(v);
	cout << clock() - t << " CPU ticks\n";
}
