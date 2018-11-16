#include <iostream>
#include <vector>

using namespace std;
class Rectangle
{
	public:
		explicit Rectangle(double w = 0.0, double h = 0.0)
		:	width(w), height(h) {}

		double getHeight() const
		{
			return height;
		}
		double getWidth() const
		{
			return width;
		}

		#ifdef AREA

		bool operator<(const Rectangle & rec) const
		{
			return getHeight() * getWidth() < rec.getWidth() * rec.getHeight();
		}

		#else

		bool operator<(const Rectangle & rec) const
		{
			return getHeight() + getWidth() < rec.getWidth() + rec.getHeight();
		}

		#endif

		private:
			double width, height;
};

const Rectangle & findMax(const vector<Rectangle> v)
{
	int maxIndex = 0;

	for (int i = 0; i < v.size(); i++)
		if (v[maxIndex] < v[i])
			maxIndex = i;

	return v[maxIndex];
}

int main()
{
	vector<Rectangle> v {Rectangle(1.2, 2.1), Rectangle(3.0, 5.0), Rectangle(4.0, 5.0), Rectangle(1.0, 12.0)};

	Rectangle x = findMax(v);
	cout << x.getHeight() <<" is the height and this is width " << x.getWidth() << endl;
}
