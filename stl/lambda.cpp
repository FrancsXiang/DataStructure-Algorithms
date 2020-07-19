#include <iostream>
using namespace std;
//1.[capture list](params list) -> return type{ function body }
//2.[capture list](params list) {function body}
//3.[capture list] {function body}
// "=","&","," outer variable descriptor
// varlist limits: no default value/must have a name/no changable variable supported
int main()
{
	int x = 1;
	auto functor = [=](int k) mutable ->int {x++; return x + k; };
	cout << functor(3) << endl;
	return 0;
}
