#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Product {
public:
	virtual ~Product() {}
	virtual void Operation() const = 0;
};


class ProductA : public Product{
public:
	void Operation() const override {
		cout << "Operation of ProductA" << endl;
	}
};

class ProductB : public Product{
public:
	void Operation() const override {
		cout << "Operation of ProductB" << endl;
	}
};

class ProductC : public Product {
public:
	void Operation() const override {
		cout << "Operation of ProductC" << endl;
	}
};

class Builder {
public:
	virtual ~Builder() {}
	virtual void builderProductA() = 0;
	virtual void builderProductB() = 0;
	virtual void builderProductC() = 0;
};

class Builder1 : public Builder {
public:
	Builder1() { product = NULL; }
	void builderProductA() override {
		product = new ProductA();
		product->Operation();
	}
	void builderProductB() override {
		product = new ProductB();
		product->Operation();
	}
	void builderProductC() override {
		product = new ProductC();
		product->Operation();
	}
private:
	Product* product;
};

class Director {
public:
	void set_builder(Builder* builder) { this->builder = builder; }
	void build() {
		builder->builderProductA();
		builder->builderProductB();
		builder->builderProductC();
	}
private:
	Builder* builder;
};

void client(Director& director) {
	Builder1* builder = new Builder1();
	director.set_builder(builder);
	director.build();
}

int main()
{
	Director* director = new Director();
	client(*director);
	return 0;
}
