#include <iostream>
#include <string>
using namespace std;

class Handler {
public:
	virtual Handler* set_handler(Handler* handler) = 0;
	virtual string handle(string request) = 0;
};

class AbstractHandler : public Handler {
public:
	AbstractHandler() : next_handler(NULL) {}
	Handler* set_handler(Handler* handler) override {
		return this->next_handler = handler;
	}
	string handle(string request) override {
		if (this->next_handler) {
			return this->next_handler->handle(request);
		}
	}
private:
	Handler* next_handler;
};

class HandlerA : public AbstractHandler {
public:
	string handle(string request) override {
		if (request == "A") return "handling request with HandlerA";
		else return AbstractHandler::handle(request);
	}
};

class HandlerB : public AbstractHandler {
public:
	string handle(string request) override {
		if (request == "B") return "handling request with HandlerB";
		else return AbstractHandler::handle(request);
	}
};

void client(Handler* handler,string request) {
	cout << handler->handle(request) << endl;
}

int main()
{
	HandlerA* A = new HandlerA();
	HandlerB* B = new HandlerB();
	A->set_handler(B);
	client(A,"B");
	return 0;
}
