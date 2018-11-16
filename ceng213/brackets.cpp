/*
 * Balancing brackets
 * program
 * using stack data structure
 */

#include <iostream>
#include <vector>

using namespace std;

void check(string & s)
{
	vector<char> stack;
	char x;
	for (auto c : s)
	{
		switch(c)
		{
			case '(':
			case '[':
			case '{':
				stack.push_back(c);
				break;
			case ')':
				x = stack.back();
				stack.pop_back();
				if (x != '(')
					throw 1;
				break;
			case ']':
				x = stack.back();
				stack.pop_back();
				if (x != '[')
					throw 1;
				break;
			case '}':
				x = stack.back();
				stack.pop_back();
				if (x != '{')
					throw 1;
				break;
		}
	}
	if (!stack.empty())
		throw 1;
}

int main()
{
	string s;
	getline(cin, s);

	try
	{
		check(s);
	}
	catch(int)
	{
		cout << "Error found!\n";
		return 0;
	}
	
	cout << "All is well\n";
}
