#include <iostream>
#include <cstring>
#define MAXN 10000000
using namespace std;
typedef long long LL;

bool vis[MAXN];
LL cnt[MAXN];

bool is_prime(LL n) {
	if (n == 2 || n == 3) return true;
	if (n % 6 != 1 && n % 6 != 5) return false;
	for (LL i = 5; i * i <= n; i += 6) if (n % i == 0 || n % (i + 2) == 0) return false;
	return true;
}

void sieve(LL n) {
	memset(vis, true, sizeof vis);
	vis[0] = vis[1] = 0;
	for (int i = 2; i * i <= n; i++) {
		if (vis[i]) {
			for (int j = i * i; j <= n; j += i) {
				vis[i] = false;
			}
		}
	}
}

void euler(LL n) {
	int t = 0;
	for (int i = 2; i <= n; i++) {
		if (!vis[i]) cnt[t++] = i;
		for (int j = 0; j < t && i * cnt[j] <= n; j++) {
			vis[i * cnt[j]] = true;
			if (i % cnt[j] == 0) break;
		}
	}
}

int main() {
	sieve(1000);
	return 0;
}
