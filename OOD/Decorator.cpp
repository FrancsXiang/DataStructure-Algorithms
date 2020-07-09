#include <iostream>
#include <string>
using namespace std;

class Component {
public:
	virtual ~Component() {}
	virtual string operation() const = 0;
};

class Decorator : public Component {
public:
	Decorator(Component* component_) : component(component_) {}
	string operation() const override {
		return component->operation();
	}
protected:
	Component* component;
};

class ComponentA : public Component {
public:
	string operation() const override {
		return "(ComponentA's Operation)";
	}
};

class DecoratorA : public Decorator {
public:
	DecoratorA(Component* component_) : Decorator(component_) {}
	string operation() const override {
		return "DecoratorA:( " + Decorator::operation() + " )";
	}
};

class DecoratorB : public Decorator {
public:
	DecoratorB(Component* component_) : Decorator(component_) {}
	string operation() const override {
		return "DecoratorB:( " + Decorator::operation() + " )";
	}
};

void client(Component* component) {
	cout << "result: " << component->operation() << endl;
}

int main()
{
	Component* compA = new ComponentA();
	Component* decorA = new DecoratorA(compA);
	Component* decorB = new DecoratorB(decorA);
	client(decorB);
	return 0;
}
