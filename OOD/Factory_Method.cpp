#include <iostream>
using namespace std;

class Product
{
public:
	virtual ~Product() {}
	virtual string Operation() const = 0;
};

class Creator {
public:
	virtual ~Creator() {}
	virtual Product* FactoryMethod() const = 0;
	string Operation() const {
		Product* product = FactoryMethod();
		string res = "The creator works with " + product->Operation();
		return res;
	}
};

class Product_1 : public Product
{
public:
	string Operation() const override {
		return "Operation of Product_1";
	}
};

class Product_2: public Product
{
public:
	string Operation() const override {
		return "Operation of Product_2";
	}
};

class Creator_1 : public Creator
{
public:
	Product* FactoryMethod() const override {
		return new Product_1;
	}
};

class Creator_2 : public Creator
{
public:
	Product* FactoryMethod() const override {
		return new Product_2;
	}
};

void client(Creator& creator) {
	cout << creator.Operation() << endl;
}

int main()
{
	Creator* creator_1 = new Creator_1();
	client(*creator_1);
	Creator* creator_2 = new Creator_2();
	client(*creator_2);
	return 0;
}
