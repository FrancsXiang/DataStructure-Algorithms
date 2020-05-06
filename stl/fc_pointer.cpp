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

int main()
{
	auto fc_1 = set_malloc_handler(add);
	auto fc_2 = set_malloc_handler_beta(add);
	fc_1(); fc_2();
}
