#include <iostream>
#include <string>
#include <vector>
using namespace std;
//referred_docs:https://wiki.jikexueyuan.com/project/kmp-algorithm/define.html


//next[i] shows longest_pre_suf_pair_length between 0 and i-1.
void getNext(string m,vector<int>& next) {
	int i = 0, k = -1;
	next[i] = -1; // next[0] == -1 means no elem front it
	while (i < m.length() - 1) {
		if (k == -1 || m[i] == m[k]) { 
			k++;
			i++;
			next[i] = k;
		}
		else
			k = next[k]; // divide into transitive smaller symmetrical block to find the most bigger pair.
	}
}

int kmp(string s,string m) {
	vector<int> next(m.size());
	getNext(m,next);
	int i = 0, j = 0;
	int len1 = s.length(), len2 = m.length();
	while (i < len1 && j < len2) {
		// j == -1 means no elem could be used to pair the s[i].
		// just rest m and go head with index i!
		if (j == -1 || s[i] == m[j]) {
			i++;
			j++;
		}
		else
			j = next[j];// adjust the index j
	}
	if (j == len2) return i - j;
	else return -1;
}
