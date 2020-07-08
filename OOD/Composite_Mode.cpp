#include <iostream>
#include <algorithm>
#include <string>
#include <list>

using namespace std;

class Component {
public:
	virtual ~Component() {}
	void set_parent(Component* parent) { this->parent = parent; }
	Component* get_parent() { return parent; }
	virtual void add(Component*) {}
	virtual void erase(Component*) {}
	virtual string operation() const = 0;
	virtual bool is_composite() { return false; }
protected:
	Component* parent;
};

class Leaf : public Component {
public:
	string id;
	Leaf(string id_) : id(id_) {}
	string operation() const override { return "leaf_" + id; }
};

class Composite : public Component {
public:
	void add(Component* component) override {
		children.push_back(component);
		component->set_parent(this);
	}
	void erase(Component* component) override {
		children.remove(component);
		component->set_parent(NULL);
	}
	bool is_composite() override { return true; }
	string operation() const override {
		string result = "branch:(";
		for (auto component : children) {
			if (children.back() == component) {
				result += component->operation() + ")";
			}
			else {
				result += component->operation() + "+";
			}
		}
		return result;
	}
protected:
	list<Component*> children;
};

void client_1(Component* component) {
	cout << component->operation() << endl;
}
 
void client_2(Component* component_1, Component* component_2) {
	if (component_1->is_composite() && !component_2->get_parent()) component_1->add(component_2);
	cout << component_1->operation() << endl;
}

int main()
{
	Component* leaf_1 = new Leaf("1");
	Component* leaf_2 = new Leaf("2");
	Component* leaf_3 = new Leaf("3");
	Composite* composite_1 = new Composite();
	Composite* composite_2 = new Composite();
	composite_1->add(leaf_1);
	composite_1->add(leaf_2);
	composite_2->add(leaf_3);
	//composite_1->add(composite_2);
	client_1(composite_1);
	client_2(composite_1, composite_2);
	client_1(composite_2);
	return 0;
}
