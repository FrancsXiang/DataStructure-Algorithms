#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void insertion_sort(int* s,int n) {
	for(int i=0;i<n-1;i++) {
		for(int j=i;j>=0;j--) {
			if(s[j] > s[j+1]) swap(s[j],s[j+1]);
		}
	}
}

void print(int* s,int n) {
	for(int i=0;i<n;i++) cout << s[i] << " ";
}

int main()
{
	int s[10];
	srand(time(0));
	for(int i=0;i<10;i++) s[i] = rand() % 1000 + 1;
	insertion_sort(s,10);
	print(s,10); 
	return 0;
}
