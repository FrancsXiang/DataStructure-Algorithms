#include <iostream>
#include <string>
using namespace std;

class command {
public:
	virtual ~command() {}
	virtual void execute() const = 0;
};

class receiver {
public:
	void process_1(string s) {
		cout << "receiver works with " + s << endl;
	}
	void process_2(string s) {
		cout << "receiver also works with " + s << endl;
	}
};

class concrete_command : public command {
public:
	concrete_command(receiver* recv_, string s_) : recv(recv_), s(s_) {}
	void execute() const override{
		recv->process_1(s);
		recv->process_2(s);
	}
private:
	receiver* recv;
	string s;
};

class invoker {
public:
	invoker(command* comd_=NULL) : comd(comd_) {}
	void set_comd(command* comd_) { comd = comd_; }
	void do_something() {
		if (comd) {
			comd->execute();
		}
		else {
			cout << "There is no binding command." << endl;
		}
	}
private:
	command* comd;
};

int main()
{
	receiver* recv = new receiver();
	concrete_command* comd = new concrete_command(recv,"hello world");
	invoker* call = new invoker();
	call->do_something();
	call->set_comd(comd);
	call->do_something();
	return 0;
}
