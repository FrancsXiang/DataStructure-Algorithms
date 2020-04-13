#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#define MAXN 1000000
using namespace std;

void radix_sort(int* s,int len) {//element-only >= 0(you can add another bucket for negative number.)
	int max_val = -1;
	int exp = 1;
	int radix = 10;
	int cnt[radix];
	int tmp[len];
	for(int i=0;i<len;i++) max_val = max(max_val,s[i]);
	while(max_val / exp) {
		memset(cnt,0,sizeof(cnt));
		for(int i=0;i<len;i++) cnt[(s[i]/exp)%10]++;
		for(int i=1;i<radix;i++) cnt[i] += cnt[i-1];
		for(int i=len-1;i>=0;i--) tmp[--cnt[(s[i]/exp)%10]] = s[i];
		memcpy(s,tmp,sizeof(tmp));
		exp *= 10;
	}
}

void print(int* s,int n) {
	for(int i=0;i<n;i++) cout << s[i] << " ";
	cout << endl;
}

int s[MAXN];

int main()
{
	int n;
	cin >> n;
	srand(time(0));
	for(int i=0;i<n;i++) s[i] = rand() % 1000 + 1;
	print(s,n);
	radix_sort(s,n);
	print(s,n);
	return 0;
}
