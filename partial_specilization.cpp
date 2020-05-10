#include <iostream>
#include <string>
using namespace std;

template<typename T>
class node{
public:
	T val;
	node(T _val): val(_val) {}
	static string flag;
};

template<typename T>
class node<T*> {
public:
	T val;
	node(T _val) : val(_val) {}
	static string flag;
};

template<typename T>
class node<const T*> {
public:
	T val;
	node(T _val) : val(_val) {}
	const static string flag;
};

template<typename T>
string node<T>::flag = "T";

template<typename T>
string node<T*>::flag = "T*";

template<typename T>
const string node<const T*>::flag = "const T*";

int main()
{
	node<int> a(1);
	node<int*> b(2);
	node<const int*> c(3);
	node<const double*> d(4);
	cout << a.flag << endl;
	cout << b.flag << endl;
	cout << c.flag << endl;
	cout << d.flag << endl;
	cout << &c.flag << " " << &d.flag << endl;
	return 0;
}
