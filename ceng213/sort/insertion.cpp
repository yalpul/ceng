#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;
template <typename T>
void insertion(vector<T> &v)
{
	for (int i = 1; i < v.size(); i++)
	{
		T tmp = std::move(v[i]), j;
		for (j = i; j > 0 && tmp < v[j-1]; j--)
			v[j] = std::move(v[j-1]);
		v[j] = std::move(tmp);
	}
}

int main(int argc, char *argv[])
{
	srand(time(0));
	vector<int> v;
	int s = atoi(argv[1]);
	for (int i = 0; i < s; i++)
		v.push_back(rand());
	
	insertion(v);
}

