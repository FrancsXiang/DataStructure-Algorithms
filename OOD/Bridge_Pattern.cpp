#include <iostream>
#include <string>
using namespace std;

class Implementation {
public:
	virtual ~Implementation() {}
	virtual string Operation() const = 0;
};

class ImplementationA : public Implementation {
public:
	string Operation() const override{
		return "Operation of ImplementationA";
	}
};

class ImplementationB : public Implementation {
public:
	string Operation() const override {
		return "Operation of ImplementationB";
	}
};

class Abstraction {
public:
	Abstraction(Implementation* imp_) : imp(imp_) {}
	virtual string Operation() const{
		return "Operation of Abstraction with " + this->imp->Operation();
	}
protected:
	Implementation* imp;
};

class ExtendedAbstraction : public Abstraction{
public:
	ExtendedAbstraction(Implementation* imp_) : Abstraction(imp_) {}
	string Operation() const override{
		return "Operation of ExtendedAbstraction with " + this->imp->Operation();
	}
};

void client(const Abstraction* abstract) {
	cout << abstract->Operation() << endl;
}

int main()
{
	Implementation* a = new ImplementationA();
	Implementation* b = new ImplementationB();
	Abstraction* abstract_1 = new Abstraction(a);
	Abstraction* abstract_2 = new ExtendedAbstraction(b);
	client(abstract_1);
	client(abstract_2);
	return 0;
}
