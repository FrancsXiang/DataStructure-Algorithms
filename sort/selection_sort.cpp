#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void selection_sort(int* s,int n) {
	for(int i=0;i<n;i++) {
		int mini = s[i];
		int rec = i;
		for(int j=i+1;j<n;j++) if(mini > s[j]) {
			mini = s[j];
			rec = j;
		}
		if(i!=rec) swap(s[i],s[rec]);
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
	selection_sort(s,10);
	print(s,10); 
	return 0;
}
