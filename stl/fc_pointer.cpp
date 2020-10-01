#include <iostream>
#include <cstring>
using namespace std;

typedef void (*fp) ();

void add() {
	cout << "add" << endl;
}

void (*set_malloc_handler(void (*f) ())) () {
	void (*fp) () = add;
	return fp;
}

fp set_malloc_handler_beta(fp f) {
	fp tmp = add;
	return tmp;
}

template<typename T, typename A>
class test {
public:
	T a;
	A b;
	test(T a_, A b_) : a(a_) , b(b_) {}
	void print() { cout << "hello world" << endl; }
};

template<typename T, typename A>
class adaptor {
public:
	adaptor(void (test<T, A>::* print) ()) : pf(print) {}
	void (test<T, A>::* pf) ();
};

template<typename T, typename A>
void print(test<T,A> obj, void (test<T, A>::*f) ()) {
	(obj.*f) ();
}

template<typename T, typename A>
inline adaptor<T, A>* generate(void (test<T, A>::* print) ()) {
	return  new adaptor<T, A>(print);
}


int main()
{
	auto fc_1 = set_malloc_handler(add);
	auto fc_2 = set_malloc_handler_beta(add);
	(*fc_1)(); fc_2();
	
	test<int,int> a(2, 3);
	auto func = &test<int,int>::print;
	adaptor<int,int> ada(func);
	//(a.*ada.pf) ();
	//print(a, ada.pf);
	auto c = generate(func);
	(a.*c->pf) ();
	return 0;
}
