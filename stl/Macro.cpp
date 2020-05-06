#include <iostream>
#include <cstdio>
#include <string>
#define TEXT_A "hello world"
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define LOG(msg) cout << msg << endl
#define TYPE(type,name) type type##_##name
#define MSG(x) puts(TEXT   ##  _A)
#define string_input(s) getline(cin,s)
#define output() cout << "no access" << endl
#define printLog(s,...) printf(s,__VA_ARGS__) 
#define printDBL(exp) printf(#exp "= %d\n", exp)
#define STR(s) #s
#define XSTR(s) STR(s)
#if 0
#undef STR(s)
#endif
#define ADD(x,y,type) \
type add(type x, type y) \
{ \
	return x + y; \
} 

using namespace std;

int main()
{
	string s;
	cout << MIN(1,3) << endl;
	LOG("out of memory!");
	TYPE(int, 1) = 3;
	string_input(s);
	cout << s << endl;
	output();
	printLog("hello world\n");
	printDBL(4 * 3);
	MSG(A);
	LOG(XSTR(hello world));
	LOG(STR(hello world""));
	return 0;
}
