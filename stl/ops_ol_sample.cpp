#include <iostream>
using namespace std;
// (++) / (--) / (+) / (-) / (*) / (/) / (cout) / (cin) ops overloading sample of INT class
class INT
{
	friend ostream& operator<< (ostream& out, const INT& elem);
	friend istream& operator>> (istream& in, const INT& elem);
public:
	INT(int i) : m_i(i) {}
	INT& operator++() {
		++(this->m_i);
		return *this;
	}
	const INT operator++(int) {
		INT tmp = *this;
		++(*this);
		return tmp;
	}
	INT& operator--() {
		--(this->m_i);
		return *this;
	}
	const INT operator--(int) {
		INT tmp = *this;
		--(*this);
		return tmp;
	}
	int& operator*() const {
		return (int&)m_i;
	}
	INT operator+(INT& b) {
		return INT(this->m_i + b.m_i);
	}
	INT operator-(INT& b) {
		return INT(this->m_i - b.m_i);
	}
	INT operator*(INT& b) {
		return INT(this->m_i * b.m_i);
	}
	INT operator/(INT& b) {
		return INT(this->m_i / b.m_i);
	}
private:
	int m_i;
};


ostream& operator<< (ostream& out, const INT& elem) {
	out << elem.m_i;
	return out;
}

istream& operator>> (istream& in, const INT& elem) {
	in >> elem.m_i;
	return in;
}

int main()
{
	INT a(2), b(2);
	auto c = a++;
	cout << *a << " " << *c << endl;
	cout << a++ << endl;
	cout << ++c << endl;
	cout << a << " " << b << endl;
	cout << a / b << endl;
	return 0;
}
