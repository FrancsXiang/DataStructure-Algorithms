#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <vector>
#define MAXN 1001
using namespace std;
//longest_palindrome_string

int brute_force(string s) {
	int len = 1;
	for (int i = 1; i < s.length() - 1; i++) {
		int j = i - 1;
		int k = i + 1;
		int cnt = 0;
		while (j >= 0 && k < s.length() && s[j] == s[k]) cnt++, j--, k++;
		len = max(len, 2 * cnt + 1);
	}
	for (int i = 0; i < s.length() - 1; i++) {
		if (s[i] == s[i + 1]) {
			int j = i - 1;
			int k = i + 2;
			int cnt = 0;
			while (j >= 0 && k < s.length() && s[j] == s[k]) cnt++, j--, k++;
			len = max(len, 2 * cnt + 2);
		}
	}
	return len;
}

//dp[last_index][length] represent possibility of being a palindrome_string
int dp(string s) {
	int res = 1, len = s.length();
	vector<vector<bool>> dp(len, vector<bool>(len + 1));
	for (int i = 0; i < len; i++) {
		dp[i][1] = true;
		if (i && s[i] == s[i - 1]) dp[i][2] = true;
	}
	for (int gap = 3; gap <= len; gap++) {
		for (int i = gap - 1; i <= len - gap; i++) {
			if (s[i - gap + 1] == s[i] && dp[i - 1][gap - 2]) {
				dp[i][gap] = true;
				res = max(res, gap);
			}
		}
	}
	return res;
}


//r[i] means the radius of the palindrome_string with intermediate index i(included)
int Manacher(string s) {
	string tmp = "#";
	for (int i = 0; i < s.length(); i++) {
		tmp.push_back(s[i]);
		tmp.push_back('#');
	}
	if (!s.length()) tmp.push_back('#');
	s = tmp;
	int pos = 0, max_right = 0, res = 1;
	vector<int> r(s.length());
	for (int i = 0; i < s.length(); i++) {
		if (i < max_right) r[i] = min(r[2 * pos - i], max_right - i);
		else r[i] = 1;
		while (i - r[i] >= 0 && i + r[i] < s.length() && s[i - r[i]] == s[i + r[i]]) r[i]++;
		if (i + r[i] - 1 > max_right) {
			max_right = i + r[i] - 1;
			pos = i;
		}
		res = max(res, r[i] - 1);
	}
	return 2 * res - 1;
}
