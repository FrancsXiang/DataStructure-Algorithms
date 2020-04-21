#include <iostream>
using namespace std;
typedef long long LL;

LL quick_power(LL a, LL b, LL mod) { //a^b % mod
	LL res = 1;
	while (b) {
		if (b & 1) res = (res * a) % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return res;
}

int main()
{
	cout << quick_power(3, 2, 2) << endl;
	return 0;
}
