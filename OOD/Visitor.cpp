#include <iostream>
#include <string>
using namespace std;

class ComponentA;
class ComponentB;

class Visitor {
public:
	virtual ~Visitor() {}
	virtual void visit_A(ComponentA* comp_a) = 0;
	virtual void visit_B(ComponentB* comp_b) = 0;
};

class Component {
public:
	virtual ~Component() {}
	virtual void accept(Visitor* visitor)  = 0;
};

class ComponentA : public Component {
public:
	ComponentA(string record_="") : record(record_) {}
	void accept(Visitor* visitor) override {
		visitor->visit_A(this);
	}
	void set_record(string record_) { this->record = record_; }
	string get_record() { return this->record; }
private:
	string record;
};

class ComponentB : public Component {
public:
	ComponentB(string record_ = "") : record(record_) {}
	void accept(Visitor* visitor) override {
		visitor->visit_B(this);
	}
	void set_record(string record_) { this->record = record_; }
	string get_record() { return this->record; }
private:
	string record;
};

class VisitorA : public Visitor {
public:
	void visit_A(ComponentA* comp_a) override {
		comp_a->set_record("visitorA visits componentA");
	}
	void visit_B(ComponentB* comp_b) override {
		comp_b->set_record("visitorA visits componentB");
	}
};

class VisitorB : public Visitor {
public:
	void visit_A(ComponentA* comp_a) override {
		comp_a->set_record("visitorB visits componentA");
	}
	void visit_B(ComponentB* comp_b) override {
		comp_b->set_record("visitorB visits componentB");
	}
};

void client(Component* comp,Visitor* visitor) {
	comp->accept(visitor);
}

int main()
{
	VisitorA* visitorA = new VisitorA();
	VisitorB* visitorB = new VisitorB();
	ComponentA* compA = new ComponentA("hello");
	ComponentB* compB = new ComponentB("world");
	client(compA, visitorB);
	client(compB, visitorA);
	cout << compA->get_record() << endl;
	cout << compB->get_record() << endl;
	return 0;
}
