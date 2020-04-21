#include <iostream>
using namespace std;
typedef long long LL;

inline LL gcd(LL a, LL b) { return b == 0 ? a : gcd(b, a % b); }

inline LL lcm(LL a, LL b) { return a / gcd(a, b) * b; }

inline LL exgcd(LL a, LL b, LL& x, LL& y) {
	if (b == 0) {
		x = 1;
		y = 0;
		return a;
	}
	LL res = exgcd(b, a % b, x, y);
	LL tmp = y;
	y = x - (a / b) * y;
	x = tmp;
	return res;
}
