#include <iostream>
#include <string>

using namespace std;

class AbstractClass {
public:
	void template_method() const {
		base_operation();
		require_operation();
	}
protected:
	void base_operation() const {
		cout << "AbstractClass: I am doing base operation." << endl;
	}
	virtual void require_operation() const = 0;
};

class ConcreteClassA : public AbstractClass {
protected:
	void require_operation() const override {
		cout << "ConcreteClassA: I am doing require operation." << endl;
	}
};

class ConcreteClassB : public AbstractClass {
protected:
	void require_operation() const override {
		cout << "ConcreteClassB: I am doing require operation." << endl;
	}
};

void client(AbstractClass* ac) {
	ac->template_method();
}

int main()
{
	ConcreteClassA* ca = new ConcreteClassA();
	client(ca);
	ConcreteClassB* cb = new ConcreteClassB();
	client(cb);
	return 0;
}
