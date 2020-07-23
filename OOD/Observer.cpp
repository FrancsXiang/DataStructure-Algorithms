#include <iostream>
#include <string>
#include <list>
using namespace std;

class IObserver {
public:
	virtual ~IObserver() {}
	virtual void update(const string message) = 0;
	virtual string operation() const = 0;
};

class ISubject {
public:
	virtual ~ISubject() {}
	virtual void attach(IObserver* observer) = 0;
	virtual void dettach(IObserver* observer) = 0;
	virtual void Notify() = 0;
};
class IObserver;
class Subject : public ISubject { 
public:
	Subject(string id_,string message_) : id(id_),message(message_) {}
	void attach(IObserver* observer) override {
		ob_list.push_back(observer);
	}
	void dettach(IObserver* observer) override {
		ob_list.remove(observer);
	}
	void Notify() override {
		for (auto item : ob_list) item->update(this->message);
	}
	void show_observer() {
		cout << "Subject " << this->id << ":" << endl;
		for (auto item : ob_list) cout << "Observer_" << item->operation() << endl;
	}
	void do_something() {
		message = "change the message";
		Notify();
	}
	string operation() {
		return get_id();
	}
	string get_message() {
		return message;
	}
private:
	string id;
	string message;
	list<IObserver*> ob_list;
	string get_id() { return this->id; }
};


class Observer : public IObserver {
public:
	Observer(string id_, Subject* subject_=NULL) : id(id_),subject(subject_) {
		message_from_subject = "";
		subject->attach(this);
	}
	string operation() const override{
		return get_id();
	}
	void update(const string message_) {
		message_from_subject = message_;
		cout << "observer: " << this->id << " get a new message: " << message_from_subject << endl;
	}
	void suscribe(Subject* subject) {
		if (subject) {
			if (this->subject) {
				this->subject->dettach(this);
				cout << "observer: " << this->id << " dettached with subject: " << this->subject->operation() << endl;
			}
			subject->attach(this);
			cout << "observer: " << this->id << " attached with subject: " << subject->operation() << endl;
		}
	}
	void remove_subscribe() {
		if (this->subject) {
			this->subject->dettach(this);
			cout << "observer: " << this->id << " dettached with subject: " << this->subject->operation() << endl;
			this->subject = NULL;
		}
	}
	string get_message() { return message_from_subject; }
private:
	string id;
	Subject* subject;
	string message_from_subject;
	string get_id() const { return this->id; }
};

void client() {
	Subject* subject = new Subject("1", "hello world");
	Observer* ob_1 = new Observer("1", subject);
	Observer* ob_2 = new Observer("2", subject);
	Observer* ob_3 = new Observer("3", subject);
	subject->Notify();
	cout << ob_1->get_message() << endl;
	subject->show_observer();
	ob_2->remove_subscribe();
	subject->do_something();
	cout << ob_3->get_message() << endl;
	subject->show_observer();
}

int main()
{
	client();
	return 0;
}
