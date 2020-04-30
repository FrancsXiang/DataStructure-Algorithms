#include <iostream>
#include <algorithm>
#include <string>
#define MAXN 1001
using namespace std;

int len[MAXN][MAXN];

//minimum distance from s1 to s2;
int main()
{
	int mini;
	string s1, s2;
	cin >> s1 >> s2;
	for (int i = 1; i <= s1.length(); i++) len[i][0] = i;
	for (int i = 1; i <= s2.length(); i++) len[0][i] = i;
	for (int i = 1; i <= s1.length(); i++) {
		for (int j = 1; j <= s2.length(); j++) {
			mini = min(len[i][j - 1] + 1, len[i - 1][j] + 1);
			if (s1[i - 1] == s2[j - 1]) mini = min(mini, len[i - 1][j - 1] + 1);
			len[i][j] = mini;
		}
	}
	return 0;
}
