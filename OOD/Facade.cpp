#include <iostream>
#include <string>
using namespace std;

class SubsystemA {
public:
	string operation() const {
		return "subsystemA operation\n";
	}
};

class SubsystemB {
public:
	string operation() const {
		return "subsystemB operation\n";
	}
};

class Facade {
public:
	Facade(SubsystemA* subA_ = NULL, SubsystemB* subB_ = NULL) {
		subA = subA_ ? subA_ : new SubsystemA();
		subB = subB_ ? subB_ : new SubsystemB();
	}
	~Facade() {
		delete subA;
		delete subB;
	}
	string operation() {
		string res = "Facade initialize subsystems:\n";
		res += subA->operation();
		res += subB->operation();
		return res;
	}
protected:
	SubsystemA* subA;
	SubsystemB* subB;
};

void client(Facade* facade) {
	cout << facade->operation() << endl;
}

int main()
{
	//SubsystemA* subA = new SubsystemA();
	//SubsystemB* subB = new SubsystemB();
	Facade* facade = new Facade();
	client(facade);
	return 0;
}
