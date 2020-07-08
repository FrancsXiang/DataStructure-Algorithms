#include <iostream>
#include <string>
using namespace std;

class Target {
public:
	virtual ~Target() {}
	virtual string request() const {
		return "Target default behavior.";
	}
};

class Adaptee {
public:
	string specific_request() const{
		return "Adaptee default behavior.";
	}
};

class Adaptor : public Target, public Adaptee {
public:
	string request() const override {
		string result = specific_request();
		reverse(result.begin(), result.end());
		return result;
	}
};

void client(Target* target) {
	cout << target->request() << endl;
}

int main()
{
	Target* a = new Target();
	client(a);
	Target* b = new Adaptor();
	client(b);
	return 0;
}
