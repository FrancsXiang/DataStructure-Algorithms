#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
using namespace std;

void quick_sort(int* s,int low,int high) {
	if(low < high) {
		int rec = s[low];
		int i = low;
		int j = high;
		while(i<j) {
			while(s[j]>rec && i < j) j--;
			if(i<j) s[i++] = s[j];
			while(s[i]<rec && i < j) i++;
			if(i<j) s[j--] = s[i];
		}
		s[i] = rec;
		quick_sort(s,low,i-1);quick_sort(s,i+1,high);
	} 
}

void print(int* s,int n) {
	for(int i=0;i<n;i++) cout << s[i] << " ";
	cout << endl;
}

int main()
{
	int n = 30;
	int s[n];
	srand(time(0));
	for(int i=0;i<n;i++) s[i] = rand() % 1000 + 1;
	print(s,n);
	quick_sort(s,0,n-1);
	print(s,n); 
	return 0;
}
