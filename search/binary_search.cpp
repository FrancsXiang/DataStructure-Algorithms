#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
using namespace std;

int main()
{
	int low,high,mid,val,res=-1;
	int s[10];
	srand(time(0));
	for(int i=0;i<10;i++) s[i] = rand() % 1000 + 1;
	low = 0;high = 9;
	val = s[6] = 1000;
	sort(s,s+10);
	while(low <= high) {
		mid = (low+high) / 2;
		if(s[mid] > val) high = mid - 1;
		else if(s[mid] < val) low = mid + 1;
		else {
			res = mid;
			break;
		}
	}
	if(res!=-1) cout << s[res] << endl;
 	return 0;
}
