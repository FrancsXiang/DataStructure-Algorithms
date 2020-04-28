#include <iostream>
#include <algorithm>
#define MAXN 101
#define MAXV 1001
using namespace std;

// if you want the full pack,initialize res[0] = 0,res[1:] = -inf
// or you want the maximum value, initialize res[:] = 0;
//you could also use cost-effective sort to solve
void orgin() { 
	int vol[MAXN];
	int val[MAXN];
	int res[MAXN][MAXV];
	int v, n;
	cin >> v >> n;
	for (int i = 1; i <= n; i++) cin >> vol[i] >> val[i];
	for (int i = 0; i <= v; i++) res[0][i] = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = vol[i]; j <= v; j++) {
			res[i][j] = max(res[i - 1][j], res[i][j - vol[i]] + val[i]);
		}
	}
}

void space_opt() {
	int vol[MAXN];
	int val[MAXN];
	int res[MAXV];
	int v, n;
	for (int i = 1; i <= n; i++) cin >> vol[i] >> val[i];
	for (int i = 0; i <= v; i++) res[i] = 0;
	for (int i = 1; i <= n; i++) {
		for (int j = vol[i]; j <= v; j++) {
			res[j] = max(res[j], res[j - vol[i]] + val[i]);
		}
	}
}
