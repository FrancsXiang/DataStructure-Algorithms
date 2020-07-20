#include <iostream>
#include <ctime>
#include <string>
#include <vector>
using namespace std;

class Memoto {
public:
	virtual string get_name() const = 0;
	virtual string get_state() const = 0;
	virtual string get_date() const = 0;
};

class ConcreteMemoto : public Memoto {
public:
	ConcreteMemoto(string state_) {
		this->state = state_;
		time_t now = time(0);
		this->date = ctime(&now);
	}
	string get_state() const override {
		return this->state;
	}
	string get_date() const override {
		return this->date;
	}
	string get_name() const override {
		return this->date + "( " + this->state.substr(0,9) + " )";
	}
private:
	string date;
	string state;
};

class Originator {
public:
	Originator(string state_) : state(state_) {}
	void work() {
		cout << "Originator works.(state changed)" << endl;
		this->state = generate_random_string();
	}
	Memoto* save() {
		cout << "memoto state saved." << endl;
		return new ConcreteMemoto(this->state);
	}
	void restore(Memoto* memoto) {
		cout << "memoto state restored." << endl;
		this->state = memoto->get_state();
	}
private:
	string state;
	string generate_random_string(int length = 10) {
		string res;
		const char alphanum[] = "0123456789"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"abcdefghijklmnopqrstuvwxyz";
		int len = sizeof(alphanum) - 1;
		for (int i = 0; i < length; i++) res += alphanum[rand() % len];
		return res;
	}
};

class Caretaker {
public:
	Caretaker(Originator* ori_) : ori(ori_) {}
	void BackUp() {
		cout << "Caretaker: Saving Originator's state" << endl;
		this->memotos.push_back(this->ori->save());
	}
	void Undo() {
		if (!this->memotos.size()) {
			return;
		}
		Memoto* last = this->memotos.back();
		this->memotos.pop_back();
		cout << "Caretaker: Restoring state: " << last->get_name() << endl;
		try
		{
			this->ori->restore(last);
		}
		catch (const std::exception&)
		{
			this->Undo();
		}
	}
	void showHistory() {
		cout << "memetos history:" << endl;
		for (auto item : this->memotos) {
			cout << item->get_name() << endl;
		}
	}
private:
	vector<Memoto*> memotos;
	Originator* ori;

};

void client()
{
	Originator* ori = new Originator("origin_state");
	Caretaker* caretaker = new Caretaker(ori);
	caretaker->BackUp();
	ori->work();
	caretaker->BackUp();
	ori->work();
	caretaker->BackUp();
	ori->work();
	caretaker->BackUp();
	caretaker->showHistory();
	caretaker->Undo();
	caretaker->Undo();
	caretaker->showHistory();
}

int main()
{
	client();
	return 0;
}
