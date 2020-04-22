/*
This is a release file of implementation of BigInteger.Works Well!(add/sub/multiply/div(mod) ops included with leading zero supported)
*/
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <cctype>
#define EQUAL 1
#define GREATER 2
using namespace std;

class BigInteger
{
public:
	string add(string, string);
	string sub(string, string);
	string multiply(string, string);
	pair<string, string> div(string, string);//you could get the quotient and remainder both together.
private:
	string _add(string, string);
	string _sub(string, string);
	string _multiply(string, string);
	pair<string, string> _div(string, string);
	bool compare(string, string, int = EQUAL);
	string b_search(string, string);
};

bool BigInteger::compare(string a, string b, int code) { //assume a>=0 and b>=0
	int len1 = a.length(); int len2 = b.length();
	reverse(a.begin(), a.end()); reverse(b.begin(), b.end());
	if (len1 < len2) for (int i = 0; i < len2 - len1; i++) a.push_back('0');
	else for (int i = 0; i < len1 - len2; i++) b.push_back('0');
	reverse(a.begin(), a.end()); reverse(b.begin(), b.end());
	if (code == EQUAL) return a >= b;
	else return a > b;
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

string BigInteger::_multiply(string a, string b) { //assume a>=0 and b>=0
	int len1 = a.length(), len2 = b.length();
	int carry = 0, sum = 0;
	vector<int> res(len1 + len2 - 1);
	string ans;
	reverse(a.begin(), a.end()); reverse(b.begin(), b.end());
	for (int i = 0; i < len1; i++) {
		for (int j = 0; j < len2; j++) {
			res[i + j] += (a[i] - '0') * (b[j] - '0');
		}
	}
	for (int i = 0; i < res.size(); i++) {
		sum = res[i] + carry;
		ans.push_back(sum % 10 + '0');
		carry = sum / 10;
	}
	while (carry) {
		ans.push_back(carry % 10 + '0');
		carry /= 10;
	}
	while (ans.size() && ans.back() == '0') ans.pop_back();
	if (!ans.size()) ans.push_back('0');
	reverse(ans.begin(), ans.end());
	return ans;
}

string BigInteger::b_search(string divid, string divisor) {
	int low = 0, high = 9, mid;
	while (low < high) {
		mid = (low + high) / 2;
		if (low + 1 == high) {
			string res(1, high + '0');
			if (compare(_multiply(divisor, res), divid, GREATER)) high = low;
			break;
		}
		string res(1, mid + '0');
		if (compare(_multiply(divisor, res), divid, GREATER)) high = mid - 1;
		else low = mid;
	}
	return string(1, '0' + low);
}

pair<string, string> BigInteger::_div(string a, string b) { //assume a>=0 and b>0
	pair<string, string> ans;
	string divid, quoti;
	for (int i = 0; i < a.size(); i++) {
		divid.push_back(a[i]);
		quoti = b_search(divid, b);
		ans.first.push_back(quoti[0]);
		divid = _sub(divid, _multiply(quoti, b));
	}
	auto& seq = ans.first;
	reverse(seq.begin(), seq.end());
	while (seq.size() && seq.back() == '0') seq.pop_back();
	if (!seq.size()) seq.push_back('0');
	reverse(seq.begin(), seq.end());
	auto& seq_l = ans.second;
	seq_l = divid;
	reverse(seq_l.begin(), seq_l.end());
	while (seq_l.size() && seq_l.back() == '0') seq_l.pop_back();
	if (!seq_l.size()) seq_l.push_back('0');
	reverse(seq_l.begin(), seq_l.end());
	return ans;
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

string BigInteger::multiply(string a, string b) {
	int flag1 = 1, flag2 = 1;
	if (a[0] == '-') flag1 = -1, a = a.substr(1);
	if (b[0] == '-') flag2 = -1, b = b.substr(1);
	if (flag1 * flag2 == 1) return _multiply(a, b);
	else return "-" + _multiply(a, b);
}

pair<string, string> BigInteger::div(string a, string b) {
	pair<string, string> ans;
	int flag1 = 1, flag2 = 1;
	if (b == "0") throw "division zero error!";
	if (a[0] == '-') flag1 = -1, a = a.substr(1);
	if (b[0] == '-') flag2 = -1, b = b.substr(1);
	ans.first = _div(a, b).first;
	ans.second = _div(a, b).second;
	if (flag1 * flag2 != 1) ans.first = "-" + ans.first;
	if (flag1 == -1) ans.second = "-" + ans.second;
	return ans;
}

int main()
{
	string a, b;
	BigInteger cal;
	cin >> a >> b;
	try
	{
		auto res = cal.div(a, b);
		cout << res.first << " " << res.second << endl;
	}
	catch (const char* msg)
	{
		cout << msg << endl;
	}
	return 0;
}
