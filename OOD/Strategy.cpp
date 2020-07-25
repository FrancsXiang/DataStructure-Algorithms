#include <iostream>
#include <string>
using namespace std;

class Strategy {
public:
	virtual ~Strategy() {}
	virtual string do_algorithm() const = 0;
};

class StrategyA : public Strategy {
public:
	string do_algorithm() const override {
		return "Algorithm A is called";
	}
};

class StrategyB : public Strategy {
public:
	string do_algorithm() const override {
		return "Algorithm B is called";
	}
};

class Context {
public:
	~Context() { delete this->strategy; }
	Context(Strategy* strategy_=NULL) : strategy(strategy_) {}
	void set_strategy(Strategy* strategy) { this->strategy = strategy; }
	string business_logic() {
		if(this->strategy) return this->strategy->do_algorithm();
	}
private:
	Strategy* strategy;
};

void client() {
	StrategyA* A = new StrategyA();
	StrategyB* B = new StrategyB();
	Context* context = new Context(A);
	cout << context->business_logic() << endl;
	context->set_strategy(B);
	cout << context->business_logic() << endl;
}

int main()
{
	client();
	return 0;
}
