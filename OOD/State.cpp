#include <iostream>
#include <typeinfo>
using namespace std;

class Context;
class State {
public:
	virtual ~State() {}
	virtual void handle_1() = 0;
	virtual void handle_2() = 0;
	void set_context(Context* context) {
		this->context = context;
	}
protected:
	Context* context;
};

class Context {
public:
	~Context() { if(this->state) delete this->state; }
	Context(State* state_ = NULL) { this->state = NULL; change_state(state_); }
	void change_state(State* state) {
		if (state) {
			cout << "Context change to state: " << typeid(*state).name() << endl;
			if (this->state) delete this->state;
			this->state = state;
			this->state->set_context(this);
		}
	}
	void request_1() {
		this->state->handle_1();
	}
	void request_2() {
		this->state->handle_2();
	}
private:
	State* state;
};

class StateA : public State {
public:
	void handle_1() override;
	void handle_2() override {
		cout << "StateA deal with request_2" << endl;
	}
};

class StateB : public State {
public:
	void handle_1() override {
		cout << "StateB deal with request_1" << endl;
	}
	void handle_2() override {
		cout << "StateB deal with request_2" << endl;
		this->context->change_state(new StateA);
	}
};

void StateA::handle_1() {
	cout << "StateA deal with request_1" << endl;
	this->context->change_state(new StateB);
}

void client() {
	Context* context = new Context(new StateA);
	context->request_1();
	context->request_2();
	delete context;
}

int main()	
{
	client();
	return 0;
}
