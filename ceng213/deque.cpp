/*
 * Implementation of deque
 */

#include <iostream>

using namespace std;
template <typename Object>
class deque{
	struct Node{
		Node(Object d = Object{}, Node *p = nullptr, Node *n = nullptr)
		: data(d), prev(p), next(n) {}

		Object data;
		Node *prev;
		Node *next;
	};
	public:
		deque()
		{
			head = new Node;
			tail = new Node;
			head->next = tail;
			tail->prev = head;
		}
		~deque()
		{
			delete head;
			delete tail;
		}
		void push(Object x)
		{
			Node *newNode = new Node(x, head, head->next);
			head->next = head->next->prev = newNode;
		}
		Object pop()
		{
			Node *goner = head->next;
			head->next = goner->next;
			goner->next->prev = head;
			Object retValue = goner->data;
			delete goner;
			return retValue;
		}
		void inject(const Object & x)
		{
			Node *newNode = new Node(x, tail->prev, tail);
			tail->prev = tail->prev->next = newNode;
		}
		Object eject()
		{
			Node *goner = tail->prev;
			tail->prev = goner->prev;
			goner->prev->next = tail;
			Object retValue = goner->data;
			delete goner;
			return retValue;
		}
		void print()
		{
			Node *current = head->next;
			while (current != tail)
			{
				cout << current->data<< ", ";
				current = current->next;
			}
			cout <<endl;
		}
	private:
		Node *head, *tail;
};

int main()
{
	deque<int> d;
	d.push(3);
	d.print();
	d.push(4);
	d.print();
	cout << d.pop() <<endl;
	d.print();
	cout << d.pop() <<endl;
	d.print();
	d.inject(5);
	d.print();
	d.push(1);
	d.print();
	cout << d.eject() <<endl;
	d.print();
	d.inject(6);
	d.print();
	d.inject(8);
	d.print();
	cout << d.pop() <<endl;
	d.print();
	d.inject(9);
	d.print();
	cout << d.pop() <<endl;
	d.print();
	cout << d.eject() <<endl;
	d.print();
	cout << d.pop() <<endl;
	d.print();
}
