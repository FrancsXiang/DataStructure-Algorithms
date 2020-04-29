#include <iostream>
#include <algorithm>
#include <string>
#define MAXN 1001
using namespace std;

int dp[MAXN];

//longest_subsequence with ascending order strictly.
int main()
{
	string s;
	int len, index;
	for (int i = 0; i < s.length(); i++) {
		for (int j = 0; j < i; j++) {
			len = index = -1;
			if (s[j] < s[i] && dp[j] > len) {
				index = j;
				len = dp[j];
			}
		}
		if(index != -1) dp[i] = dp[index] + 1;
	}
	return 0;
}
