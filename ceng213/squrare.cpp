#include <iostream>
#include <vector>

using namespace std;

class Square
{
	public:
		explicit Square(double s = 0.0)
		: storage {s} {}

		double getSide() const
		{
			return storage;
		}
		double getArea() const
		{
			return storage * storage;
		}

		bool operator<(const Square & rhs)
		{
			return getSide() < rhs.getSide();
		}

		void print(ostream & out = cout) const
		{
			out << getSide();
		}
	
	private:
		double storage;
};

ostream & operator<<(ostream & out, const Square & sqr)
{
	sqr.print(out);
	return out;
}

template <typename Cprbl>
Cprbl & findMax(vector<Cprbl>& v)
{
	int maxIndex = 0;

	for (int i = 1; i < v.size(); i++)
		if (v[maxIndex] < v[i])
			maxIndex = i;

	return v[maxIndex];
}
int main()
{
	Square a = Square(1.2), b = Square(2.1), c = Square(4.3);
	vector<Square> v {a,b,c};
  
	cout << findMax(v) <<endl;
	return 0;
}
