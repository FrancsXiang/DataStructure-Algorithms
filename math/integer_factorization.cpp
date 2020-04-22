#include <iostream>
using namespace std;
typedef long long LL;

int main()
{
	LL n,cnt;
	cin >> n;
	for (LL i = 2; i * i <= n; i++) {
		if (n % i == 0) {
			for (cnt = 0; !(n % i) ; cnt++) n /= i;
			cout << i << " ";
		}
	}
	if (n != 1) cout << n << endl;
	return 0;
}
