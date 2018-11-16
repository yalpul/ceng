#include <iostream>
#include <forward_list>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

const int hsize = 20;
int hash(const string &s)
{
	int sum = 0;
	for (int i = 0; i < s.size(); i++)
		sum += s[i];
	return sum % hsize;
}
class HashTable
{
public:
	HashTable()
	: list(hsize) {}
	void print() const
	{
		for (int i = 0; i < hsize; i++)
		{
			cout << i << " -> ";
			for (std::forward_list<string>::const_iterator iter = list[i].begin(); iter != list[i].end(); iter++)
				cout << *iter << " ";
			cout << endl;
		}
	}
	void insert(const string &s)
	{
		int hashval = hash(s);
		list[hashval].push_front(s);
	}
private:
	vector<std::forward_list<string> > list;
};


int main()
{
	int i = 0;
	HashTable htable;
	while (i++ < 5)
	{
		string s;
		cin >> s;
		htable.insert(s);
	}
	htable.print();	
}
