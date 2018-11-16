/*
 * C++ program for converting
 * infix notation to postfix notation
 * works only for '+' and '*'
 */

#include <iostream>
#include <stack>

using namespace std;
void printWhileGreat(char c, stack<char> & stackk)
{
	if (c == '+')
		while (!stackk.empty())
			cout << stackk.top() << " ", stackk.pop();
	else if (c == '*')
		while (!stackk.empty() and stackk.top() != '+')
			cout << stackk.top() << " ", stackk.pop();
}
int main()
{
	string s;
	stack<char> stackk;

	while (cin >> s)
	{
		if (s != "+" and s != "*")
			cout << s << " ";
		else
		{
			printWhileGreat(s[0], stackk);
			stackk.push(s[0]);
		}
	}

	while (!stackk.empty())
		cout << stackk.top()<< " ", stackk.pop();
}
