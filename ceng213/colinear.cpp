/**
 * Given n points on 2D plane
 * Compute whether there are colinear points
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Point
{
	public:
		Point(int c1=0, int c2=0)
		: x(c1), y(c2) {}

		int x,y;
};

class Vector
{
	public:
		Vector(Point p1, Point p2)
		: point(p1) 
		{
			angle = double(p2.y-p1.y)/(p2.x-p1.x);
		}
		bool operator==(Vector& rhs)
		{
			return this->angle == rhs.angle;
		}
		Point point;
		double angle;
};
bool operator<(const Vector& lhs, const Vector& rhs)
{
	return lhs.angle < rhs.angle;
}

bool hasEqual(vector<Vector> &lines)
{
	for (int i = 0; i < lines.size() - 1; i++)
		if (lines[i] == lines[i+1])
			return true;
	return false;
}

int main()
{
	int n;

	cin >> n;

	vector<Point> v(n);

	while(n--)
		cin >> v[n].x >> v[n].y;

	for (int i = 0; i < v.size(); i++)
	{
		vector<Vector> lines;

		for (int j = i; j < v.size(); j++)
			lines.push_back(Vector(v[i], v[j]));

		sort(lines.begin(), lines.end());
		
		if (hasEqual(lines))
		{
			cout << "Colinear Point Found!\n";
			return 0;
		}
	}
	cout << "No Colinear Points :(\n";
}
