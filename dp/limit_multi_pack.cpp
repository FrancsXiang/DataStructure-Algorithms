#include <iostream>
#include <cstring>
#include <algorithm>
#define MAXN 101
#define MAXV 1001
using namespace std;
int vol[MAXN];
int val[MAXN];
int num[MAXN];
int res[MAXV];
int v, n;
// if you want the full pack,initialize res[0] = 0,res[1:] = -inf
// or you want the maximum value, initialize res[:] = 0;

inline void complete_pack(int c,int w) {
	for (int i = c; i <= v; i++) res[i] = max(res[i], res[i - c] + w);
}

inline void zero_one_pack(int c, int w) {
	for (int i = v; i >= c; i--) res[i] = max(res[i], res[i - c] + w);
}

void limit_multi_pack() {
	cin >> v >> n;
	for (int i = 1; i <= n; i++) cin >> vol[i] >> val[i] >> num[i];
	memset(res, 0, sizeof res);
	for (int i = 1; i <= n; i++) {
		//you can consider the number of i-th item is inf.
		if (vol[i] * num[i] >= v) complete_pack(vol[i], val[i]);
		else {
			//leverage the binary idea,all solution could be made up of binary nums.
			//so you can split it into several parts which could be settled by zero_one_pack solver.
			int k = 1;
			while (k < num[i]) {
				zero_one_pack(vol[i] * k, val[i] * k);
				num[i] -= k;
				k <<= 1;
			}
			zero_one_pack(vol[i] * k, val[i] * k);
		}
	}
}
