#include <iostream>
#include <string>
using namespace std;

class Singleton {
public:
	Singleton(const Singleton& bother) = delete;
	Singleton& operator=(const Singleton& other) = delete;
	static Singleton* getInstance(const string value_);
	void business_logic() {}
	string get_value() { return value; }
protected:
	static Singleton* instance;
	string value;
	Singleton(const string value_) : value(value_) {}
};

Singleton* Singleton::instance = NULL;
Singleton* Singleton::getInstance(const string value_) {
	if (instance == NULL) return instance = new Singleton(value_);
	else return instance;
}

int main()
{
	Singleton* a = Singleton::getInstance("hello world");
	Singleton* b = a->getInstance("go go go");
	cout << b->get_value() << endl;
	return 0;
}
