/*
The file implemented add and sub ops,I will finish the multi and div ops soon!(allow leading zero exists)
*/
#include <iostream>
#include <algorithm>
#include <string>
#include <cctype>
using namespace std;
class BigInteger
{
public:
	string add(string, string);
	string sub(string, string);
private:
	string _add(string, string);
	string _sub(string, string);
	bool compare(string, string);
};

bool BigInteger::compare(string a, string b) { //assume a>=0 and b>=0
	reverse(a.begin(), a.end()); reverse(b.begin(), b.end());
	int len1 = 1, len2 = 1;
	for (int i = 1; i < a.length(); i++) {
		if (a[i] != '0') len1++;
		else break;
	}
	for (int i = 1; i < b.length(); i++) {
		if (b[i] != '0') len2++;
		else break;
	}
	if (len1 > len2) return true;
	else if (len2 > len1) return false;
	else if (a[len1 - 1] >= b[len2 - 1]) return true;
	else return false;
}

string BigInteger::_add(string a, string b) { //assume a>=0 and b>=0
	int carry = 0, sum = 0;
	string res;
	int len1 = a.length(); int len2 = b.length();
	reverse(a.begin(), a.end()); reverse(b.begin(), b.end());
	if (len1 > len2) for (int i = 0; i < len1 - len2; i++) b.push_back('0');
	else for (int i = 0; i < len2 - len1; i++) a.push_back('0');
	int len = max(len1, len2);
	for (int i = 0; i < len; i++) {
		sum = a[i] - '0' + b[i] - '0' + carry;
		res.push_back(sum % 10 + '0');
		carry = sum / 10;
	}
	while (carry) {
		res.push_back(carry % 10 + '0');
		carry /= 10;
	}
	while (res.size() && res.back() == '0') res.pop_back();
	if (!res.size()) res.push_back('0');
	reverse(res.begin(), res.end());
	return res;
}

string BigInteger::_sub(string a, string b) { //assume a is bigger than b(a>=0,b>=0)
	int len1 = a.length(); int len2 = b.length();
	reverse(a.begin(), a.end()); reverse(b.begin(), b.end());
	for (int i = 0; i < len1 - len2; i++) b.push_back('0');
	for (int i = 0; i < len1; i++) {
		if (a[i] < b[i]) {
			a[i] += '0' + 10 - b[i];
			a[i + 1]--;
		}
		else {
			a[i] += '0' - b[i];
		}
	}
	while (a.size() && a.back() == '0') a.pop_back();
	if (!a.size()) a.push_back('0');
	reverse(a.begin(), a.end());
	return a;
}

string BigInteger::add(string a, string b) {
	if (isdigit(a[0]) && b[0] == '-') {
		b = b.substr(1);
		if (compare(a, b)) return _sub(a, b);
		else return "-" + _sub(b, a);
	}
	else if (isdigit(a[0]) && isdigit(b[0])) {
		return _add(a, b);
	}
	else if (a[0] == '-' && isdigit(b[0])) {
		a = a.substr(1);
		if (compare(b, a)) return _sub(b, a);
		else return "-" + _sub(a, b);
	}
	else {
		return "-" + _add(a.substr(1), b.substr(1));
	}
}

string BigInteger::sub(string a, string b) {
	if (isdigit(a[0]) && b[0] == '-') return _add(a, b.substr(1));
	else if (isdigit(a[0]) && isdigit(b[0])) {
		if (compare(a, b)) return _sub(a, b);
		else return "-" + _sub(b, a);
	}
	else if (a[0] == '-' && isdigit(b[0])) {
		return "-" + _add(a.substr(1), b);
	}
	else {
		a = a.substr(1); b = b.substr(1);
		if (compare(b, a)) return _sub(b, a);
		else return "-" + _sub(a, b);
	}
}

int main()
{
	string a, b;
	BigInteger cal;
	cin >> a >> b;
	cout << cal.add(a, b) << endl;
	return 0;
}
