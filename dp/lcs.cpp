#include <iostream>
#include <algorithm>
#include <string>
#define MAXN 1001
using namespace std;

int dp[MAXN][MAXN];

//longest_common_subsequence.
int main()
{
	string s1,s2;
	cin >> s1 >> s2;
	for (int i = 1; i <= s1.length(); i++) {
		for (int j = 1; j <= s2.length(); j++) {
			if (s1[i - 1] == s2[j - 1]) dp[i][j] = dp[i - 1][j - 1] + 1;
			else dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
		}
	}
	return 0;
}
