/*
This is a opp implementation of data_structure of monotonic_stack.(generics supported)
*/
#include <iostream>
#define UP 0
#define DOWN 1
using namespace std;

template<typename T>
struct node
{
	T data;
	node<T>* prev;
};

template<typename T>
class MST
{
public:
	MST(int code=UP);
	~MST();
	T top();
	T pop();
	bool empty();
	void push(int val);
	void set_code(int code);
	void clear();
private:
	int code;
	node<T> *head, *last;
};

template<typename T>
MST<T>::MST(int code)
{
	head = new node<T>;
	last = head;
	this->code = code;
}

template<typename T>
MST<T>::~MST()
{
	clear();
}

template<typename T>
T MST<T>::top() {
	if (empty()) throw "no elements in stack!";
	return last->data;
}

template<typename T>
void MST<T>::push(int val) {
	node<T>* cur = new node<T>;
	cur->data = val;
	if (code == UP)
		while (last != head && last->data > val) last = last->prev;
	else
		while (last != head && last->data < val) last = last->prev;
	cur->prev = last;
	last = cur;
}

template<typename T>
T MST<T>::pop() {
	if (empty()) throw "no elements in stack!";
	node<T>* tmp = last->prev;
	delete last;
	last = tmp;
}

template<typename T>
bool MST<T>::empty() {
	if (head == last) return true;
	else return false;
}

template<typename T>
void MST<T>::clear() {
	node<T>* tmp = last;
	while (last != head) {
		delete tmp;
		tmp = last;
		last = last->prev;
	}
}

template<typename T>
void MST<T>::set_code(int code) {
	this->code = code;
	clear();
}

int main()
{
	MST<int> st;
	st.set_code(DOWN);
	for (int i = 0; i < 10; i++) st.push(i);
	try
	{

		for (int i = 0; i < 10; i++) {
			cout << st.top() << " ";
			st.pop();
		}
	}
	catch (const char* msg)
	{
		cout << msg << endl;
	}
	return 0;
}
