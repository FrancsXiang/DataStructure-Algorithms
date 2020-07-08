#include <iostream>
using namespace std;

class AbstractProductA {
public:
	virtual ~AbstractProductA() {}
	virtual string Operation() const = 0;
};

class ProductA1 : public AbstractProductA {
public:
	string Operation() const override {
		return "Operation of Product A1";
	}
};

class ProductA2 : public AbstractProductA {
	string Operation() const override {
		return "Operation of Product A2";
	}
};

class AbstractProductB {
public:
	virtual ~AbstractProductB() {}
	virtual string Operation() const = 0;
	virtual string Cooperator(const AbstractProductA& productA) const = 0;
};

class ProductB1 : public AbstractProductB {
	string Operation() const override {
		return "Operation of Product B1";
	}
	string Cooperator(const AbstractProductA& productA) const override {
		return "Product B1's Cooperator with " + productA.Operation();
	}
};

class ProductB2 : public AbstractProductB {
	string Operation() const override {
		return "Operation of Product B2";
	}
	string Cooperator(const AbstractProductA& productA) const override {
		return "Product B2's Cooperator with " + productA.Operation();
	}
};

class AbstractFactory {
public:
	virtual AbstractProductA* createProductA() const = 0;
	virtual AbstractProductB* createProductB() const = 0;
};

class Facotry_1 : public AbstractFactory {
public:
	AbstractProductA* createProductA() const override {
		return new ProductA1();
	}
	AbstractProductB* createProductB() const override {
		return new ProductB1();
	}
};

class Factory_2 : public AbstractFactory {
public:
	AbstractProductA* createProductA() const override {
		return new ProductA2();
	}
	AbstractProductB* createProductB() const override {
		return new ProductB2();
	}
};

void client(const AbstractFactory& Factory) {
	const AbstractProductA* ProductA = Factory.createProductA();
	const AbstractProductB* ProductB = Factory.createProductB();
	cout << ProductA->Operation() << endl;
	cout << ProductB->Operation() << endl;
	cout << ProductB->Cooperator(*ProductA) << endl;
}

int main()
{
	const AbstractFactory* Factory1 = new Facotry_1();
	const AbstractFactory* Factory2 = new Factory_2();
	client(*Factory1);
	client(*Factory2);
	return 0;
}
