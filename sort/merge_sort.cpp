#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
using namespace std;

void merge_sort(int* s,int low,int high) {
	if(low < high) {
		int mid = (low+high)/2;
		merge_sort(s,low,mid);merge_sort(s,mid+1,high);
		int* tmp = (int*)malloc((high-low+1)*sizeof(int));
		int i = low;int j = mid + 1;int t = 0;
		while(i<=mid&&j<=high) {
			if(s[i] > s[j]) tmp[t++] = s[j++];
			else tmp[t++] = s[i++]; 
		}
		while(i<=mid) tmp[t++] = s[i++];
		while(j<=high) tmp[t++] = s[j++];
		memcpy(s+low,tmp,sizeof(int)*(high-low+1));
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
	merge_sort(s,0,9);
	print(s,10); 
	return 0;
}
