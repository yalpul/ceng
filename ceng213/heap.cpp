#include <iostream>
#include <vector>
#include <cmath>

template <class T>
class Heap{
public:
	Heap(int capacity = 100)
	: size(0), array(capacity) {}

	void insert(const T &el)
	{
		if (size == array.size() - 1)
			array.resize(array.size() * 2);

		int hole = ++size;
		array[0] = el;

		while (el < array[hole/2])
			array[hole] = array[hole/2], hole /= 2;
		array[hole] = array[0];
	}
	
	void print() const
	{
		int height = std::log2(size) + 1;
		for (int i = 1; i < size+1; i *= 2)
		{
			for (int j = 0; j < height; j++) 
				std::cout << " ";
			height--;
			for (int j = i; j < i*2; j++)
				std::cout << array[j] << " ";
			std::cout << std::endl;
		}
	}

	void deletemin()
	{
		if (!size)
			return;
		array[1] = array[size--];
		percolatedown(1);
	}
	int getsize() const
	{
		return size;
	}
	void percolatedown(int hole)
	{
		int child;
		T tmp = array[hole];

		while (2 * hole <= size)
		{	
			child = hole * 2;

			if (child != size && array[child+1] < array[child])
				child++;
			if (tmp > array[child])
				array[hole] = array[child];
			else break;
			hole = child;
		}
		array[hole] = tmp;
	}

private:
	std::vector<T> array;
	int size;
};
	
int main()
{
	int n;
	Heap<int> h;
	while (true)
	{
		std::cin >> n;
		h.insert(n);
		h.print();
		if (h.getsize() == 8)
			break;
	}
	while (h.getsize())
		h.deletemin(), h.print();
}
