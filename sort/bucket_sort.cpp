//bucket_sort implementation by array.
//you could learn more about the bucket_sort extension knowledge which is widely used in Hadoop,Tero_sort.
//strategy:
//1.make sure of the range of datasets. 
//2.make uniform splits on the datasets. 
//3.group the data into several buckets.
//4.sort on each bucket parallelly.
//5.acquire the result sequentially.
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#define MAXN 1000
using namespace std;

vector<double> arr(MAXN),res;
vector<vector<double>> buckets;

int main()
{
	
	int n,m,diff,gap,mini;
	int low, high, mid;
	cout << "how many buckets you want:(1<=n<=8)" << endl;
	while (cin >> n && n < 1 || n > 8) cout << "please follow the instruction ahead." << endl;
	buckets.resize(n);
	cout << "how many element you want to sort:(m >= 1)" << endl;
	while(cin >> m && m < 1) cout << "please follow the instruction ahead." << endl;
	srand(time(0));
	for (int i = 0; i < m; i++) arr[i] = rand() % 1000 + 1; 
	mini = 1; diff = 1000;//diff = max_val - min_val + 1;
	low = 1; high = diff;
	while (low < high) {
		mid = (low + high) / 2;
		if (mid * n >= diff) high = mid;
		else low = mid + 1;
	}
	gap = low;
	for (int i = 0; i < m; i++) buckets[(arr[i] - mini) / gap].push_back(arr[i]);
	for (int i = 0; i < n; i++) sort(buckets[i].begin(), buckets[i].end());
	for (int i = 0; i < n; i++) res.insert(res.end(), buckets[i].begin(), buckets[i].end());
	for (int i = 0; i < m; i++) cout << arr[i] << " ";
	cout << endl;
	for (int i = 0; i < res.size(); i++) cout << res[i] << " ";
	cout << endl;
	for (int i = 0; i < n; i++) {
		cout << "bucket_" << i << ":" << endl;
		for (int j = 0; j < buckets[i].size(); j++) cout << buckets[i][j] << " ";
		cout << endl;
	}
	return 0;
}
