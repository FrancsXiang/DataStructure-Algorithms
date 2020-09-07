#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

int rec;
map<double, int> cnt;


int main()
{
	vector<double> arr;
	srand(time(0));
	for (int i = 0; i < 10; i++) {
		arr.push_back(rand() % 1000 + 1);
		cnt[arr.back()]++;
	}
	vector<double> res(arr.size());
	for (auto& it : cnt) {
		it.second += rec;
		rec = it.second;
	}
	for (auto val : arr) {
		res[--cnt[val]] = val;
	}
	for (auto it : arr) cout << it << " ";
	cout << endl;
	for (auto it : res) cout << it << " ";

	return 0;
}
