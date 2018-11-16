#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

template <typename T>
void shell(vector<T> &v)
{
	int g = v.size() / 2;
	while (g)
	{
		for (int i = g; i < v.size(); i++)
		{
			int j = i;
			T tmp = v[i];
			
			while (j >= g && tmp < v[j-g])
				v[j] = v[j-g], j -= g;
			v[j] = tmp;
		}
		if (g == 2)
			g = 1;
		else
			g /= 2.2;
	}
}

int main(int argc, char *argv[])
{
	srand(time(0));
	int s = atoi(argv[1]);
	vector<int> v(s);
	for (int i = 0; i < s; i++)
		v[i] = rand();
	shell(v);
}
