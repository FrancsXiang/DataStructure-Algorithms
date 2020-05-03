#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#define MIN_INF -999999999
using namespace std;

template<typename T>
struct cmp {
	bool operator() (const T& a, const T& b) {
		return a < b;
	}
};

template<typename T> //similar to class-types
struct _cmp {
	_cmp() :state(0) {} //record state
	T operator() (const T& a, const T& b) {
		return state = a > b ? a : b;
	}
	T get_state() { return state; }
private:
	T state;
};

template<typename T, typename F>
bool calc(T a, T b, F fc) {
	return fc(a, b);
}

template<typename T, typename F>
class test
{
public:
	F func;
	T getMaxi();
	test(vector<T>,F);
private:
	T maxi;
	vector<T> con;
};

template<typename T,typename F>
T test<T,F>::getMaxi() {
	maxi = MIN_INF;
	for (auto& it : con) maxi = func(maxi, it);
	return maxi;
}

template<typename T, typename F>
test<T,F>::test(vector<T> con, F func) {
	this->con = con;
	this->func = func;
	maxi = MIN_INF;
}

int main()
{
	srand(time(0));
	int x = 3;
	int y = 4;
	string a = "a";
	string b = "b";
	vector<int> v1;
	vector<string> v2;
	cout << calc<int, cmp<int>>(x, y, cmp<int>()) << endl;
	cout << calc<string, cmp<string>>(a, b, cmp<string>()) << endl;
	for (int i = 0; i < 10; i++) v1.push_back(rand() % 1000 + 1);
	test<int, _cmp<int>> judge(v1,_cmp<int>());
	cout << judge.getMaxi() << " " << judge.func.get_state() << endl;
	return 0;
}
