/*
 * Reverse Polish Notation Caluclator
 * made with stack
 */

#include <iostream>
#include <stack>

using namespace std;
int main()
{
	string s;
	stack<int> stack;
	int i;
	char a,b;
	while (cin >> s)
	{
		try{
			stack.push(stoi(s));
		} catch (invalid_argument){
				switch (s[0])
				{
					case '+':
						a = stack.top(), stack.pop();
						b = stack.top(), stack.pop();
						stack.push(a + b);
						break;
					case '-':
						a = stack.top(), stack.pop();
						b = stack.top(), stack.pop();
						stack.push(a - b);
						break;
					case '*':
						a = stack.top(), stack.pop();
						b = stack.top(), stack.pop();
						stack.push(a * b);
						break;
					case '/':
						a = stack.top(), stack.pop();
						b = stack.top(), stack.pop();
						stack.push(a / b);
						break;
				}
			}
		}
	
	cout << stack.top() << endl;
}
