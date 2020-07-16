#include <iostream>
#include <string>
using namespace std;

class test {
public:
	test(const char* s_) : s(string(s_)) {}
	operator string () {
		return s;
	}
private:
	string s;
};

int main() {
	test a = "hello world";
	string b = a;
	cout << b << endl;
	return 0;
}
