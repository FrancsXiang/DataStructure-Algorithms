#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void shell_sort(int* s,int n) {
	for(int gap=n/2;gap>=1;gap/=2) {
		for(int k=0;k<gap;k++) {
			for(int i=k;i<n-1;i+=gap) {
				for(int j=i;j>=0;j-=gap) {
					if(s[j] > s[j+gap]) swap(s[j],s[j+gap]);
					else break;
				}
			}
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
	shell_sort(s,10);
	print(s,10); 
	return 0;
}
