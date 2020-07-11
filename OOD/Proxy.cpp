#include <iostream>
#include <string>
using namespace std;

class Subject {
public:
	virtual ~Subject() {}
	virtual void request() const = 0;
};

class Realsubject : public Subject {
public:
	void request() const override {
		cout << "Realsubject: handling request" << endl;
	}
};

class Proxy : public Subject {
public:
	Proxy(Realsubject* realSub_ = NULL) {
		realSub = realSub_ ? realSub_ : new Realsubject();
	}
	void request() const override {
		if (check_access()) {
			realSub->request();
			log_time();
		}
	}
private:
	Realsubject* realSub;
	bool check_access() const {
		cout << "checking the access priority" << endl;
		return true;
	}
	void log_time() const {
		cout << "logging time of request" << endl;
	}
};

void client(Subject& subject) {
	subject.request();
}

int main()
{
	Realsubject* realSub = new Realsubject();
	client(*realSub);
	Proxy* proxy = new Proxy();
	client(*proxy);
	return 0;
}
