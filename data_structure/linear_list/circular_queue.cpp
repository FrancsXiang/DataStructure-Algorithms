#include <iostream>
#define MAXN 10000000
using namespace std;

template<typename T>
class CQ
{
public:
	CQ(int max_vol=MAXN);
	~CQ();
	T pop();
	T top();
	void push(T val);
	bool empty();
	bool full();
private:
	int front, rear,max_vol;
	T* container;
};

template<typename T>
CQ<T>::CQ(int max_vol)
{
	max_vol++;
	this->max_vol = max_vol;
	front = rear = 0;
	container = new T[max_vol];
}

template<typename T>
CQ<T>::~CQ()
{
	delete[] container;
}

template<typename T> 
bool CQ<T>::empty() {
	if (front == rear) return true;
	else return false;
}

template<typename T>
bool CQ<T>::full() {
	if (front == (rear + 1) % max_vol) return true;
	else return false;
}

template<typename T>
void CQ<T>::push(T val) {
	if (full()) throw "The queue is full!";
	container[rear] = val;
	rear = (rear + 1) % max_vol;
}

template<typename T>
T CQ<T>::pop() {
	if (empty()) throw "The queue is empty!";
	T tmp = container[front];
	front = (front + 1) % max_vol;
	return tmp;
}

template<typename T>
T CQ<T>::top() {
	if (empty()) throw "The queue is empty!";
	return container[front];
}
int main()
{
	CQ<int> que;
	for (int i = 0; i < 10; i++) que.push(i);
	try
	{
		for (int i = 0; i < 10; i++) {
			if (!que.empty()) cout << que.top() << " ";
			que.pop();
		}
	}
	catch (const char* msg)
	{
		cerr << msg << endl;
	}
	return 0;
}
