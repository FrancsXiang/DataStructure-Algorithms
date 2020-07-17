#include <iostream>
#include <string>
using namespace std;

class BaseComponent;
class Mediator {
public:
	virtual void Notify(BaseComponent* sender, string event) const = 0;
};

class BaseComponent {
public:
	BaseComponent(Mediator* mediator_ = NULL) : mediator(mediator_) {}
	void set_mediator(Mediator* mediator_) { this->mediator = mediator_; }
protected:
	Mediator* mediator;
};

class Component1 : public BaseComponent {
public:
	void doA() {
		if (mediator) {
			cout << "Component1 do A" << endl;
			mediator->Notify(this, "A");
		}
	}
	void doB() {
		if (mediator) {
			cout << "Component1 do B" << endl;
			mediator->Notify(this, "B");
		}
	}
};

class Component2 : public BaseComponent {
public: 
	void doC() {
		if (mediator) {
			cout << "Component2 do C" << endl;
			mediator->Notify(this, "C");
		}
	}

	void doD() {
		if (mediator) {
			cout << "Component2 do D" << endl;
			mediator->Notify(this, "D");
		}
	}
};

class ConcreteMediator : public Mediator {
public:
	ConcreteMediator(Component1* comp1_, Component2* comp2_) : comp_1(comp1_), comp_2(comp2_) {
		comp_1->set_mediator(this);
		comp_2->set_mediator(this);
	}
	void Notify(BaseComponent* sender, string event) const override {
		if (event == "A") {
			this->comp_1->doB();
		}
		if (event == "C") {
			this->comp_2->doD();
		}
	}
private:
	Component1* comp_1;
	Component2* comp_2;
};

void client() {
	Component1* comp1 = new Component1();
	Component2* comp2 = new Component2();
	ConcreteMediator* mediator = new ConcreteMediator(comp1, comp2);
	comp1->doA();
	comp2->doC();
}

int main()
{
	client();
	return 0;
}
