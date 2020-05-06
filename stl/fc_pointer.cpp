#include <iostream>
#include <cstring>
using namespace std;

typedef int (*fp) ();

int add() {
	cout << "add" << endl;
}

int (*set_malloc_handler(int (*f) ())) () {
	int (*fp) () = add;
	return fp;
}

fp set_malloc_handler_beta(fp f) {
	fp tmp = add;
	return tmp;
}
