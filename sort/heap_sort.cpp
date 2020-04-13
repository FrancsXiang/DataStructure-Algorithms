#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#define MAXN 1000000
using namespace std;

void adjust(int* s,int index,int len) {
	int rec = index;
	if(2*index+1<len && s[2*index+1] > s[rec]) rec = 2*index+1;
	if(2*index+2<len && s[2*index+2] > s[rec]) rec = 2*index+2;
	if(rec!=index) {
		swap(s[rec],s[index]);
		adjust(s,rec,len);
	}
}

void heap_sort(int* s,int n) {
	for(int i=n/2-1;i>=0;i--) adjust(s,i,n);
	for(int i=1;i<n;i++) {
		swap(s[0],s[n-i]);
		adjust(s,0,n-i);
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
	srand(time(0));
	for(int i=0;i<n;i++) s[i] = rand() % 1000 + 1;
	print(s,n);
	heap_sort(s,n);
	print(s,n);
	return 0;
}
