#include <iostream>
#include <string>
#include <cstring>
using namespace std;

class prototype {
public:
	virtual ~prototype() { delete[] field; }
	virtual prototype* clone() = 0;
	string getId() { return id; }
	char* getField() { return field; }
protected:
	string id;
	char* field;
};


class prototypeA : public prototype {
public:
	prototypeA(const string id, const char* str) {
		if (strlen(str)== 0) {
			field = new char[1];
			field[0] = '\0';
		}
		else {
			field = new char[1 + strlen(str)];
			strcpy_s(field, 1 + strlen(str), str);
		}
		this->id = id;
	}
	prototype* clone() override {
		return new prototypeA(*this);
	}
	prototypeA& operator=(prototypeA& copy) {
		this->id = copy.id;
		this->field = copy.field;
		return *this;
	}
private:
	prototypeA(const prototypeA& copy) {
		this->id = copy.id;
		this->field = new char[strlen(copy.field) + 1];
		strcpy_s(this->field, 1 + strlen(copy.field), copy.field);
	}
};

void client() {
	prototype* a = new prototypeA("franc_zi", "hello world");
	prototype* b = a->clone();
	cout << b->getId() << endl;
	cout << b->getField() << endl;
}

int main()
{
	client();
	return 0;
}
