#include <iostream>
using namespace std;

//when T is a class-type or struct, you need overload corresponding operators.
template<typename T>
void swap(T& a, T& b, int code = 0) {
	if (code == 0) {
		T tmp = a;
		a = b;
		b = tmp;
	}
	else if(code == 1){
		a += b;
		b = a - b;
		a -= b;
	}
	else {
		a ^= b;
		b ^= a;
		a ^= b;
	}
}

int main()
{
	int a = 3, b = 4;
	swap(a, b, -1);
	cout << a << " " << b << endl;
	return 0;
}
