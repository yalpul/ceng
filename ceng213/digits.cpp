#include <iostream>

using namespace std;

int digits(int a)
{
	if (a == 1)
		return 1;
	if (a % 2 == 1)
		return 1 + digits(a/2);
	return digits(a>>1);
}

int main()
{
	int a; 
	cin >> a;

	cout << digits(a) <<endl;
	return 0;
}
